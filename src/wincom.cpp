#include "wincom.hpp"

map<string,int> WinCom::mapPort;
map<string,int> WinCom::mapBaudRate;
map<string,int> WinCom::mapDataBit;
map<string,int> WinCom::mapStopBit;
map<string,int> WinCom::mapParity;

const map<string,int>& WinCom::enumSettingPort()
{
    int i,ret = ERROR_SUCCESS;
    HKEY key;
    CHAR valueNameBuf[REG_DARA_MAXLEN + 1];
    DWORD valueNameLen;
    DWORD valueType;
    CHAR valueDataBuf[REG_DARA_MAXLEN + 1];
    DWORD valueDataLen;
    if (mapPort.empty())
    {
        //打开键
        ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_READ, &key);

        for (i = 0; ret != ERROR_NO_MORE_ITEMS ; ++i )
        {
            //长度会作为入参使用
            valueNameLen = REG_DARA_MAXLEN + 1;
            valueDataLen = REG_DARA_MAXLEN + 1;
            
            ret = RegEnumValueA(key, i, valueNameBuf, &valueNameLen, NULL, NULL, NULL, NULL);
            if (ERROR_SUCCESS != ret) continue;
            if (NULL == strstr(valueNameBuf,"ser") && NULL == strstr(valueNameBuf,"Serial") && NULL == strstr(valueNameBuf,"Comm")) continue;
            ret = RegQueryValueExA(key, valueNameBuf, NULL, &valueType, (UCHAR*)valueDataBuf, &valueDataLen);
            if (ERROR_SUCCESS != ret) continue;
            mapPort.insert(pair<string,int>(valueDataBuf,i));
        }
        //关闭键
        RegCloseKey(key);
    }
    
    return mapPort;
}

const map<string,int>& WinCom::enumSettingBaudRate()
{
    if (mapBaudRate.empty())
    {
        mapBaudRate.insert(pair<string,int>("9600",CBR_9600));
        mapBaudRate.insert(pair<string,int>("115200",CBR_115200));
    }
    return mapBaudRate;
}

const map<string,int>& WinCom::enumSettingDataBit()
{
    if (mapDataBit.empty())
    {
        mapDataBit.insert(pair<string,int>("7",7));
        mapDataBit.insert(pair<string,int>("8",8));
    }
    return mapDataBit;
}

const map<string,int>& WinCom::enumSettingStopBit()
{
    if (mapStopBit.empty())
    {
        mapStopBit.insert(pair<string,int>("1",ONESTOPBIT));
        mapStopBit.insert(pair<string,int>("2",TWOSTOPBITS));
    }
    return mapStopBit;
}

const map<string,int>& WinCom::enumSettingParity()
{
    if (mapParity.empty())
    {
        mapParity.insert(pair<string,int>("NONE",NOPARITY));
        mapParity.insert(pair<string,int>("EVEN",EVENPARITY));
        mapParity.insert(pair<string,int>("ODD",ODDPARITY));
    }
    return mapParity;
}


WinCom::WinCom(const string& portName, int baudRate, int dataBit, int stopBit, int parity)
    :comm(INVALID_HANDLE_VALUE)
{
    settings.portName = "\\\\.\\";
    settings.portName += portName;
    settings.baudRate = baudRate;
    settings.dataBit = dataBit;
    settings.stopBit = stopBit;
    settings.parity = parity;
    lastSend = new char[COMMBUF_LEN];
    readBuf = new char[COMMBUF_LEN];
}

WinCom::~WinCom()
{
    delete lastSend;
    delete readBuf;
}

int WinCom::open()
{
    DCB dcb;
    comm = CreateFileA(settings.portName.c_str(), GENERIC_READ | GENERIC_WRITE,
                       0, 0, OPEN_EXISTING, 0, 0);
    if (comm == INVALID_HANDLE_VALUE) return COMM_ERR_OPEN;

    memset(&dcb,0,sizeof(DCB));
    GetCommState(comm, &dcb);
    dcb.BaudRate = settings.baudRate;
    dcb.ByteSize = settings.dataBit;
    dcb.StopBits = settings.stopBit;
    dcb.Parity = settings.parity;
    SetCommState(comm, &dcb);

    PurgeComm(comm, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);

    ClearCommError(comm, &err, &status);

    COMMTIMEOUTS commTimeouts;
    memset(&commTimeouts,0,sizeof(COMMTIMEOUTS));
    commTimeouts.ReadIntervalTimeout = 20;
    commTimeouts.ReadTotalTimeoutConstant = 20;
    SetCommTimeouts(comm, &commTimeouts);

    return COMM_SUC;
}

void WinCom::close()
{
    FlushFileBuffers(comm);
    CancelIo(comm);
    CloseHandle(comm);
    comm = INVALID_HANDLE_VALUE;
}

int WinCom::send(const string& data)
{
    bool ret;
    unsigned int len = data.size();
    unsigned long written = 0;
    memset(lastSend,0,COMMBUF_LEN);
    memcpy(lastSend,data.c_str(),len);
    ret = WriteFile(comm, lastSend, len, &written, NULL);
    if (!ret || written != len) return COMM_ERR_SEND;
    ++sendCount;
    return COMM_SUC;
}

int WinCom::recv(string& data)
{
    bool ret;
    unsigned long recvedSize = 0;
    if (!ClearCommError(comm, &err, &status)) return COMM_ERR_RECV;
    if (status.cbInQue == 0) return COMM_ERR_RECV;
    memset(readBuf,'a',COMMBUF_LEN);
    readBuf[COMMBUF_LEN-1] = '\0';
    ret = ReadFile(comm, readBuf, COMMBUF_LEN, &recvedSize, NULL);
    if(!ret || recvedSize == 0)  return COMM_ERR_RECV;
    readBuf[recvedSize] = '\0';
    data = readBuf;
    ++recvCount;
    return COMM_SUC;
}

bool WinCom::compare(const string& data)
{
    if(data == lastSend) return true;
    ++erroCount;
    return false;
}





