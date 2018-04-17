# 485串口demo分析 #

## 485 recv函数 ##

函数主要语句如下,其中带标记的为485特有语句.

  1. [ ] uartFd = open(uartname, O\_RDWR|O\_NDELAY, 0);
  2. [ ] retCode = ioctl(uartFd, FIOSETOPTIONS, OPT\_LINE);
  3. [ ] retCode = ioctl(uartFd, FIOFLUSH, 0);
  4. [ ] retCode = ioctl(uartFd, SIO\_MODE\_SET, SIO\_MODE\_INT);
  5. [ ] retCode = ioctl(uartFd, FIONREAD,&count);
  6. [ ] retCode = readcnt=read(uartFd,buf,BUFFSIZE);
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

## 小结 ##

485的串口在发送数据时需要特殊设置,相关宏定义在驱动头文件xr17d15xSio.h中.
