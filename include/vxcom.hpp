#ifndef _VXCOM_HPP_
#define _VXCOM_HPP_
#include <map>
#include "comm.hpp"
using std::map;

class VxCom : public Comm
{
public:
    static const map<string,int>& enumSettingPort();
    static const map<string,int>& enumSettingBaudRate();
    static const map<string,int>& enumSettingDataBit();
    static const map<string,int>& enumSettingStopBit();
    static const map<string,int>& enumSettingParity();
    
    VxCom(const string& portName, int baudRate, int dataBit, int stopBit, int parity, bool isRtsOn);
    ~VxCom();

    int open();
    void close();
    int send(const string& data);
    int recv(string& data);
    bool compare(const string& data);

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
        bool isRtsOn;
    } settings;
    
    int fd;
};

#endif

