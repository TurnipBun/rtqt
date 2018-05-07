#include "os.hpp"
#include "log.hpp"

#include "modulewidget.hpp"

ModuleWidget::ModuleWidget()
    :comm1st(NULL),comm2nd(NULL)
{
    setupUi(this);
    setEnabledAtClose();
    //连接到界面调整信号
    connect(pushOpen,SIGNAL(clicked()),this,SLOT(setEnabledAtOpen()));
    connect(pushClose,SIGNAL(clicked()),this,SLOT(setEnabledAtClose()));
    //连接线程信号
    connect(&comm1stThread,SIGNAL(started()),this,SLOT(onThreadStarted()));
    connect(&comm2ndThread,SIGNAL(started()),this,SLOT(onThreadStarted()));
    connect(&comm1stThread,SIGNAL(finished()),this,SLOT(onThreadFinished()));
    connect(&comm2ndThread,SIGNAL(finished()),this,SLOT(onThreadFinished()));
    connect(&comm1stThread,SIGNAL(dataRecved(const QString&)),this,SLOT(onComm1stRecved(const QString&)));
    connect(&comm2ndThread,SIGNAL(dataRecved(const QString&)),this,SLOT(onComm2ndRecved(const QString&)));
}

ModuleWidget::~ModuleWidget()
{

}

void ModuleWidget::showMsgBox(const QString& text)
{
    msgBox.setText(text);
    msgBox.exec();
}


void ModuleWidget::setEnabledAtOpen()
{
    pushOpen->setEnabled(false);
    groupSetting->setEnabled(false);
    
    group1st->setEnabled(true);
    group2nd->setEnabled(true);
    pushClose->setEnabled(true);
    pushAuto->setEnabled(true);
}

void ModuleWidget::setEnabledAtClose()
{
    pushOpen->setEnabled(true);
    groupSetting->setEnabled(true);
    
    group1st->setEnabled(false);
    group2nd->setEnabled(false);
    pushClose->setEnabled(false);
    pushAuto->setEnabled(false);
}


void ModuleWidget::on_pushAuto_clicked()
{
    int i;
    (*g_log)<< "auto test start..."<< ENDL;
    QProgressBar processBar;
    processBar.setMinimum(1);
    processBar.setMaximum(COMM_AUTO_TEST_NUM);
    processBar.show();
    for (i = 1; i <= COMM_AUTO_TEST_NUM; ++i)
    {
        on_pushSend1st_clicked();
        on_pushSend2nd_clicked();
        processBar.setValue(i);
    }
    
    (*g_log)<< "auto test end... " << ENDL;
}

void ModuleWidget::on_pushSend1st_clicked()
{
    int ret;
    string sendData = getTextLineSend1st();
    (*g_log)<< "comm1st sending data: " << sendData << ENDL;
    ret = comm1st->send(sendData);
    if (ret != COMM_SUC)
    {
        showMsgBox(tr("ERROR: comm1st send data failed: %1").arg(ret));
        return;
    }
    OS::wait(20);

    
    setLcdSendCount1st(comm1st->getSendCount());
    appendTextBrowserSend1st(QString::fromStdString(sendData));
    setTextLineSend1st(QString::fromStdString(OS::genVisibleString(8)));
}

void ModuleWidget::on_pushSend2nd_clicked()
{
    int ret;
    string sendData = getTextLineSend2nd();
    (*g_log)<< "comm2nd sending data: " << sendData << ENDL;
    ret = comm2nd->send(sendData);
    if (ret != COMM_SUC)
    {
        showMsgBox(tr("ERROR: comm2nd send data failed: %1").arg(ret));
        return;
    }
    OS::wait(20);

    setLcdSendCount2nd(comm2nd->getSendCount());
    appendTextBrowserSend2nd(QString::fromStdString(sendData));
    setTextLineSend2nd(QString::fromStdString(OS::genVisibleString(8)));
}
/*
void ModuleWidget::onComm1stSended()
{
    int ret;
    string recvData;
    unsigned int sendNum;
    double lostRate,erroRate;

    ret = comm2nd->recv(recvData);
    if (ret == COMM_SUC)
    {
        (*g_log)<< "comm2nd recving data: " << recvData << ENDL;
        comm1st->compare(recvData);
        setTextLineRecv2nd(recvData);

        sendNum = comm1st->getSendCount();
        lostRate = (sendNum == 0) ? 0.0 : 1 - 1.0 * comm2nd->getRecvCount() / sendNum;
        erroRate = (sendNum == 0) ? 0.0 : 1.0 * comm1st->getErroCount() / sendNum;

        setLcdSendCount1st(sendNum);
        setLcdLostRate1st(lostRate);
        setLcdErroRate1st(erroRate);
    }
    else
    {
        (*g_log)<< "comm2nd recv failed... " << ENDL;
    }
}

void ModuleWidget::onComm2ndSended()
{
    int ret;
    string recvData;
    unsigned int sendNum;
    double lostRate,erroRate;

    ret = comm1st->recv(recvData);
    if (ret == COMM_SUC)
    {
        (*g_log)<< "comm1st recving data: " << recvData << ENDL;
        comm2nd->compare(recvData);
        setTextLineRecv1st(recvData);

        sendNum = comm2nd->getSendCount();
        lostRate = (sendNum == 0) ? 0.0 : 1 - 1.0 * comm1st->getRecvCount() / sendNum;
        erroRate = (sendNum == 0) ? 0.0 : 1.0 * comm2nd->getErroCount() / sendNum;
        
        setLcdSendCount2nd(sendNum);
        setLcdLostRate2nd(lostRate);
        setLcdErroRate2nd(erroRate);
    }
}
*/

void ModuleWidget::onComm1stRecved(const QString& data)
{
    appendTextBrowserRecv1st(data);
    if (comm1st != NULL)
    {
        setLcdRecvCount1st(comm1st->getRecvCount());
    }
    const string& temp = data.toStdString();
    (*g_log)<< "comm2nd recving data: " << temp << ENDL;
}

void ModuleWidget::onComm2ndRecved(const QString& data)
{
    appendTextBrowserRecv2nd(data);
    if (comm2nd != NULL)
    {
        setLcdRecvCount2nd(comm2nd->getRecvCount());
    }
    const string& temp = data.toStdString();
    (*g_log)<< "comm2nd recving data: " << temp << ENDL;
}

void ModuleWidget::onThreadStarted()
{
     (*g_log)<< "one thread started... " << ENDL;
}

void ModuleWidget::onThreadFinished()
{
    (*g_log)<< "one thread finished... " << ENDL;
}


void ModuleWidget::clearComms()
{
    comm1stThread.stop();
    comm2ndThread.stop();
    
    if (comm1st != NULL)
    {
        comm1st->send("bye");
    }

    if (comm2nd != NULL)
    {
        comm2nd->send("bye");
    }
    
    comm1stThread.wait();
    comm2ndThread.wait();

    if (comm1st != NULL)
    {
        comm1st->close();
        delete comm1st;
        comm1st = NULL;
    }

    if (comm2nd != NULL)
    {
        comm2nd->close();
        delete comm2nd;
        comm2nd = NULL;
    }
}


void ModuleWidget::clearTextBrowsers()
{
    textSend1st->clear();
    textSend2nd->clear();
    textRecv1st->clear();
    textRecv2nd->clear();
}


