#include "winsock.hpp"
#include "os.hpp"

map<string,int> WinSock::mapSysIp;

const map<string,int>&  WinSock::enumSysIpAddr()
{
    int ret;
    WSADATA wsaData;
    HOSTENT* host;
    //struct in_addr addr;
    int i = 0;
    char hostName[HOST_NAME_MAX_LEN];
    char hostIp[HOST_IP_MAX_LEN];
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
    return mapSysIp;
}

void * acceptRoutine(void * data)
{
    WinSock *pSock = reinterpret_cast<WinSock*>(data);
    SOCKET acceptSock;
    while (1)
    {
        acceptSock = SOCKET_ERROR;
        acceptSock = accept(pSock->sockFd,NULL,NULL);
        if (acceptSock != INVALID_SOCKET)
        {
            pSock->sockFd = acceptSock;
            break;
        }
        OS::wait(20);
    }
    return NULL;
}


WinSock::WinSock(const string &ip, unsigned int port)
  :sockFd(INVALID_SOCKET)
{
    settings.ip = ip;
    settings.port = port;
    settings.isServer = true;
    lastSend = new char[COMMBUF_LEN];
    readBuf = new char[COMMBUF_LEN];
}

WinSock::~WinSock()
{
    delete lastSend;
    delete readBuf;
}

int WinSock::open()
{
    //TODO:区分客户端和服务端
    //TODO:客户端 WSAStartup->socket->connect
    //TODO:服务端 WSAStartup->socket->bind->listen->accept
    int ret;
    WSADATA wsaData;
    sockaddr_in service;
    ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0) return COMM_ERR_OPEN;
    sockFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockFd == INVALID_SOCKET) return COMM_ERR_OPEN;
    
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(settings.ip.c_str());
    service.sin_port = htons(settings.port);
    
    ret = bind(sockFd, (SOCKADDR*)&service, sizeof(service));
    if (ret == SOCKET_ERROR) return COMM_ERR_OPEN;
    
    if (settings.isServer)
    {
        ret = listen(sockFd, 1);
        if (ret == SOCKET_ERROR) return COMM_ERR_OPEN;
        pthread_create(&acceptTh, NULL, acceptRoutine, this);
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

void WinSock::close()
{
    pthread_cancel(acceptTh);
    WSACleanup();
    sockFd = INVALID_SOCKET;
    return;
}

void WinSock::connect(const string &ip, unsigned int port)
{
    settings.remoteIp = ip;
    settings.remotePort = port;
    settings.isServer = false;
    return;
}

int WinSock::send(const string& data)
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

int WinSock::recv(string& data)
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

bool WinSock::compare(const string& data)
{
    if(data == lastSend) return true;
    ++erroCount;
    return false;
}

