#ifndef _VXCOM_HPP_
#define _VXCOM_HPP_
#include <string>
#include <map>
using std::string;
using std::map;

#define COM_SUC 0
#define COM_ERR -1
#define COM_ERR_OPEN -2
#define COM_ERR_IOCTL -3
#define COM_ERR_SEND -4
#define COM_ERR_RECV -5

#define READBUF_LEN 32

class VxCom
{
public:
    VxCom(const string& portName, int baudRate, int dataBit, int stopBit, int parity);
    ~VxCom();

    static const map<string,int>& enumSettingPort();
    static const map<string,int>& enumSettingBaudRate();
    static const map<string,int>& enumSettingDataBit();
    static const map<string,int>& enumSettingStopBit();
    static const map<string,int>& enumSettingParity();

    int open();
    void close();
    int send(const string& data);
    int recv(string& data);
    bool compare(const string& data);

    unsigned int getSendCount(){return sendCount;}
    unsigned int getRecvCount(){return recvCount;}
    unsigned int getErroCount(){return erroCount;}

private:
    static map<string,int> mapPort;
    static map<string,int> mapBaudRate;
    static map<string,int> mapDataBit;
    static map<string,int> mapStopBit;
    static map<string,int> mapParity;

    struct 
    {
        string portName;
        int baudRate;
        int dataBit;
        int stopBit;
        int parity;
    } settings;
    
    int fd;
    char * lastSend;
    char * readBuf;
    unsigned int sendCount;
    unsigned int recvCount;
    unsigned int erroCount;
};

#endif

