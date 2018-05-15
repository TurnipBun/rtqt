#include <QtGui>
#include "os.hpp"
#include "can.hpp"

map<string,int> Can::mapDevice;
map<string,int> Can::mapBaudRate;

const map<string,int>& Can::enumSettingDevice()
{
    if (mapDevice.empty())
    {
        mapDevice.insert(pair<string,int>("0",0));
        mapDevice.insert(pair<string,int>("1",1));
        mapDevice.insert(pair<string,int>("2",2));
    }
    return mapDevice;
}

const map<string,int>& Can::enumSettingBaudRate()
{
    if (mapBaudRate.empty())
    {
        mapBaudRate.insert(pair<string,int>("10",10));
        mapBaudRate.insert(pair<string,int>("50",50));
        mapBaudRate.insert(pair<string,int>("100",100));
        mapBaudRate.insert(pair<string,int>("125",125));
        mapBaudRate.insert(pair<string,int>("200",200));
        mapBaudRate.insert(pair<string,int>("250",250));
        mapBaudRate.insert(pair<string,int>("400",400));
        mapBaudRate.insert(pair<string,int>("500",500));
        mapBaudRate.insert(pair<string,int>("800",800));
        mapBaudRate.insert(pair<string,int>("1000",1000));
    }
    return mapBaudRate;
}

Can::Can(int channel,int rate)
    :ch(channel),baudRate(rate)
{
    lastSend = new char[COMMBUF_LEN];
    readBuf = new char[COMMBUF_LEN];
}

Can::~Can()
{
    delete lastSend;
    delete readBuf;
}

int Can::open()
{
    CANRMInitInBuf conf;
    
    if (CAN_ERR == CANOpen(ch))
    {
        return COMM_ERR_OPEN;
    }
    CANReset(ch);

    conf.FrameFormat = 0;
    conf.LocalID = CAN_DEFAULT_LOCALID;
    conf.LocalIDMask = CAN_DEFAULT_MASK;
    conf.BaudRate = baudRate;
    conf.Reserved1=1;
    conf.Reserved2=0;
    conf.Reserved3=0;
    conf.Reserved4=0;

    if (CAN_ERR == CANInit(ch, conf))
    {
        CANClose(ch);
        return COMM_ERR_INIT;
    }

    return COMM_SUC;
}

void Can::close()
{
    CANReset(ch);
    CANClose(ch);
}

int Can::send(const string& data)
{
    CANRMMsg *msg = (CANRMMsg *)lastSend;
    int len = data.size();
    memset(lastSend,0,COMMBUF_LEN);

    msg->FrameFormat = 0;
    msg->RTR = 0;
    msg->ID = CAN_DEFAULT_MSGID;
    msg->DataLenCode = len;
    memcpy(msg->Data,data.c_str(),len);

    if (CAN_SUC != CANSend(ch, *msg))
    {
        return COMM_ERR_SEND;
    }
    ++sendCount;
    return COMM_SUC;
}

int Can::recv(string& data)
{
    CANRMMsg *msg = (CANRMMsg *)readBuf;
    memset(readBuf,'a',COMMBUF_LEN);
    int ret = CANReceive(ch, msg);
    if (CAN_SUC != ret) return COMM_ERR_RECV;
    msg->Data[msg->DataLenCode] = '\0';
    data = (char*)msg->Data;
    ++recvCount;
    return COMM_SUC;
}

bool Can::compare(const string &data)
{
    if(data == (lastSend+8)) return true;
    ++erroCount;
    return false;
}


