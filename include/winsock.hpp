#ifndef _WINSOCK_HPP_
#define _WINSOCK_HPP_
#include <map>
#include <winsock2.h>
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
class WinSock : public Comm
{
public:
    static const map<string,int>& enumSysIpAddr();//枚举系统ip地址
    friend void * acceptRoutine(void * data);

    WinSock(const string &ip, unsigned int port);
    ~WinSock();

    
    int open();
    void close();
    void connect(const string &ip, unsigned int port);//客户端需要实现
    int send(const string& data);
    int recv(string& data);
    bool compare(const string& data);
    
    SOCKET sockFd;
    
private:
    static map<string,int> mapSysIp;

    struct
    {
        string ip;
        unsigned int port;
        string remoteIp;
        unsigned int remotePort;
        bool isServer;//依据是否调用connect来设置
    } settings;
    pthread_t acceptTh; 
};


#endif

