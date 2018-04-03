#include <string>
#include <cassert>
#include <QtGui>

#include "os.hpp"
#include "mainwindow.hpp"

using std::string;

/*通道1接收*/
void *canRecv1(void *arg)
{
    int ret;
    string recvStr;
    MainWindow *pWin = (MainWindow *)arg;
    Log &fileLog = *(pWin->pLog);
    
    while(1)
    {
        CAN *ch1 = pWin->pCan1;
        CAN *ch2 = pWin->pCan2;
        if (ch1 == NULL || ch2 == NULL) break;
        ret = ch1->recv();
        if (CAN_SUC == ret)
        {
            ch2->checkMsg(ch1->getRecvMsgRaw());//发送方检查
            recvStr = ch1->getRecvMsgStr();
            pWin->lineRecvData_1->setText(QString::fromStdString(recvStr));
            fileLog << "first channel received data " << recvStr << " ..." << ENDL;
        }
    }
    pthread_exit(NULL);
    return NULL;
}

/*通道2接收*/
void *canRecv2(void *arg)
{
    int ret;
    string recvStr;
    MainWindow *pWin = (MainWindow *)arg;
    Log &fileLog = *(pWin->pLog);
    
    
    while(1)
    {
        
        CAN *ch1 = pWin->pCan1;
        CAN *ch2 = pWin->pCan2;
        if (ch1 == NULL || ch2 == NULL) break;
        ret = ch2->recv();
        if (CAN_SUC == ret)
        {
            ch1->checkMsg(ch2->getRecvMsgRaw());//发送方检查
            recvStr = ch2->getRecvMsgStr();
            pWin->lineRecvData_2->setText(QString::fromStdString(recvStr));
            fileLog << "second channel received data " << recvStr << " ..." << ENDL;
        }
    }
    pthread_exit(NULL);
    return NULL;
}

void *comRecv1(void *arg)
{
    int ret;
    const char * pRecv;
    MainWindow *pWin = (MainWindow *)arg;
    Log &fileLog = *(pWin->pLog);
    
    while(1)
    {
        COM *thisCom = pWin->pCom1;
        COM *sendCom = pWin->pCom2;
        if (thisCom == NULL || sendCom == NULL) break;
        ret = thisCom->recv();
        if (COM_SUC == ret)
        {
            pRecv = thisCom->getRecvData();
            sendCom->compare(pRecv);
            pWin->lineCOMRecvData1->setText(QString::fromStdString(pRecv));
            fileLog << "first com received data " << pRecv << " ..." << ENDL;
        }
        OS::wait(1);
    }
    pthread_exit(NULL);
    return NULL;
}

void *comRecv2(void *arg)
{
    int ret;
    const char * pRecv;
    MainWindow *pWin = (MainWindow *)arg;
    Log &fileLog = *(pWin->pLog);
    
    while(1)
    {
        COM *thisCom = pWin->pCom2;
        COM *sendCom = pWin->pCom1;
        if (thisCom == NULL || sendCom == NULL) break;
        ret = thisCom->recv();
        if (COM_SUC == ret)
        {
            pRecv = thisCom->getRecvData();
            sendCom->compare(pRecv);
            fileLog << "second com received data " << pRecv << " ..." << ENDL;
            pWin->lineCOMRecvData2->setText(QString::fromStdString(pRecv));
        }
        OS::wait(1);
    }
    pthread_exit(NULL);
    return NULL;
}

MainWindow::MainWindow()
    :pStatusLabel(NULL), pLog(NULL), pCan1(NULL), pCan2(NULL), pCom1(NULL), pCom2(NULL),
     pCanTh1(NULL), pCanTh2(NULL), pComTh1(NULL), pComTh2(NULL)
{
    
    pLog = LogFactory::getFactory()->createLog(TO_FILE);
    pLog->init();
    (*pLog) << "init main window ..." << ENDL;
    
	setupUi(this);
    createStatusBar();
}

MainWindow::~MainWindow()
{
    (*pLog) << "destory main window ..." << ENDL;
    
    destoryCANRecvThread();
    deleteCAN();

    destoryCOMRecvThread();
    deleteCOM();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 1)
    {
        comboCOMName1->clear();
        comboCOMName2->clear();
        
#ifdef VXWORKS

#else
        GetComList & getList = *(new GetWinComList);
#endif

        list<string> & comList = getList();
        while (!comList.empty())
        {
            const string & comName = comList.front();
            comboCOMName1->addItem(tr(comName.c_str()));
            comboCOMName2->addItem(tr(comName.c_str()));
            comList.pop_front();
        }
    }
}

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
    if (CAN_ERR == createCAN(devNo,canRate))
    {
        deleteCAN();
        updateStatus(tr("init channels failed ..."));
        return;
    }
    updateStatus(tr("init channels init success ..."));

    //创建线程
    (*pLog) << "create receive threads ..." << ENDL;
    if(CAN_ERR == createCANRecvThread())
    {
        deleteCAN();
        destoryCANRecvThread();
        updateStatus(tr("create receive threads failed ..."));
        return;
    }
    
    //更新发送数据
    string sendStr;
    sendStr = OS::genVisibleString(8);
    lineSendData_1->setText(QString::fromStdString(sendStr));
    sendStr = OS::genVisibleString(8);
    lineSendData_2->setText(QString::fromStdString(sendStr));
    
    //调整可用性
    comboDevIndex->setEnabled(false);
    comboCANRate->setEnabled(false);
    pushCANOpen->setEnabled(false);
    pushCANClose->setEnabled(true);
    groupChannel_1->setEnabled(true);
    groupChannel_2->setEnabled(true);
}


void MainWindow::on_pushCANClose_clicked()
{
    //销毁线程
    (*pLog) << "destory receive threads ..." << ENDL;
    destoryCANRecvThread();

    OS::wait(2);

    //释放CAN
    (*pLog) << "close channels ..." << ENDL;
    deleteCAN();

    //调整可用性
    comboDevIndex->setEnabled(true);
    comboCANRate->setEnabled(true);
    pushCANOpen->setEnabled(true);
    pushCANClose->setEnabled(false);
    groupChannel_1->setEnabled(false);
    groupChannel_2->setEnabled(false);
}

void MainWindow::on_pushCANSend1_clicked()
{
    string sendStr;
    QString str = lineSendData_1->text();

    //更新统计数据，本次不计入
    Count send = pCan1->getSendCount();
    Count err = pCan1->getErrCount();
    Count recv = pCan2->getRecvCount();
    double lostRate = (send == 0) ? 0.0 : 1 - 1.0*recv/send;
    double errRate = (send == 0) ? 0.0 : 1.0*err/send;

    lcdSendNum_1->display(static_cast<int>(send));
    lcdLostRate_1->display(lostRate);
    lcdErrRate_1->display(errRate);

    //发送数
    (*pLog) << "first channel send data " << str.toStdString() << " ..." << ENDL;
    if (CAN_ERR == pCan1->send(str.toStdString()))
    {
        updateStatus(tr("first channel send data %1 failed ...").arg(str));
        return;
    }
    updateStatus(tr("first channel send data %1 success ...").arg(str));
    
    //更新发送数据
    sendStr = OS::genVisibleString(8);
    lineSendData_1->setText(QString::fromStdString(sendStr));
}

/*通道1发送*/
void MainWindow::on_pushCANSend2_clicked()
{
    string sendStr;
    QString str = lineSendData_2->text();

    //更新统计数据，本次不计入
    Count send = pCan2->getSendCount();
    Count err = pCan2->getErrCount();
    Count recv = pCan1->getRecvCount();
    double lostRate = (send == 0) ? 0 : 1 - 1.0*recv/send;
    double errRate = (send == 0) ? 0 : 1.0*err/send;
    
    lcdSendNum_2->display(static_cast<int>(send));
    lcdLostRate_2->display(lostRate);
    lcdErrRate_2->display(errRate);

    //发送数据
    (*pLog) << "second channel send data " << str.toStdString() << " ..." << ENDL;
    if (CAN_ERR == pCan2->send(str.toStdString()))
    {
        updateStatus(tr("second channel send data %1 failed ...").arg(str));
        return;
    }
    updateStatus(tr("send data %1 success ...").arg(str));
    
    //更新发送数据
    sendStr = OS::genVisibleString(8);
    lineSendData_2->setText(QString::fromStdString(sendStr));
}

int MainWindow::createCAN(int devNo, int canRate)
{
    //初始化通道1
    if (pCan1 != NULL)
        delete pCan1;
    pCan1 = new CAN(devNo*2);
    if (CAN_ERR == pCan1->init(canRate))
    {
        return CAN_ERR;
    }
    pCan1->setMsgHead();
    
    //初始化通道2
    if (pCan2 != NULL)
        delete pCan2;
    pCan2 = new CAN(devNo*2+1);

    if (CAN_ERR == pCan2->init(canRate))
    {
        return CAN_ERR;
    }
    pCan2->setMsgHead();

    return CAN_SUC;
}


void MainWindow::deleteCAN()
{
    if (pCan1 != NULL)
    {
        delete pCan1;
        pCan1 = NULL;
    }
    
    if (pCan2 != NULL)
    {
        delete pCan2;
        pCan2 = NULL;
    }
}


int MainWindow::createCANRecvThread()
{
    int rc;

    pCanTh1 = new pthread_t;
    rc = pthread_create(pCanTh1, NULL, canRecv1, (void *)this);
    if (rc) return CAN_ERR;
    rc = pthread_detach(*pCanTh1);
    if (rc) return CAN_ERR;

    pCanTh2 = new pthread_t;
    rc = pthread_create(pCanTh2, NULL, canRecv2, (void *)this);
    if (rc) return CAN_ERR;
    rc = pthread_detach(*pCanTh2);
    if (rc) return CAN_ERR;
    
    return CAN_SUC;
}

void MainWindow::destoryCANRecvThread()
{
    if (pCanTh1 != NULL)
    {
        pthread_cancel(*pCanTh1);
        delete pCanTh1;
        pCanTh1 = NULL;
    }
    
    if (pCanTh2 != NULL)
    {
        pthread_cancel(*pCanTh2);
        delete pCanTh2;
        pCanTh2 = NULL;
    }
}


void MainWindow::on_pushCOMOpen_clicked()
{
    int ret;
    ret = createCOM();
    if (ret != COM_SUC)
    {
        deleteCOM();
        updateStatus(tr("open coms failed ..."));
        return;
    }

    ret = createCOMRecvThread();
    if (ret != COM_SUC)
    {
        destoryCOMRecvThread();
        deleteCOM();
        updateStatus(tr("create com receive threads failed ..."));
        return;
    }
    
    string sendStr;
    sendStr = OS::genVisibleString(8);
    lineCOMSendData1->setText(QString::fromStdString(sendStr));
    sendStr = OS::genVisibleString(8);
    lineCOMSendData2->setText(QString::fromStdString(sendStr));
    
    pushCOMClose->setEnabled(true);
    groupCOM1->setEnabled(true);
    groupCOM2->setEnabled(true);
    
    pushCOMOpen->setEnabled(false);
    comboCOMName1->setEnabled(false);
    comboCOMName2->setEnabled(false);
    comboRate->setEnabled(false);
    comboDataBit->setEnabled(false);
    comboStopBit->setEnabled(false);
    comboParity->setEnabled(false);
}

void MainWindow::on_pushCOMClose_clicked()
{
    (*pLog) << "destory receive threads ..." << ENDL;
    destoryCOMRecvThread();
    OS::wait(2);
    (*pLog) << "delete coms ..." << ENDL;
    deleteCOM();

    pushCOMClose->setEnabled(false);
    groupCOM1->setEnabled(false);
    groupCOM2->setEnabled(false);
    
    pushCOMOpen->setEnabled(true);
    comboCOMName1->setEnabled(true);
    comboCOMName2->setEnabled(true);
    comboRate->setEnabled(true);
    comboDataBit->setEnabled(true);
    comboStopBit->setEnabled(true);
    comboParity->setEnabled(true);
}

void MainWindow::on_pushCOMSend1_clicked()
{
    
    QString qstrSend = lineCOMSendData1->text();
    string strSend = qstrSend.toStdString();

    //更新统计数据，本次不计入
    Count send = pCom1->getSendCount();
    Count err = pCom1->getErrCount();
    Count recv = pCom2->getRecvCount();
    double lostRate = (send == 0) ? 0.0 : 1 - 1.0*recv/send;
    double errRate = (send == 0) ? 0.0 : 1.0*err/send;

    lcdCOMSendNum1->display(static_cast<int>(send));
    lcdCOMLostRate1->display(lostRate);
    lcdCOMErrRate1->display(errRate);

    //发送数
    (*pLog) << "first com send data " << strSend << " ..." << ENDL;
    if (COM_ERR == pCom1->send(strSend.c_str(),strlen(strSend.c_str())))
    {
        updateStatus(tr("first com send data %1 failed ...").arg(qstrSend));
        return;
    }

    lineCOMSendData1->setText(QString::fromStdString(OS::genVisibleString(8)));

}

void MainWindow::on_pushCOMSend2_clicked()
{
    QString qstrSend = lineCOMSendData2->text();
    string strSend = qstrSend.toStdString();

    //更新统计数据，本次不计入
    Count send = pCom2->getSendCount();
    Count err = pCom2->getErrCount();
    Count recv = pCom1->getRecvCount();
    double lostRate = (send == 0) ? 0.0 : 1 - 1.0*recv/send;
    double errRate = (send == 0) ? 0.0 : 1.0*err/send;

    lcdCOMSendNum2->display(static_cast<int>(send));
    lcdCOMLostRate2->display(lostRate);
    lcdCOMErrRate2->display(errRate);

    //发送数
    (*pLog) << "second com send data " << strSend << " ..." << ENDL;
    if (COM_ERR == pCom2->send(strSend.c_str(),strlen(strSend.c_str())))
    {
        updateStatus(tr("second com send data %1 failed ...").arg(qstrSend));
        return;
    }

    lineCOMSendData2->setText(QString::fromStdString(OS::genVisibleString(8)));
}

/*更新状态栏*/
void MainWindow::updateStatus(const QString &text)
{
    pStatusLabel->setText(text);
}

int MainWindow::createCOM()
{
    string com1 = comboCOMName1->currentText().toStdString();
    string com2 = comboCOMName2->currentText().toStdString();
    if (com1 == com2)
    {
        updateStatus(tr("open coms failed, two com ports cannot be the same ..."));
        return COM_ERR;
    }

    string strBaudRate = comboRate->currentText().toStdString();
    string strDataBit = comboDataBit->currentText().toStdString();
    string strStopBit = comboStopBit->currentText().toStdString();
    string strParity = comboParity->currentText().toStdString();
    
#ifdef VXWORKS

#else
    pCom1 = new WinCom(com1, strBaudRate, strDataBit, strStopBit, strParity);
    pCom2 = new WinCom(com2, strBaudRate, strDataBit, strStopBit, strParity);
#endif
    int ret1 = pCom1->init();
    int ret2 = pCom2->init();
    if (ret1 == COM_SUC && ret2 == COM_SUC) return COM_SUC;
    return COM_ERR;
}

void MainWindow::deleteCOM()
{
    if (pCom1 != NULL)
    {
        delete pCom1;
        pCom1 = NULL;
    }
    
    if (pCom2 != NULL)
    {
        delete pCom2;
        pCom2 = NULL;
    }
}

int MainWindow::createCOMRecvThread()
{
    int rc;

    pComTh1 = new pthread_t;
    rc = pthread_create(pComTh1, NULL, comRecv1, (void *)this);
    if (rc) return COM_ERR;
    rc = pthread_detach(*pComTh1);
    if (rc) return COM_ERR;

    pComTh2 = new pthread_t;
    rc = pthread_create(pComTh2, NULL, comRecv2, (void *)this);
    if (rc) return COM_ERR;
    rc = pthread_detach(*pComTh2);
    if (rc) return COM_ERR;
    
    return COM_SUC;
}

void MainWindow::destoryCOMRecvThread()
{
    if (pComTh1 != NULL)
    {
        pthread_cancel(*pComTh1);
        delete pComTh1;
        pComTh1 = NULL;
    }
    
    if (pComTh2 != NULL)
    {
        pthread_cancel(*pComTh2);
        delete pComTh2;
        pComTh2 = NULL;
    }
}


/*创建状态栏*/
void MainWindow::createStatusBar()
{
    pStatusLabel = new QLabel(tr("windows initialized success ..."));
    pStatusLabel->setAlignment(Qt::AlignHCenter);

    statusBar()->addWidget(pStatusLabel);
}

