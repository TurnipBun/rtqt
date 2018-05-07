#ifdef VXWORKS
#include <hostLib.h>
#include <inetLib.h>
#endif
#include "sock.hpp"
#include "os.hpp"

map<string,int> Sock::mapSysIp;

#ifdef VXWORKS
/**W I N   S O C K . E N U M   S Y S   I P   A D D R***********************
 * Create: BY Huang Cheng(yelloworangecc@icloud.com) ON 2018424
 * Description: vx下获得系统ip地址，目前只能获得一个ip地址
 * Parameters: 
   - void
 * Return: const map<string,int>& 对成员变量mapSysIp的const 引用
----------------------------C H A N G E   L O G----------------------------
 * 
**************************************************************************/
const map<string,int>&  Sock::enumSysIpAddr()
{
    int ret;
    char *ptr;
    char hostName[HOST_NAME_MAX_LEN];
    char hostIp[HOST_IP_MAX_LEN];
    
    if (mapSysIp.empty())
    {
        ret = gethostname(hostName, HOST_NAME_MAX_LEN);
        if (ret == ERROR) return mapSysIp;
        ret = hostGetByName(hostName);
        if (ret == ERROR) return mapSysIp;
        ptr = (char *)&ret;
        sprintf(hostIp,"%d.%d.%d.%d",
                ptr[0] & 0xFF, ptr[1] & 0xFF,
                ptr[2] & 0xFF, ptr[3] & 0xFF);
        mapSysIp.insert(pair<string,int>(hostIp,0));
    }
    return mapSysIp;
}
#else
/**W I N   S O C K . E N U M   S Y S   I P   A D D R***********************
 * Create: BY Huang Cheng(yelloworangecc@icloud.com) ON 2018424
 * Description: windows下枚举系统ip地址
 * Parameters: 
   - void
 * Return: const map<string,int>& 对成员变量mapSysIp的const 引用
----------------------------C H A N G E   L O G----------------------------
 * 
**************************************************************************/
const map<string,int>&  Sock::enumSysIpAddr()
{
    int ret;
    WSADATA wsaData;
    HOSTENT* host;
    //struct in_addr addr;
    int i = 0;
    char hostName[HOST_NAME_MAX_LEN];
    char hostIp[HOST_IP_MAX_LEN];
    if (mapSysIp.empty())
    {
        ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (ret != 0) return mapSysIp;

        ret = gethostname(hostName, HOST_NAME_MAX_LEN);
        if (ret != 0) return mapSysIp;

        host = gethostbyname(hostName);
        if (host == NULL) return mapSysIp;

        while (host->h_addr_list[i] != 0)
        {
            sprintf(hostIp,"%d.%d.%d.%d",
                    host->h_addr_list[i][0] & 0xFF, host->h_addr_list[i][1] & 0xFF,
                    host->h_addr_list[i][2] & 0xFF, host->h_addr_list[i][3] & 0xFF);
            //addr.S_un.S_addr = *(u_long *)host->h_addr_list[i++];
            mapSysIp.insert(pair<string,int>(hostIp,i));
            ++i;
        }
        WSACleanup();
    }
    return mapSysIp;
}
#endif

void * acceptRoutine(void * data)
{
    Sock *pSock = reinterpret_cast<Sock*>(data);
    int acceptSock;
    while (1)
    {
        acceptSock = SOCKET_ERROR;
        acceptSock = ::accept(pSock->sockFd,NULL,NULL);
        if (acceptSock != INVALID_SOCKET)
        {
            pSock->sockFd = acceptSock;
            break;
        }
        pthread_testcancel();
        OS::wait(20);
    }
    pthread_exit(NULL);
    return NULL;
}


Sock::Sock(const string &ip, unsigned int port)
  :sockFd(INVALID_SOCKET)
{
    settings.ip = ip;
    settings.port = port;
    settings.isServer = true;
    lastSend = new char[COMMBUF_LEN];
    readBuf = new char[COMMBUF_LEN];
}

Sock::~Sock()
{
    delete lastSend;
    delete readBuf;
}

int Sock::open()
{
    int ret;
    sockaddr_in service;

    sockFd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockFd == INVALID_SOCKET) return COMM_ERR_OPEN;
    
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(settings.ip.c_str());
    service.sin_port = htons(settings.port);
    
    ret = ::bind(sockFd, (SOCKADDR*)&service, sizeof(service));
    if (ret == SOCKET_ERROR) return COMM_ERR_OPEN;
    
    if (settings.isServer)
    {
        ret = ::listen(sockFd, 1);
        if (ret == SOCKET_ERROR) return COMM_ERR_OPEN;
        pthread_create(&acceptTh, NULL, acceptRoutine, this);
        pthread_detach(acceptTh);
    }
    else
    {
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = inet_addr(settings.remoteIp.c_str());
        service.sin_port = htons(settings.remotePort);

        ret = ::connect(sockFd, (SOCKADDR*)&service, sizeof(service));
        if (ret == SOCKET_ERROR) return COMM_ERR_OPEN;
    }
    return COMM_SUC;
}

void Sock::close()
{
    pthread_cancel(acceptTh);
#ifndef VXWORKS
    closesocket(sockFd);
#else
    close(sockFd);
#endif
    sockFd = INVALID_SOCKET;
    return;
}

void Sock::connect(const string &ip, unsigned int port)
{
    settings.remoteIp = ip;
    settings.remotePort = port;
    settings.isServer = false;
    return;
}

int Sock::send(const string& data)
{
    int ret,len;
    len = data.length();
    memset(lastSend,0,COMMBUF_LEN);
    memcpy(lastSend,data.c_str(),len);
    ret = ::send(sockFd,lastSend,len,0);
    if (ret != len) return COMM_ERR_SEND;
    lastSend[ret] = '\0';
    ++sendCount;
    return COMM_SUC;
}

int Sock::recv(string& data)
{
    int ret;
    memset(readBuf,'a',COMMBUF_LEN);
    readBuf[COMMBUF_LEN-1] = '\0';
    ret = ::recv(sockFd, readBuf,COMMBUF_LEN, 0);
    if (ret <= 0) return COMM_ERR_RECV;
    readBuf[ret] = '\0';
    data = readBuf;
    ++recvCount;
    return COMM_SUC;
}

bool Sock::compare(const string& data)
{
    if(data == lastSend) return true;
    ++erroCount;
    return false;
}

