#ifndef _WINSOCK_HPP_
#define _WINSOCK_HPP_
#include <map>
#ifdef VXWORKS
#include <sockLib.h>
#include <in.h>
#define INVALID_SOCKET ERROR
#define SOCKET_ERROR ERROR
#else
#include <winsock2.h>
#endif
#include <pthread.h>
#include "comm.hpp"

using std::map;
using std::pair;

#define HOST_NAME_MAX_LEN 128
#define HOST_IP_MAX_LEN 32

void * acceptRoutine(void * data);

/**W I N   S O C K*********************************************************
 * Create: BY Huang Cheng(yelloworangecc@icloud.com) ON 2018418
 * Description: window平台的socket通信类
 * Members: 
   - 
----------------------------C H A N G E   L O G----------------------------
 * 
**************************************************************************/
class Sock : public Comm
{
public:
    static const map<string,int>& enumSysIpAddr();//枚举系统ip地址
    friend void * acceptRoutine(void * data);

    Sock(const string &ip, unsigned int port, const string& protocol);
    ~Sock();

    
    int open();
    void close();
    void connect(const string &ip, unsigned int port);//客户端需要实现
    int send(const string& data);
    int recv(string& data);
    bool compare(const string& data);
    
    int sockFd;
    
private:
    int createSock();
    int initSock();

    static map<string,int> mapSysIp;
    sockaddr_in local;
    sockaddr_in remote;
    bool isRemoteOk;

    struct
    {
        string ip;
        unsigned int port;
        string remoteIp;
        unsigned int remotePort;
        int protocol;
        bool isServer;//依据是否调用connect来设置
    } settings;
    pthread_t acceptTh; 
};


#endif

