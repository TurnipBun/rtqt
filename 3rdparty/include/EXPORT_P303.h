/************************************************************
  Copyright (C), 2007, Embeded Tech. Co., Ltd.
  FileName:                EXPORT_P303.H
  Description:             HT-P303 DLL        
  Version:                 1.0   
  Auther:                  Henly
  Last Modify Time:        2007.05.08
***********************************************************/
#if !defined(CAN_DLLHEAD_H)
#define CAN_DLLHEAD_H

typedef int Status;

typedef struct
{
    char devastate;
    char devInfo[256];
}DEVINFO,*PDEVINFO;

typedef struct _CANRMInitInBuf
{
    unsigned char FrameFormat ;/* 保留*/
    unsigned long LocalID;  /* 验收码*/
    unsigned long LocalIDMask;/* 屏蔽码*/
    unsigned long BaudRate;/*波特率，例如250=250K bit/s*/
    unsigned long Reserved1;/*对于SJA1000控制器，1=单滤波 0=双滤波*/
    unsigned long Reserved2; /* 保留*/
    unsigned long Reserved3; /* 保留*/
    unsigned long Reserved4; /* 保留*/
} CANRMInitInBuf;

/*---------------------------------------------------------------------
**  CurrentMode
**    bit 7    : 0 - BasicCAN mode; 1 - PeliCAN mode
**    bit 6-5    : Reserved
**    bit 4    : sleep mode
**    bit 3    : acceptance filter mode, 0 - dual filter; 1 - single filter
**    bit 2    : Reserved
**    bit 1    : listen only mode
**    bit 0    : Reserved
**  InterruptEnable
**    bit 7    : bus error interrupt enable
**    bit 6    : arbitration lost interrupt enable
**    bit 5    : error passive interrupt enable
**    bit 4    : wake-up interrupt enable
**    bit 3    : data overrun interrupt enable
**    bit 2    : error waring interrupt enable
**    bit 1    : transmit interrupt enable
**    bit 0    : receive interrupt enable
**  ErrorWarningLimit
**    bit 7-0    : error warning limit value
**-------------------------------------------------------------------*/
typedef struct _CAN_INFORMATION
{
    unsigned char CurrentMode;        /* CAN working mode */
    unsigned char InterruptEnable;    /* Interrupt enable Status */
    unsigned char ErrorWarningLimit;    /* max allowed Tx/Rx count */
} CAN_INFORMATION;

typedef struct _CANRMMsg
{
    unsigned char FrameFormat ;/*0=标准帧，1=扩展帧*/
    unsigned char RTR; /*0=数据帧，1=远程帧*/
    unsigned char DataLenCode;/* 数据长度*/
    unsigned long ID;
    unsigned char Data[8];
} CANRMMsg;

/*************************外部调用的函数*************************/
extern "C" Status __declspec(dllexport) CANOpen(int channel);
extern "C" Status __declspec(dllexport) CANClose (int channel);
extern "C" Status __declspec(dllexport) CANReset(int channel);
extern "C" Status __declspec(dllexport) CANInit(int channel,CANRMInitInBuf pcan);
extern "C" Status __declspec(dllexport) CANSend(int channel,CANRMMsg pcan_msg);
extern "C" Status __declspec(dllexport) CANReceive(int channel,CANRMMsg *pcan_msg);
extern "C" Status __declspec(dllexport) InterruptEnable1CANRM(int channel,void (* usrInterrupt)(void));
extern "C" Status __declspec(dllexport) InterruptEnable2CANRM(int channel,void (* usrInterrupt)(void));
extern "C" Status __declspec(dllexport) InterruptDisable1CANRM(int channel);
extern "C" Status __declspec(dllexport) InterruptDisable2CANRM(int channel);
extern "C" Status __declspec(dllexport) CANRMClearRcvBuf(int channel);
extern "C" Status __declspec(dllexport) CANRMBit(int mode, char *pDevInfo);
/****************************************************************/
#endif