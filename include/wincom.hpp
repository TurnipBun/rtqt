#ifndef _WINCOM_HPP_
#define _WINCOM_HPP_
#include <windows.h>
#include <winbase.h>
#include "com.hpp"

#define REG_DARA_MAXLEN 255

/**G E T   W I N   C O M   L I S T*****************************************
 * Create: BY Huang Cheng(turnipbun@icloud.com) ON 2018328
 * Description: windows平台下获取可用的COM设备列表
 * Members: 
   - 
----------------------------C H A N G E   L O G----------------------------
 * 
**************************************************************************/
class GetWinComList : public GetComList
{
public:
    list<string> &operator()();
    ~GetWinComList(){}
};


/**W I N   C O M***********************************************************
 * Create: BY Huang Cheng(turnipbun@icloud.com) ON 2018327
 * Description: windows 串口通讯类
 * Members: 
   - 
----------------------------C H A N G E   L O G----------------------------
 * 
**************************************************************************/
class WinCom : public COM
{
public:
    WinCom(const string & comName, const string &strBoundRate, const string &strDataBit,
             const string &strStopBit, const string &strParity);
    ~WinCom();
    int init();
    void close();
    int send(const char *data, unsigned int len);
    int recv();
    bool compare(const char *data);

    void setBaudRateByString(const string & strBaudRate);
    void setDataBitByString(const string & strDataBit);
    void setStopBitByString(const string & strStopBit);
    void setParityByString(const string & strParity);
    
private:
    int baudRate;
    int dataBit;
    int stopBit;
    int parity;
    
    HANDLE comm;
    DWORD err;
    COMSTAT status;
};

#endif

