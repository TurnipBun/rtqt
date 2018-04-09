//#include <ioLib.h>
//#include <sioLib.h>
#include <string.h>
#include "vxcom.hpp"
using std::pair;

/* options to SIO_HW_OPTS_SET (ala POSIX), bitwise or'ed together */

#define CLOCAL         0x1     /* ignore modem status lines */
#define CREAD          0x2     /* enable device reciever */

#define CSIZE          0xc     /* bits 3 and 4 encode the character size */
#define CS5            0x0     /* 5 bits */
#define CS6            0x4     /* 6 bits */
#define CS7            0x8     /* 7 bits */
#define CS8            0xc     /* 8 bits */

#define HUPCL          0x10    /* hang up on last close */
#define STOPB          0x20    /* send two stop bits (else one) */
#define PARENB         0x40    /* parity detection enabled (else disabled) */
#define PARODD         0x80    /* odd parity  (else even) */


map<string,int> VxCom::mapPort;
map<string,int> VxCom::mapBaudRate;
map<string,int> VxCom::mapDataBit;
map<string,int> VxCom::mapStopBit;
map<string,int> VxCom::mapParity;


const map<string,int>& VxCom::enumSettingPort()
{
    if (mapPort.empty())
    {
        mapPort.insert(pair<string,int>("/tySCo/0",0));
        mapPort.insert(pair<string,int>("/tySCo/1",1));
        mapPort.insert(pair<string,int>("/tySCo/2",2));
        mapPort.insert(pair<string,int>("/tySCo/3",3));
        mapPort.insert(pair<string,int>("/tySCo/4",4));
        mapPort.insert(pair<string,int>("/tySCo/5",5));
        mapPort.insert(pair<string,int>("/tySCo/6",6));
        mapPort.insert(pair<string,int>("/tySCo/7",7));
    }
    return mapPort;
}

const map<string,int>& VxCom::enumSettingBaudRate()
{
    if (mapBaudRate.empty())
    {
        mapBaudRate.insert(pair<string,int>("9600",9600));
        mapBaudRate.insert(pair<string,int>("115200",115200));
    }
    return mapBaudRate;
}

const map<string,int>& VxCom::enumSettingDataBit()
{
    if (mapDataBit.empty())
    {
        mapDataBit.insert(pair<string,int>("5",CS5));
        mapDataBit.insert(pair<string,int>("6",CS6));
        mapDataBit.insert(pair<string,int>("7",CS7));
        mapDataBit.insert(pair<string,int>("8",CS8));
    }
    return mapDataBit;
}

const map<string,int>& VxCom::enumSettingStopBit()
{
    if (mapStopBit.empty())
    {
        mapStopBit.insert(pair<string,int>("1",0));
        mapStopBit.insert(pair<string,int>("2",STOPB));
    }
    return mapStopBit;
}

const map<string,int>& VxCom::enumSettingParity()
{
    if (mapParity.empty())
    {
        mapParity.insert(pair<string,int>("NONE",0));
        mapParity.insert(pair<string,int>("EVEN",PARENB));
        mapParity.insert(pair<string,int>("ODD",PARENB|PARODD));
    }
    return mapParity;
}


VxCom::VxCom(const string& portName, int boudRate, int dataBit, int stopBit, int parity)
    :fd(0),lastSend(NULL),readBuf(NULL),sendCount(0),recvCount(0),erroCount(0)
{
    settings.portName = portName;
    settings.baudRate = boudRate;
    settings.dataBit = dataBit;
    settings.stopBit = stopBit;
    settings.parity = parity;
    lastSend = new char[READBUF_LEN];
    readBuf = new char[READBUF_LEN];
    memset(lastSend,0,READBUF_LEN);
    memset(readBuf,0,READBUF_LEN);
}

VxCom::~VxCom()
{
}

int VxCom::open()
{
/*
    fd = ::open(settings.portName.c_str(),O_RDWR,0);
    if (ERROR == fd) return COM_ERR_OPEN;
    if (ERROR == ::ioctl(fd,FIOSETOPTIONS,OPT_RAW)) return COM_ERR_IOCTL;
    if (ERROR == ::ioctl(fd,FIOBAUDRATE, settings.baudRate)) return COM_ERR_IOCTL;
    if (ERROR == ::ioctl(fd,SIO_HW_OPTS_SET,(CLOCAL|CREAD|settings.dataBit)&~(HUPCL|settings.stopBit|settings.parity))) return COM_ERR_IOCTL;
    if (ERROR == ::ioctl(fd,FIOFLUSH,0)) return COM_ERR_IOCTL;
*/
    return COM_SUC;
}

void VxCom::close()
{
/*
    ::close(fd);
*/
}

int VxCom::send(const string& data)
{
/*
    int ret,len;
    len = data.size();
    memcpy(lastSend,data.c_str(),len);
    ret = ::write(fd,lastSend,len);
    if (ret != len) return COM_ERR_SEND;
*/
    ++sendCount;
    return COM_SUC;
}

int VxCom::recv(string& data)
{
/*
    int ret;
    ret = ::read(fd,readBuf,READBUF_LEN);
    if (ret <= 0) return COM_ERR_RECV;
    data.assign(readBuf,ret);
*/
    data = "test";
    ++recvCount;
    return COM_SUC;
}

bool VxCom::compare(const string& data)
{
    if(lastSend == data) return true;
    ++erroCount;
    return false;
}
