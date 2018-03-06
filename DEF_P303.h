/*************************************************
Copyright (C) 2003, EMBED
File name: DEF_P303.h   
Author:    nifangfang       
Date:      2011.01.13
Description:  .h for HT-P303 driver
Version: 1.0.1


modification history
--------------------
01c,29Mar2012,nf     add option for vxworks5.5 or vxworks6.6
01b,29Mar2012,nf     add option to switch middleware function calling

*************************************************/
#ifndef DEF_P303_H_
#define DEF_P303_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "iosLib.h"
#include "semLib.h"
#include "eventLib.h"   
#include "drv/pci/pciConfigLib.h" 	

#define EBT_OK 			1
#define EBT_ERROR 		0
#define EBT_BIT_OK 		1
#define EBT_BIT_ERROR 	(-1)
	
/*can initialize struct */
struct CANRMInitInBuf
{  
	unsigned char	FrameFormat;		/* 0 = Std or 1 = Ext */
	unsigned long	LocalID;			/* local CAN node id (4 bytes at least) acr */
	unsigned long	LocalIDMask;		/* local CAN node id mask (4 bytes at least) amr */
	unsigned long	BaudRate;           
	unsigned long	Reserved1;			/* reserved */ /*for sja1000, 1=single 32 bit filter, 0=double 16 bit filter */
	unsigned long	Reserved2;			/* reserved */
	unsigned long	Reserved3;			/* reserved */
	unsigned long	Reserved4;			/* reserved */
};
/*can data frames struct */
typedef struct 
{
unsigned char FrameFormat ;                /*0 = Std  or 1 = Ext */
unsigned char RTR;                          /*0 = data frames or 1 = long-range frames */
unsigned char DataLenCode;                  /*data length*/
unsigned long ID;
unsigned char Data[8];
}CANRMMsg;

/****vxworks snap to 4 byte ，sizeof(RECORD_BUFF) = 20*******nf 20110726***/
#if 0
typedef struct
{
 unsigned char dirct;/* 0=接收，1=发送*/
 CANRMMsg canmsg;
}RECORD_BUFF;
#endif 
/***修改为一下，sizeof(RECORD_BUFF) = 16***/

/*can 数据录取数据帧*/
typedef struct
{
 unsigned char dirct;/* 0=接收，1=发送*/
 unsigned char FrameFormat ;                /*0=标准帧，1=扩展帧*/
 unsigned char RTR;                                 /*0=数据帧，1=远程帧*/
 unsigned char DataLenCode;                  /* 数据长度*/
 unsigned long ID;
 unsigned char Data[8];
}RECORD_BUFF;

/***end nf****/

STATUS	P303DrvInit(void);  /*pci 设备注册函数*/

/*用户接口*/
STATUS	CANOpen(int channel);
STATUS	CANClose(int channel);
STATUS	CANInit(int channel, struct CANRMInitInBuf canrminitinbuf);
STATUS	CANReset(int channel);
STATUS	CANSend(int channel,  CANRMMsg canrmmsg);
STATUS	CANReceive(int channel,  CANRMMsg *pcanrmmsg);
STATUS	CANRMClearRecBuf(int channel);
STATUS  CANRMBit(int index,char * ErrInfo);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

