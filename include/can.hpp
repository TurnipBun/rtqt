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

#define CAN_ERR 0
#define CAN_SUC 1

/*代表CAN的一个通道*/
class CAN
{
public:
	CAN(int ch);
	~CAN();
	
	int init(int id, int mask = 0xffff, int rate = 250);//调用CANopen和CANinit进行初始化
	void setSendMsgHead(int id, int dataLen = 8);//设置CAN消息头
	int send(string msg);//发送CAN消息
	int recv();//接收CAN消息
	int close();//关闭CAN通道
	
	int getChannel();//获取通道号
	string getSendMsg();//获取发送消息
	string getRecvMsg();//获取接收消息
private:
    int channel;
	CANRMMsg sendMsg;
	CANRMMsg recvMsg;
    bool isInited;
    bool isHeadSetted;
    //TODO:添加计数器,发送计数,接收计数,错误计数
};

inline int CAN::getChannel()
{
    return channel;
}
inline string CAN::getSendMsg()
{
    return string((char*)sendMsg.Data,8);
}
inline string CAN::getRecvMsg()
{
    return string((char*)recvMsg.Data,8);
}

#endif
