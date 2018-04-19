# 485串口demo分析 #

## 485 recv函数 ##

函数主要语句如下,其中带标记的为485特有语句.

  1. [ ] uartFd = open(uartname, O\_RDWR|O\_NDELAY, 0);
  2. [ ] retCode = ioctl(uartFd, FIOSETOPTIONS, OPT\_LINE);
  3. [ ] retCode = ioctl(uartFd, FIOFLUSH, 0);
  4. [ ] retCode = ioctl(uartFd, SIO\_MODE\_SET, SIO\_MODE\_INT);
  5. [ ] retCode = ioctl(uartFd, FIONREAD,&count);
  6. [ ] readcnt=read(uartFd,buf,BUFFSIZE);
  7. [ ] close(uartFd);

## 485 send函数 ##

函数主要语句如下,其中带标记的为485特有语句.

  1. [ ] uartFd = open(uartname, O\_RDWR, 0);
  2. [ ] retCode = ioctl(uartFd, SIO\_MODE\_GET, &mode);
  3. [ ] retCode = ioctl(uartFd, FIOSETOPTIONS, OPT\_RAW);
  4. [x] retCode = ioctl(uartFd, SIO_RS485, 1);
  5. [ ] retCode = ioctl(uartFd, FIOFLUSH, 0);
  6. [ ] write(uartFd, buff, 41);
  7. [ ] close(uartFd);

## 当前代码中的读串口过程 ##

操作过程的主要语句如下,其中带标记的为与demo不同的语句.

  1. [ ] fd = ::open(settings.portName.c\_str(),O\_RDWR,0);
  2. [ ] retCode = ::ioctl(fd,FIOSETOPTIONS,OPT\_RAW);
  3. [x] retCode = ::ioctl(fd,FIOBAUDRATE, settings.baudRate);
  4. [x] retCode = ::ioctl(fd,SIO\_HW\_OPTS\_SET,(CLOCAL|CREAD|settings.dataBit)&~(HUPCL|settings.stopBit|settings.parity);
  5. [ ] retCode = ::ioctl(fd,FIOFLUSH,0);
  6. [ ] retCode = ::ioctl(fd,FIONREAD,&count);
  7. [ ] ret = ::read(fd,readBuf,COMMBUF\_LEN);
  8. [ ] ::close(fd);

## 小结 ##

485的串口在发送数据时需要特殊设置,相关宏定义在驱动头文件xr17d15xSio.h中.demo中的代码没有对波特率,数据位数等常规参数的配置.
