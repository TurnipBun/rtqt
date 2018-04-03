#ifndef _COM_HPP_
#define _COM_HPP_
#include <list>
#include <string>
using std::list;
using std::string;

#define BUF_LEN 1023
#define COM_ERR -1
#define COM_SUC 0

typedef unsigned int Count;

/**G E T   C O M   L I S T*************************************************
 * Create: BY Huang Cheng(turnipbun@icloud.com) ON 2018328
 * Description: 获取操作系统可用串口列表的函数类
 * Members: 
   - 
----------------------------C H A N G E   L O G----------------------------
 * 
**************************************************************************/
class GetComList
{
public:
    virtual list<string> &operator()() = 0;
    virtual ~GetComList(){comList.clear();}
protected:
    list<string> comList;
};

/**C   O   M***************************************************************
 * Create: BY Huang Cheng(turnipbun@icloud.com) ON 2018327
 * Description: 串口通讯接口类,负责端口名,发送缓存,接收缓存的管理
 * Members: 
   - 
----------------------------C H A N G E   L O G----------------------------
 * 
**************************************************************************/
class COM
{
public:
    COM():pSend(NULL),pRecv(NULL),sendCount(0),recvCount(0),errCount(0){}
    virtual ~COM(){}
    
    virtual int init() = 0;
    virtual void close() = 0;
    virtual int send(const char *data, unsigned int len) = 0;
    virtual int recv() = 0;
    virtual bool compare(const char *data) = 0;
    
	Count getSendCount(){return sendCount;}
    Count getRecvCount(){return recvCount;}
    Count getErrCount(){return errCount;}
    const char *getSendData(){return pSend;}
    const char *getRecvData(){return pRecv;}
    
protected:
    
    string strPortName;
    char * pSend;
    char * pRecv;
    
    Count sendCount;
    Count recvCount;
    Count errCount;
};

#endif

