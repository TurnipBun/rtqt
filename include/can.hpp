#ifndef _CAN_H_
#define _CAN_H_
#include <cstring>
#include <string>
#include <map>
#include <QtGui>
#include "comm.hpp"

#ifdef VXWORKS
#include "DEF_P303.h"
#else
#include "EXPORT_P303.H"
#endif

using std::string;
using std::map;
using std::pair;

#define CAN_ERR 0
#define CAN_SUC 1
#define CAN_DEFAULT_LOCALID 0x16e
#define CAN_DEFAULT_MASK    0xffff
#define CAN_DEFAULT_RATE    250
#define CAN_DEFAULT_MSGID   0xf1
#define CAN_DEFAULT_DATALEN 8

/*代表CAN的一个通道*/
class Can : public Comm
{
public:
    static const map<string,int>& enumSettingDevice();
    static const map<string,int>& enumSettingBaudRate();

    Can(int ch,int rate);
    ~Can();

    int open();
    void close();
    int send(const string& data);
    int recv(string& data);
    bool compare(const string& data);
    
private:
    static map<string,int> mapDevice;
    static map<string,int> mapBaudRate;
    
    int ch;
    int baudRate;
};

#endif

