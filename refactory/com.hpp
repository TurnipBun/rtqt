#ifndef _COM_HPP_
#define _COM_HPP_
#include <string>
using std::string;


#define COM_SUC 0
#define COM_ERR -1
#define COM_ERR_OPEN -2
#define COM_ERR_IOCTL -3
#define COM_ERR_SEND -4
#define COM_ERR_RECV -5

#define READBUF_LEN 32

/**C O M*******************************************************************
 * Create: BY Huang Cheng(yelloworangecc@icloud.com) ON 2018410
 * Description: 串口通讯接口类
 * Members: 
   - 
----------------------------C H A N G E   L O G----------------------------
 * 
**************************************************************************/
class Com
{
public:
    Com():lastSend(NULL),readBuf(NULL),sendCount(0),recvCount(0),erroCount(0){}
    virtual ~Com(){}
    
    virtual int open() = 0;
    virtual void close() = 0;
    virtual int send(const string& data) = 0;
    virtual int recv(string& data) = 0;
    virtual bool compare(const string& data) = 0;
    
    unsigned int getSendCount(){return sendCount;}
    unsigned int getRecvCount(){return recvCount;}
    unsigned int getErroCount(){return erroCount;}

protected:
    
    struct 
    {
        string portName;
        int baudRate;
        int dataBit;
        int stopBit;
        int parity;
    } settings;
    
    char * lastSend;
    char * readBuf;
    unsigned int sendCount;
    unsigned int recvCount;
    unsigned int erroCount;
};

#endif

