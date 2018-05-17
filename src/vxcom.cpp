#include <ioLib.h>
#include <sioLib.h>
#include <string.h>
#include "vxcom.hpp"
#include "xr17d15xSio.h"
using std::pair;


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
        //mapDataBit.insert(pair<string,int>("5",CS5));
        //mapDataBit.insert(pair<string,int>("6",CS6));
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


VxCom::VxCom(const string& portName, int baudRate, int dataBit, int stopBit, int parity, bool isRtsOn)
    :fd(0)
{
    settings.portName = portName;
    settings.baudRate = baudRate;
    settings.dataBit = dataBit;
    settings.stopBit = stopBit;
    settings.parity = parity;
    settings.isRtsOn = isRtsOn;
    lastSend = new char[COMMBUF_LEN];
    readBuf = new char[COMMBUF_LEN];
}

VxCom::~VxCom()
{
    delete lastSend;
    delete readBuf;
}

int VxCom::open()
{
    fd = ::open(settings.portName.c_str(),O_RDWR,0);
    if (ERROR == fd) return COMM_ERR_OPEN;
    if (ERROR == ::ioctl(fd,FIOSETOPTIONS,OPT_RAW)) return COMM_ERR_IOCTL;
    if (ERROR == ::ioctl(fd,FIOBAUDRATE, settings.baudRate)) return COMM_ERR_IOCTL;
    if (settings.isRtsOn)
        if (ERROR == ::ioctl(fd, SIO_RS485, 1)) return COMM_ERR_IOCTL;
    else
        if (ERROR == ::ioctl(fd, SIO_RS485, 0)) return COMM_ERR_IOCTL;
    if (ERROR == ::ioctl(fd,SIO_HW_OPTS_SET,(CLOCAL|CREAD|settings.dataBit)&~(HUPCL|settings.stopBit|settings.parity))) return COMM_ERR_IOCTL;
    if (ERROR == ::ioctl(fd,FIOFLUSH,0)) return COMM_ERR_IOCTL;

    return COMM_SUC;
}

void VxCom::close()
{
    ::close(fd);
}

int VxCom::send(const string& data)
{
    int ret,len;
    len = data.size();

    memset(lastSend,0,COMMBUF_LEN);
    memcpy(lastSend,data.c_str(),len);
    ret = ::write(fd,lastSend,len);
    if (ret != len) return COMM_ERR_SEND;

    ++sendCount;
    return COMM_SUC;
}

int VxCom::recv(string& data)
{
    int ret;
    unsigned int count;
    if (ERROR == ioctl(fd,FIONREAD,&count)) return COMM_ERR_IOCTL;
    if (count == 0) return COMM_ERR_RECV;
    memset(readBuf,'a',COMMBUF_LEN);
    readBuf[COMMBUF_LEN-1] = '\0';
    ret = ::read(fd,readBuf,COMMBUF_LEN);
    if (ret <= 0) return COMM_ERR_RECV;
    readBuf[ret] = '\0';
    data = readBuf;

    ++recvCount;
    return COMM_SUC;
}

bool VxCom::compare(const string& data)
{
    if(data == lastSend) return true;
    ++erroCount;
    return false;
}
