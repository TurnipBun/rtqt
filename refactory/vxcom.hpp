#ifndef _VXCOM_HPP_
#define _VXCOM_HPP_
#include <string>
#include <map>
using std::string;
using std::map;
/* options to SIO_HW_OPTS_SET (ala POSIX), bitwise or'ed together */

#define CLOCAL		0x1	/* ignore modem status lines */
#define CREAD		0x2	/* enable device reciever */

#define CSIZE		0xc	/* bits 3 and 4 encode the character size */
#define CS5		0x0	/* 5 bits */
#define CS6		0x4	/* 6 bits */
#define CS7		0x8	/* 7 bits */
#define CS8		0xc	/* 8 bits */

#define HUPCL		0x10	/* hang up on last close */
#define STOPB		0x20	/* send two stop bits (else one) */
#define PARENB		0x40	/* parity detection enabled (else disabled) */
#define PARODD		0x80	/* odd parity  (else even) */

#define COM_SUC 0
#define COM_ERR -1
#define COM_ERR_OPEN -2
#define COM_ERR_IOCTL -3

class VxCom
{
public:
    VxCom(const string& portName, int baudRate, int dataBit, int stopBit, int parity);
    ~VxCom();

    static const map<string,int>& enumSettingPort();
    static const map<string,int>& enumSettingBaudRate();
    static const map<string,int>& enumSettingDataBit();
    static const map<string,int>& enumSettingStopBit();
    static const map<string,int>& enumSettingParity();

    int open();
    void close();

private:
    static map<string,int> mapPort;
    static map<string,int> mapBaudRate;
    static map<string,int> mapDataBit;
    static map<string,int> mapStopBit;
    static map<string,int> mapParity;

    struct 
    {
        string portName;
        int baudRate;
        int dataBit;
        int stopBit;
        int parity;
    } settings;
    int fd;
};

#endif

