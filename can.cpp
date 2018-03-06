#include "can.hpp"

#define CAN_CHECK_RETURN(x) if ((x) == CAN_ERR) return CAN_ERR;

static LocalID gId = 0x1000;
static MsgUnit gUnitBase = 0;


static LocalID getLocalID()
{
    return gId <<= 1;
}
static MsgUnit getMsgUnitBase()
{
    return gUnitBase += 1;
}

Can::Can(DevNo dev)
{
    devNo = dev;
    firstChannel = dev* 2;
    secondChannel = dev * 2 + 1;
}

void Can::reset(DevNo dev)
{
    closeAll();
    devNo = dev;
    firstChannel = devNo * 2;
    secondChannel = devNo * 2 + 1;
}

int Can::openAll()
{
    int ret;
    
    ret = CANOpen(firstChannel);
    CAN_CHECK_RETURN(ret);
    ret = CANOpen(secondChannel);
    CAN_CHECK_RETURN(ret);
    
    return CAN_SUC;
}

int Can::initAll()
{
    CANRMInitInBuf initData;
    int ret;
    
    ret = CANReset(firstChannel);
    CAN_CHECK_RETURN(ret);
    ret = CANReset(secondChannel);
    CAN_CHECK_RETURN(ret);

    defaultInitData(initData);
    ret = CANInit(firstChannel, initData);
    CAN_CHECK_RETURN(ret);
    
    defaultInitData(initData);
    ret = CANInit(secondChannel, initData);
    CAN_CHECK_RETURN(ret);
}

int Can::send(CANRMMsg &msgData,ChannelNo channel)
{
    int ret;
    ret = CANSend(channel, msgData);
    CAN_CHECK_RETURN(ret);
    return CAN_SUC;
}

int Can::resv(CANRMMsg &msgData,ChannelNo channel)
{
    int ret;
    ret = CANReceive(channel, &msgData);
    CAN_CHECK_RETURN(ret);
    return CAN_SUC;
}

inline ChannelNo Can::getFirstChannel()
{
    return firstChannel;
}

inline ChannelNo Can::getSecondChannel()
{
    return secondChannel;
}

void Can::closeAll()
{
    if (devNo == INVALID_DEVNO) return;
    CANClose(firstChannel);
    CANClose(secondChannel);
    devNo == INVALID_DEVNO;
}

int Can::createRecvTask()
{

}

void Can::defaultInitData(CANRMInitInBuf &initData)
{
    initData.FrameFormat =0;           /*标准帧(1-扩展帧)*/
	initData.LocalID=getLocalID();     /*本地CAN节点ID*/
	initData.LocalIDMask =0xfffff800; /*本地CAN节点ID掩码*/
	initData.BaudRate=250;
	initData.Reserved1=1;              /*两个16位过滤器(0-单个32位过滤器)*/
}

void Can::defaultMsgData(CANRMMsg &msgData)
{
    msgData.FrameFormat = 0;      /*标准帧*/
	msgData.RTR = 0;
	msgData.ID = 0x02;            /*目标站点号*/
	msgData.DataLenCode = 8;      /*数据长度*/

	for(int i = 0; i < 8; ++i)
		msgData.Data[i] = getMsgUnitBase() + i; 
}