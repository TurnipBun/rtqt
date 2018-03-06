#ifndef CAN_H
#define CAN_H

#ifdef VXWORKS
#include "DEF_P303.h"
#else
#include "EXPORT_P303.H"
#endif


#define CAN_ERR 0
#define CAN_SUC 1

#define INVALID_DEVNO 0xff
//#define INVALID_CHANNELNO 0xff;

using DevNo = unsigned char;
using ChannelNo = unsigned char;
using LocalID = unsigned int;
using MsgUnit = unsigned char;

class Can
{
public:
	Can(DevNo = INVALID_DEVNO);
    void reset(DevNo);
	int openAll();
	int initAll();
    int send(CANRMMsg &msgData,ChannelNo channel);
    int resv(CANRMMsg &msgData,ChannelNo channel);
    ChannelNo getFirstChannel();
    ChannelNo getSecondChannel();
	int createRecvTask();
	void closeAll();

	static void defaultInitData(CANRMInitInBuf &initData);
	static void defaultMsgData(CANRMMsg &msgData);
private:

	DevNo devNo;
    ChannelNo firstChannel;
    ChannelNo secondChannel;
    MsgUnit firstSendBuf[8];
    MsgUnit secondSendBuf[8];
    MsgUnit firstRecvBuf[8];
    MsgUnit secondRecvBuf[8];
};
#endif