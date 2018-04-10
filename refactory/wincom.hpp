#ifndef _WINCOM_HPP_
#define _WINCOM_HPP_
#include <windows.h>
#include <winbase.h>
#include <map>
#include "com.hpp"

using std::map;
using std::pair;
#define REG_DARA_MAXLEN 255

/**W I N   C O M***********************************************************
 * Create: BY Huang Cheng(turnipbun@icloud.com) ON 2018327
 * Description: windows 串口通讯类
 * Members: 
   - 
----------------------------C H A N G E   L O G----------------------------
 * 
**************************************************************************/
class WinCom : public Com
{
public:
    static const map<string,int>& enumSettingPort();
    static const map<string,int>& enumSettingBaudRate();
    static const map<string,int>& enumSettingDataBit();
    static const map<string,int>& enumSettingStopBit();
    static const map<string,int>& enumSettingParity();

    WinCom(const string& portName, int baudRate, int dataBit, int stopBit, int parity);
    ~WinCom();
    
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

    
    HANDLE comm;
    DWORD err;
    COMSTAT status;
};

#endif

