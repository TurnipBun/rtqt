#ifndef _VXCOM_HPP_
#define _VXCOM_HPP_
#include <list>
using std::list;
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


class VxCom
{
public:
    VxCom(){}
    ~VxCom(){}

private:
    //TODO1:提供一个获取支持配置的接口供界面进行初始化
    //TODO2:设置swOpts成员变量
    //TODO3:提供操作swOpts成员变量的接口(CSX,STOPB,PARENB,PARODD)
};

#endif

