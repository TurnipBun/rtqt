#include "com.hpp"
#include "wincom.hpp"

list<string> &GetWinComList::operator()()
{
    int i;
    int ret = ERROR_SUCCESS;
    HKEY key;
    CHAR valueNameBuf[REG_DARA_MAXLEN + 1];
    DWORD valueNameLen;
    DWORD valueType;
    CHAR valueDataBuf[REG_DARA_MAXLEN + 1];
    DWORD valueDataLen;

    comList.clear();
    //打开键
    ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_READ, &key);

    for (i = 0; ret != ERROR_NO_MORE_ITEMS ; ++i )
    {
        //长度会作为入参使用
        valueNameLen = REG_DARA_MAXLEN + 1;
        valueDataLen = REG_DARA_MAXLEN + 1;
        
        ret = RegEnumValueA(key, i, valueNameBuf, &valueNameLen, NULL, NULL, NULL, NULL);
        if (ERROR_SUCCESS != ret) continue;
        if (NULL == strstr(valueNameBuf,"ser") && NULL == strstr(valueNameBuf,"Serial") && NULL == strstr(valueNameBuf,"Com")) continue;
        ret = RegQueryValueExA(key, valueNameBuf, NULL, &valueType, (UCHAR*)valueDataBuf, &valueDataLen);
        if (ERROR_SUCCESS != ret) continue;
        comList.push_back(valueDataBuf);
    }
    //关闭键
    RegCloseKey(key);
    return comList;
}

WinCom::WinCom(const string & comName, const string &strBaudRate, const string &strDataBit,
                 const string &strStopBit, const string &strParity)
    :comm(INVALID_HANDLE_VALUE)
{
    strPortName = "\\\\.\\";
    strPortName += comName;
    
    setBaudRateByString(strBaudRate);
    setDataBitByString(strDataBit);
    setStopBitByString(strStopBit);
    setParityByString(strParity);

    pSend = new char[BUF_LEN + 1];
    pSend[BUF_LEN] = '\0';
    pRecv = new char[BUF_LEN + 1];
    pRecv[BUF_LEN] = '\0';
}

WinCom::~WinCom()
{
    if (comm != INVALID_HANDLE_VALUE) close();
    if (pSend != NULL) delete pSend;
    if (pRecv != NULL) delete pRecv;
}

int WinCom::init()
{
    DCB dcb;
    comm = CreateFileA(strPortName.c_str(), GENERIC_READ | GENERIC_WRITE,
                       0, 0, OPEN_EXISTING, 0, 0);
    if (comm == INVALID_HANDLE_VALUE) return COM_ERR;

    memset(&dcb,0,sizeof(DCB));
    GetCommState(comm, &dcb);
    dcb.BaudRate = baudRate;
    SetCommState(comm, &dcb);

    PurgeComm(comm, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);

    ClearCommError(comm, &err, &status);

    COMMTIMEOUTS commTimeouts;
    memset(&commTimeouts,0,sizeof(COMMTIMEOUTS));
    commTimeouts.ReadIntervalTimeout = 40;
    commTimeouts.ReadTotalTimeoutConstant = 40;
    SetCommTimeouts(comm, &commTimeouts);

    return COM_SUC;
}

void WinCom::close()
{
    if (comm != INVALID_HANDLE_VALUE)
    {
        FlushFileBuffers(comm);
        CancelIo(comm);
        CloseHandle(comm);
        comm = INVALID_HANDLE_VALUE;
    }
}

int WinCom::send(const char *data, unsigned int len)
{
    unsigned long written = 0;
    unsigned int copyLen = len > BUF_LEN ? BUF_LEN : len;
    memcpy(pSend,data,copyLen);
    pSend[copyLen] = '\0';
        
    bool ret = WriteFile(comm, pSend, copyLen, &written, NULL);
    if (ret && written == copyLen)
    {
        ++sendCount;
        return COM_SUC;
    }
    return COM_ERR;
}

int WinCom::recv()
{
    unsigned long recvedSize;
    DWORD Errors;
    COMSTAT Status;
    if (!ClearCommError(comm, &Errors, &Status)) return COM_ERR;
    if (Status.cbInQue == 0) return COM_ERR;
    bool ret = ReadFile(comm, pRecv, BUF_LEN, &recvedSize, NULL);
    pRecv[recvedSize] = '\0';
    if(ret)
    {
        ++recvCount;
        return COM_SUC;
    }
    return COM_ERR;
}

bool WinCom::compare(const char *data)
{
    if(strcmp(pSend,data) != 0)
    {
        ++errCount;
        return false;
    }
    return true;
}


void WinCom::setBaudRateByString(const string & strBaudRate)
{
    int res;
    if      (strBaudRate.compare("110") == 0)    res = 110;
    else if (strBaudRate.compare("300") == 0)    res = CBR_300;
    else if (strBaudRate.compare("600") == 0)    res = CBR_600;
    else if (strBaudRate.compare("1200") == 0)   res = CBR_1200;
    else if (strBaudRate.compare("2400") == 0)   res = CBR_2400;
    else if (strBaudRate.compare("4800") == 0)   res = CBR_4800;
    else if (strBaudRate.compare("9600") == 0)   res = CBR_9600;
    else if (strBaudRate.compare("14400") == 0)  res = CBR_14400;
    else if (strBaudRate.compare("19200") == 0)  res = CBR_19200;
    else if (strBaudRate.compare("38400") == 0)  res = CBR_38400;
    else if (strBaudRate.compare("56000") == 0)  res = CBR_56000;
    else if (strBaudRate.compare("57600") == 0)  res = CBR_57600;
    else if (strBaudRate.compare("115200") == 0) res = CBR_115200;
    else if (strBaudRate.compare("128000") == 0) res = CBR_128000;
    else if (strBaudRate.compare("256000") == 0) res = CBR_256000;
    else res = 8;
    baudRate = res;
}

void WinCom::setDataBitByString(const string & strDataBit)
{
    int res;
    if      (strDataBit.compare("4") == 0) res = 4;
    else if (strDataBit.compare("5") == 0) res = 6;
    else if (strDataBit.compare("6") == 0) res = 7;
    else if (strDataBit.compare("7") == 0) res = 8;
    else res = 8;
    dataBit = res;
}

void WinCom::setStopBitByString(const string & strStopBit)
{
    int res;
    if      (strStopBit.compare("Onehalf") == 0) res = ONE5STOPBITS;
    else if (strStopBit.compare("Two") == 0) res = TWOSTOPBITS;
    else res = ONESTOPBIT;
    stopBit =  res;
}

void WinCom::setParityByString(const string & strParity)
{
    int res;
    if      (strParity.compare("Even") == 0)  res = EVENPARITY;
    else if (strParity.compare("Odd") == 0)   res = ODDPARITY;
    else if (strParity.compare("Mark") == 0)  res = MARKPARITY;
    else if (strParity.compare("Space") == 0) res = SPACEPARITY;
    else res = NOPARITY;
    parity = res;
}


