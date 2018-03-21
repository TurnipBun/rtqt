#include <pthread.h>
#include <QtGui>

#include "os.hpp"
#include "can.hpp"

using std::string;

CAN::CAN(int ch)
    :channel(ch), sendCount(0), recvCount(0), errCount(0), isInited(false), isHeadSetted(false)
{
    memset(&sendMsg, 0, sizeof(CANRMMsg));
    memset(&recvMsg, 0, sizeof(CANRMMsg));
}

CAN::~CAN()
{
    if (isInited)
    {
        close();
    }
}

/*初始化通道*/
int CAN::init(int rate, int id, int mask)
{

    CANRMInitInBuf conf;

    //检查是否已初始化
    if (isInited)
    {
        return CAN_SUC;
    }
    isInited = true;
    
    //打开通道
    if (CAN_ERR == CANOpen(channel))
    {
        return CAN_ERR;
    }
    
    
    if (CAN_ERR == CANReset(channel))
    {
    	CANClose(channel);
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
    	CANClose(channel);
        return CAN_ERR;
    }

    return CAN_SUC;
}

/*设置消息头*/
void CAN::setMsgHead(int id, int dataLen)
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
    ++sendCount;
    return CAN_SUC;
}

/*接收数据*/
int CAN::recv()
{
    int ret = CANReceive(channel, &recvMsg);
    if (ret == CAN_SUC) ++recvCount;
    return ret;
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

/*检查数据是否为所发送数据*/
bool CAN::checkMsg(const CANRMMsg &msg)
{
    bool ret = (0 == memcmp(&sendMsg, &msg, sizeof(CANRMMsg)));
    if (ret == false) ++errCount;
    return ret;
}


