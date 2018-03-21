#include <string>
#include <cassert>
#include <QtGui>
//#include <pthread>

#include "os.hpp"
#include "mainwindow.hpp"

using std::string;

/*通道1接收*/
void *recvFirst(void *arg)
{
    int ret;
    string recvStr;
    
    MainWindow *pWin = (MainWindow *)arg;
    CAN &firstCh = *(pWin->pFirstCh);
    CAN &secondCh = *(pWin->pSecondCh);
    Log &fileLog = *(pWin->pLog);
    
    while(1)
    {
        ret = firstCh.recv();
        if (CAN_SUC == ret)
        {
            secondCh.checkMsg(firstCh.getRecvMsgRaw());//发送方检查
            
            recvStr = firstCh.getRecvMsgStr();
            pWin->lineRecvData_1->setText(QString::fromStdString(recvStr));
            fileLog << "first channel received data " << recvStr << " ..." << ENDL;
        }
    }
    pthread_exit(NULL);
}

/*通道2接收*/
void *recvSecond(void *arg)
{
    int ret;
    string recvStr;
    
    MainWindow *pWin = (MainWindow *)arg;
    CAN &firstCh = *(pWin->pFirstCh);
    CAN &secondCh = *(pWin->pSecondCh);
    Log &fileLog = *(pWin->pLog);
    
    while(1)
    {
        ret = secondCh.recv();
        if (CAN_SUC == ret)
        {
            firstCh.checkMsg(secondCh.getRecvMsgRaw());//发送方检查
            
            recvStr = secondCh.getRecvMsgStr();
            pWin->lineRecvData_2->setText(QString::fromStdString(recvStr));
            fileLog << "second channel received data " << recvStr << " ..." << ENDL;
        }
    }
    pthread_exit(NULL);
}


/*构造函数
 *1.初始化UI
 *2.创建两个CAN通道对象
 *3.创建状态栏
 */
MainWindow::MainWindow()
    :pStatusLabel(NULL), pFirstCh(NULL), pSecondCh(NULL), pFirstTh(NULL), pSecondTh(NULL), pLog(NULL)
{
	setupUi(this);
    pFirstCh = new CAN(0);
    pSecondCh = new CAN(1);
    pLog = LogFactory::getFactory()->createLog(TO_FILE);
    pLog->init();
    createStatusBar();
    (*pLog) << "init main window ..." << ENDL;
}

MainWindow::~MainWindow()
{
    (*pLog) << "destory main window ..." << ENDL;
    if (NULL != pFirstCh) delete pFirstCh;
    if (NULL != pSecondCh) delete pSecondCh;
    if (NULL != pLog) delete pLog;
}

/*打开通道*/
void MainWindow::on_pushCANOpen_clicked()
{
    bool result;
    QString devStr = comboDevIndex->currentText();
    int devNo = devStr.toInt(&result,10);
    assert(result);
    
    QString canRateStr = comboCANRate->currentText();
    int canRate = canRateStr.toInt(&result,10);
    assert(result);

    //初始化通道
    (*pLog) << "init channels ..." << ENDL;
    if (CAN_ERR == createChannels(devNo,canRate))
    {
        deleteChannels();
        updateStatus(tr("init channels failed ..."));
        return;
    }
    updateStatus(tr("init channels init success ..."));

    //创建线程
    (*pLog) << "create receive threads ..." << ENDL;
    if(CAN_ERR == createCANRecvThread())
    {
        deleteChannels();
        destoryCANRecvThread();
        updateStatus(tr("create receive threads failed ..."));
        return;
    }
    
    //更新发送数据
    string sendStr;
    sendStr = OS::randDigitString(8);
    lineSendData_1->setText(QString::fromLocal8Bit(sendStr.c_str()));
    sendStr = OS::randDigitString(8);
    lineSendData_2->setText(QString::fromLocal8Bit(sendStr.c_str()));
    
    //调整可用性
    comboDevIndex->setEnabled(false);
    comboCANRate->setEnabled(false);
    pushCANOpen->setEnabled(false);
    pushCANClose->setEnabled(true);
    groupChannel_1->setEnabled(true);
    groupChannel_2->setEnabled(true);
}

/*关闭通道*/
void MainWindow::on_pushCANClose_clicked()
{
    //销毁线程
    (*pLog) << "destory receive threads ..." << ENDL;
    destoryCANRecvThread();

    //释放CAN
    (*pLog) << "close channels ..." << ENDL;
    deleteChannels();

    //调整可用性
    comboDevIndex->setEnabled(true);
    comboCANRate->setEnabled(true);
    pushCANOpen->setEnabled(true);
    pushCANClose->setEnabled(false);
    groupChannel_1->setEnabled(false);
    groupChannel_2->setEnabled(false);
}

/*通道1发送*/
void MainWindow::on_pushSend_1_clicked()
{
    string sendStr;
    QString str = lineSendData_1->text();

    //更新统计数据，本次不计入
    Count send = pFirstCh->getSendCount();
    Count err = pFirstCh->getErrCount();
    Count recv = pSecondCh->getRecvCount();
    double lostRate = (send == 0) ? 0.0 : 1 - 1.0*recv/send;
    double errRate = (send == 0) ? 0.0 : 1.0*err/send;

    lcdSendNum_1->display(static_cast<int>(send));
    lcdLostRate_1->display(lostRate);
    lcdErrRate_1->display(errRate);

    //发送数
    (*pLog) << "first channel send data " << str.toStdString() << " ..." << ENDL;
    if (CAN_ERR == pFirstCh->send(str.toStdString()))
    {
        updateStatus(tr("first channel send data %1 failed ...").arg(str));
        return;
    }
    updateStatus(tr("first channel send data %1 success ...").arg(str));
    
    //更新发送数据
    sendStr = OS::randDigitString(8);
    lineSendData_1->setText(QString::fromLocal8Bit(sendStr.c_str()));
}

/*通道1发送*/
void MainWindow::on_pushSend_2_clicked()
{
    string sendStr;
    QString str = lineSendData_2->text();

    //更新统计数据，本次不计入
    Count send = pSecondCh->getSendCount();
    Count err = pSecondCh->getErrCount();
    Count recv = pFirstCh->getRecvCount();
    double lostRate = (send == 0) ? 0 : 1 - 1.0*recv/send;
    double errRate = (send == 0) ? 0 : 1.0*err/send;
    
    lcdSendNum_2->display(static_cast<int>(send));
    lcdLostRate_2->display(lostRate);
    lcdErrRate_2->display(errRate);

    //发送数据
    (*pLog) << "second channel send data " << str.toStdString() << " ..." << ENDL;
    if (CAN_ERR == pSecondCh->send(str.toStdString()))
    {
        updateStatus(tr("second channel send data %1 failed ...").arg(str));
        return;
    }
    updateStatus(tr("send data %1 success ...").arg(str));
    
    //更新发送数据
    sendStr = OS::randDigitString(8);
    lineSendData_2->setText(QString::fromLocal8Bit(sendStr.c_str()));
}

/*创建状态栏*/
void MainWindow::createStatusBar()
{
    pStatusLabel = new QLabel(tr("windows initialized success ..."));
    pStatusLabel->setAlignment(Qt::AlignHCenter);

    statusBar()->addWidget(pStatusLabel);
}

/*更新状态栏*/
void MainWindow::updateStatus(const QString &text)
{
    pStatusLabel->setText(text);
}

int MainWindow::createChannels(int devNo, int canRate)
{
    //初始化通道1
    if (pFirstCh != NULL)
        delete pFirstCh;
    pFirstCh = new CAN(devNo*2);
    if (CAN_ERR == pFirstCh->init(canRate))
    {
        return CAN_ERR;
    }
    pFirstCh->setMsgHead();
    
    //初始化通道2
    if (pSecondCh != NULL)
        delete pSecondCh;
    pSecondCh = new CAN(devNo*2+1);

    if (CAN_ERR == pSecondCh->init(canRate))
    {
        return CAN_ERR;
    }
    pSecondCh->setMsgHead();

    return CAN_SUC;
}


void MainWindow::deleteChannels()
{
    if (pFirstCh != NULL)
    {
        delete pFirstCh;
        pFirstCh = NULL;
    }
    
    if (pSecondCh != NULL)
    {
        delete pSecondCh;
        pSecondCh = NULL;
    }
}


int MainWindow::createCANRecvThread()
{
    int rc;

    pFirstTh = new pthread_t;
    rc = pthread_create(pFirstTh, NULL, recvFirst, (void *)this);
    if (rc) return CAN_ERR;
    
    rc = pthread_detach(*pFirstTh);
    if (rc) return CAN_ERR;

    pSecondTh = new pthread_t;
    rc = pthread_create(pSecondTh, NULL, recvSecond, (void *)this);
    if (rc) return CAN_ERR;
    
    rc = pthread_detach(*pSecondTh);
    if (rc) return CAN_ERR;
    
    return CAN_SUC;
}

void MainWindow::destoryCANRecvThread()
{
    if (pFirstTh != NULL)
    {
        pthread_cancel(*pFirstTh);
        delete pFirstTh;
        pFirstTh = NULL;
    }
    
    if (pSecondTh != NULL)
    {
        pthread_cancel(*pSecondTh);
        delete pSecondTh;
        pSecondTh = NULL;
    }
}


