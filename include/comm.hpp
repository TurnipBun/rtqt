#ifndef _COMM_HPP_
#define _COMM_HPP_
#include <string>
using std::string;


#define COMM_SUC 0
#define COMM_ERR -1
#define COMM_ERR_OPEN -2
#define COMM_ERR_INIT -3
#define COMM_ERR_IOCTL -4
#define COMM_ERR_SEND -5
#define COMM_ERR_SEND_REMOTE -6
#define COMM_ERR_RECV -7

#define COMMBUF_LEN 32
#define COMM_AUTO_TEST_NUM 100
#define COMM_DEFAULT_SOCKPORT 5005

/**C O M*******************************************************************
 * Create: BY Huang Cheng(yelloworangecc@icloud.com) ON 2018410
 * Description: 串口通讯接口类
 * Members: 
   - 
----------------------------C H A N G E   L O G----------------------------
 * 
**************************************************************************/
class Comm
{
public:
    Comm():lastSend(NULL),readBuf(NULL),sendCount(0),recvCount(0),erroCount(0){}
    virtual ~Comm(){}
    
    virtual int open() = 0;
    virtual void close() = 0;
    virtual int send(const string& data) = 0;
    virtual int recv(string& data) = 0;
    virtual bool compare(const string& data) = 0;
    
    unsigned int getSendCount(){return sendCount;}
    unsigned int getRecvCount(){return recvCount;}
    unsigned int getErroCount(){return erroCount;}

protected:
    
    char * lastSend;
    char * readBuf;
    unsigned int sendCount;
    unsigned int recvCount;
    unsigned int erroCount;
};

#endif

