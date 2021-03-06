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
        if (acceptSock != (int)INVALID_SOCKET)
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


Sock::Sock(const string &ip, unsigned int port, const string& protocol)
  :sockFd(INVALID_SOCKET),isRemoteOk(false)
{
    settings.ip = ip;
    settings.port = port;
    settings.isServer = true;
    if (protocol.compare("TCP") == 0)
    {
        settings.protocol = IPPROTO_TCP;
    }
    else
    {
        settings.protocol = IPPROTO_UDP;
    }
    memset(&local,0,sizeof(local));
    memset(&remote,0,sizeof(remote));
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
    sockFd = createSock();
    if (sockFd == (int)INVALID_SOCKET) return COMM_ERR_OPEN;
    return initSock();
}

void Sock::close()
{
    if (settings.protocol == IPPROTO_TCP)
    {
        pthread_cancel(acceptTh);
    }
#ifndef VXWORKS
    closesocket(sockFd);
#else
    ::close(sockFd);
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
    if (settings.protocol == IPPROTO_TCP)
    {
        ret = ::send(sockFd,lastSend,len,0);
    }
    else if (isRemoteOk)
    {
        ret = ::sendto(sockFd,lastSend,len,0,(SOCKADDR*)&remote,sizeof(remote));
    }
    else
    {
        return COMM_ERR_SEND_REMOTE;
    }
    if (ret != len) return COMM_ERR_SEND;
    lastSend[ret] = '\0';
    ++sendCount;
    return COMM_SUC;
}

int Sock::recv(string& data)
{
    int ret;
    int remote_len = sizeof(remote);
    memset(readBuf,'a',COMMBUF_LEN);
    readBuf[COMMBUF_LEN-1] = '\0';
    if (settings.protocol == IPPROTO_TCP)
    {
        ret = ::recv(sockFd, readBuf,COMMBUF_LEN, 0);
    }
    else
    {
        ret = ::recvfrom(sockFd, readBuf,COMMBUF_LEN, 0, (SOCKADDR*)&remote,&remote_len);
        isRemoteOk = true;
    }
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

int Sock::createSock()
{
    int sockType = SOCK_DGRAM;//默认udp
    if (settings.protocol == IPPROTO_TCP)
    {
        sockType = SOCK_STREAM;
    }
    return ::socket(AF_INET, sockType, settings.protocol);
}

int Sock::initSock()
{
    int ret;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = inet_addr(settings.ip.c_str());
    local.sin_port = htons(settings.port);
    ret = ::bind(sockFd, (SOCKADDR*)&local, sizeof(local));
    if (ret == SOCKET_ERROR) return COMM_ERR_OPEN;
    
    if (settings.protocol == IPPROTO_TCP)
    {
        if (settings.isServer)//服务器端
        {
            ret = ::listen(sockFd, 1);
            if (ret == SOCKET_ERROR) return COMM_ERR_OPEN;
            pthread_create(&acceptTh, NULL, acceptRoutine, this);
            pthread_detach(acceptTh);
        }
        else//客户端
        {
            remote.sin_family = AF_INET;
            remote.sin_addr.s_addr = inet_addr(settings.remoteIp.c_str());
            remote.sin_port = htons(settings.remotePort);
            isRemoteOk = true;
            ret = ::connect(sockFd, (SOCKADDR*)&remote, sizeof(remote));
            if (ret == SOCKET_ERROR) return COMM_ERR_OPEN;
        }
    }
    else
    {
        if (settings.isServer)//服务器端
        {
        }
        else//客户端
        {
            remote.sin_family = AF_INET;
            remote.sin_addr.s_addr = inet_addr(settings.remoteIp.c_str());
            remote.sin_port = htons(settings.remotePort);
            isRemoteOk = true;
        }
    }
    return COMM_SUC;
}

