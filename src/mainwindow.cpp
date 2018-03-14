#include <string>
#include <cassert>
#include <QtGui>
//#include <pthread>

#include "os.hpp"
#include "mainwindow.hpp"

using std::string;

void *recvFirst(void *arg)
{
    int ret;
    MainWindow *pWin = (MainWindow *)arg;
    string recvStr;
    while(1)
    {
        ret = pWin->pFirstCh->recv();
        if (CAN_SUC == ret)
        {
            recvStr = pWin->pFirstCh->getRecvMsg();
            pWin->lineRecvData_1->setText(QString::fromStdString(recvStr));
            //pWin->lineRecvData_1->setText(QString::fromStdString("stub"));
            OS::addLog("receive data from first channel", false);
            OS::addLog(recvStr);
        }
        else OS::addLog("receive data from first channel failed ...");
    }
    pthread_exit(NULL);
}

void *recvSecond(void *arg)
{
    int ret;
    MainWindow *pWin = (MainWindow *)arg;
    string recvStr;
    while(1)
    {
        ret = pWin->pSecondCh->recv();
        if (CAN_SUC == ret)
        {
            recvStr = pWin->pSecondCh->getRecvMsg();
            pWin->lineRecvData_2->setText(QString::fromStdString(recvStr));
            //pWin->lineRecvData_2->setText(QString::fromStdString("stub"));
            OS::addLog("receive data from second channel", false);
            OS::addLog(recvStr);
        }
        else OS::addLog("receive data from second channel failed ...");
    }
    pthread_exit(NULL);
}


/*构造函数
 *1.初始化UI
 *2.创建两个CAN通道对象
 *3.创建状态栏
 */
MainWindow::MainWindow()
    :pStatusLabel(NULL), pFirstCh(NULL), pSecondCh(NULL), pFirstTh(NULL), pSecondTh(NULL)
{
	setupUi(this);
    pFirstCh = new CAN(0);
    pSecondCh = new CAN(1);
    createStatusBar();
}

/*下拉框变化时重新创建通道*/
void MainWindow::on_comboDevIndex_currentIndexChanged(const QString &text)
{
    bool result;
    int devNo = text.toInt(&result,10);
    assert(result);
    if (pFirstCh != NULL)
    {
        delete pFirstCh;
    }
    if (pSecondCh != NULL)
    {
        delete pSecondCh;
    }
    pFirstCh = new CAN(devNo*2);
    pSecondCh = new CAN(devNo*2+1);
    updateStatus(tr("current device id is %1").arg(devNo));
}

/*打开通道*/
void MainWindow::on_pushCANOpen_clicked()
{
    //更新发送数据
    string sendStr;
    sendStr = OS::randDigitString(8);
    lineSendData_1->setText(QString::fromLocal8Bit(sendStr.c_str()));
    sendStr = OS::randDigitString(8);
    lineSendData_2->setText(QString::fromLocal8Bit(sendStr.c_str()));
    
    if (CAN_ERR == pFirstCh->init(0x2000))
    {
        updateStatus(tr("channel %1 init failed ...").arg(pFirstCh->getChannel()));
        return;
    }
    if (CAN_ERR == pSecondCh->init(0x4000))
    {
        updateStatus(tr("channel %1 init failed ...").arg(pSecondCh->getChannel()));
        return;
    }
    updateStatus(tr("all channel init success ..."));
    
    pFirstCh->setSendMsgHead(0x2);
    pSecondCh->setSendMsgHead(0x1);

    comboDevIndex->setEnabled(false);
    pushCANOpen->setEnabled(false);
    pushCANClose->setEnabled(true);
    groupChannel_1->setEnabled(true);
    groupChannel_2->setEnabled(true);

    createCANRecvThread();
}

/*关闭通道*/
void MainWindow::on_pushCANClose_clicked()
{
    pFirstCh->close();
    pSecondCh->close();

    comboDevIndex->setEnabled(true);
    pushCANOpen->setEnabled(true);
    pushCANClose->setEnabled(false);
    groupChannel_1->setEnabled(false);
    groupChannel_2->setEnabled(false);

    /*确认线程是否创建*/
    destoryCANRecvThread();
}

/*通道1发送*/
void MainWindow::on_pushSend_1_clicked()
{
    string sendStr;
    QString str = lineSendData_1->text();
    if (CAN_ERR == pFirstCh->send(str.toStdString()))
    {
        updateStatus(tr("send data %1 failed ...").arg(str));
        return;
    }
    updateStatus(tr("send data %1 success ...").arg(str));
    //更新发送数据
    sendStr = OS::randDigitString(8);
    lineSendData_1->setText(QString::fromLocal8Bit(sendStr.c_str()));
}

/*通道1发送*/
void MainWindow::on_pushSend_2_clicked()
{
    string sendStr;
    QString str = lineSendData_2->text();
    if (CAN_ERR == pSecondCh->send(str.toStdString()))
    {
        updateStatus(tr("send data %1 failed ...").arg(str));
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
    pStatusLabel = new QLabel(tr("windows initialized ok ..."));
    pStatusLabel->setAlignment(Qt::AlignHCenter);

    statusBar()->addWidget(pStatusLabel);
}

/*更新状态栏*/
void MainWindow::updateStatus(const QString &text)
{
    pStatusLabel->setText(text);
}

int MainWindow::createCANRecvThread()
{
    pFirstTh = new pthread_t;
    pthread_create(pFirstTh, NULL, recvFirst, (void *)this);
    pthread_detach(*pFirstTh);

    pSecondTh = new pthread_t;
    pthread_create(pSecondTh, NULL, recvSecond, (void *)this);
    pthread_detach(*pSecondTh);
    return 0;
}

int MainWindow::destoryCANRecvThread()
{
    pthread_cancel(*pFirstTh);
    pthread_cancel(*pSecondTh);
    return 0;
}


