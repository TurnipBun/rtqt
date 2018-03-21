#ifndef CAN_H
#define CAN_H

#include <cstring>
#include <string>
#include <pthread.h>
#include <QtGui>

#ifdef VXWORKS
#include "DEF_P303.h"
#else
#include "EXPORT_P303.H"
#endif

using std::string;
typedef unsigned int Count;

#define CAN_ERR 0
#define CAN_SUC 1
#define CAN_DEFAULT_LOCALID 0x16e
#define CAN_DEFAULT_MASK    0xffff
#define CAN_DEFAULT_RATE    250
#define CAN_DEFAULT_MSGID   0xf1
#define CAN_DEFAULT_DATALEN 8

/*代表CAN的一个通道*/
class CAN
{
public:
	CAN(int ch);
	~CAN();
	
	int init(int rate, int id = CAN_DEFAULT_LOCALID, int mask = CAN_DEFAULT_MASK);//调用CANopen和CANinit进行初始化
	void setMsgHead(int id = CAN_DEFAULT_MSGID, int dataLen = CAN_DEFAULT_DATALEN);//设置CAN消息头
	int send(string msg);//发送CAN消息
	int recv();//接收CAN消息
	int close();//关闭CAN通道
	bool checkMsg(const CANRMMsg &msg);//判断是否为所发送的消息
	
	int getChannel();//获取通道号
	Count getSendCount();//获取发送计数
    Count getRecvCount();//获取接收计数
    Count getErrCount();//获取错包计数
    const CANRMMsg &getSendMsgRaw();//获取发送消息结构体
	const CANRMMsg &getRecvMsgRaw();//获取接收消息结构体
	string getSendMsgStr();//获取发送消息,字符串,不带头
	string getRecvMsgStr();//获取接收消息,字符串,不带头
private:
    int channel;
    Count sendCount;
    Count recvCount;
    Count errCount;
	CANRMMsg sendMsg;
	CANRMMsg recvMsg;
    bool isInited;
    bool isHeadSetted;
};

inline int CAN::getChannel()
{
    return channel;
}

inline Count CAN::getSendCount()
{
    return sendCount;
}

inline Count CAN::getRecvCount()
{
    return recvCount;
}

inline Count CAN::getErrCount()
{
    return errCount;
}

inline const CANRMMsg &CAN::getSendMsgRaw()
{
    return sendMsg;
}

inline const CANRMMsg &CAN::getRecvMsgRaw()
{
    return recvMsg;
}

inline string CAN::getSendMsgStr()
{
    return string((char*)sendMsg.Data,8);
}

inline string CAN::getRecvMsgStr()
{
    return string((char*)recvMsg.Data,8);
}

#endif
