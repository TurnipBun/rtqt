#include <sstream>
#include <iostream>
#include <pthread.h>
#include <QtGui>

#include "os.hpp"
#include "can.hpp"

#define CAN_CHECK_RETURN(x) if ((x) == CAN_ERR) return CAN_ERR;

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;
using std::hex;

CAN::CAN(int ch)
    :channel(ch), isInited(false), isHeadSetted(false)
{}

CAN::~CAN()
{
    if (isInited)
    {
        close();
    }
}

/*初始化通道*/
int CAN::init(int id, int mask, int rate)
{

    CANRMInitInBuf conf;

    //检查是否已初始化
    if (isInited)
    {
        return CAN_SUC;
    }

    //打开通道
    if (CAN_ERR == CANOpen(channel))
    {
        return CAN_ERR;
    }

    //初始化通道
    conf.FrameFormat = 0;
    conf.LocalID = id;
    conf.LocalIDMask = mask;
    conf.BaudRate = rate;
    conf.Reserved1=1;
    conf.Reserved2=0;
    conf.Reserved3=0;
    conf.Reserved4=0;

    if (CAN_ERR == CANInit(channel, conf))
    {
        return CAN_ERR;
    }

    return CAN_SUC;
}

/*设置消息头*/
void CAN::setSendMsgHead(int id, int dataLen)
{
    sendMsg.FrameFormat = 0;
    sendMsg.RTR = 0;
    sendMsg.ID = id;
    sendMsg.DataLenCode = dataLen;

    isHeadSetted = true;//消息头已设置状态
}
int CAN::send(string msg)
{
    int i;

    //检查消息头是否设置
    if (!isHeadSetted)
    {
        return CAN_ERR;
    }

    //填充消息
    memset(sendMsg.Data,0,8);
    for (i = 0; i < 8; i++)
    {
        if (msg[i] == '\0') break;
        sendMsg.Data[i] = msg[i];
    }

    //发送消息
    if (CAN_ERR == CANSend(channel, sendMsg))
    {
        return CAN_ERR;
    }

    return CAN_SUC;
}

/*接收数据*/
int CAN::recv()
{
    return CANReceive(channel, &recvMsg);
}

/*关闭通道*/
int CAN::close()
{
    int ret = CANClose(channel);
    if (ret == CAN_SUC)
    {
        isInited = false;//恢复到未初始化状态
    }
    return ret;
}

