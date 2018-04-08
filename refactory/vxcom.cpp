#include "vxcom.hpp"
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
        mapPort.insert(pair<string,int>("/tySco/0",0));
        mapPort.insert(pair<string,int>("/tySco/1",1));
        mapPort.insert(pair<string,int>("/tySco/2",2));
        mapPort.insert(pair<string,int>("/tySco/3",3));
        mapPort.insert(pair<string,int>("/tySco/4",4));
        mapPort.insert(pair<string,int>("/tySco/5",5));
        mapPort.insert(pair<string,int>("/tySco/6",6));
        mapPort.insert(pair<string,int>("/tySco/7",7));
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
{
    settings.portName = portName;
    settings.baudRate = boudRate;
    settings.dataBit = dataBit;
    settings.stopBit = stopBit;
    settings.parity = parity;
}

VxCom::~VxCom()
{
}

int VxCom::open()
{
    fd = ::open(settings.portName.c_str(),O_RDWR,0);
    if (fd == ERROR) return COM_ERR_OPEN;
    if (0 != ::ioctl(fd,FIOBAUDRATE, settings.baudRate)) return COM_ERR_IOCTL;
    if (0 != ::ioctl(fd,SIO_HW_OPTS_SET,(CLOCAL|CREAD|settings.dataBit)&~(HUPCL|settings.stopBit|settings.parity))) return COM_ERR_IOCTL;
    return COM_SUC;
}

void VxCom::close()
{
}