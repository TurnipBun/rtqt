#include "os.hpp"
#include "log.hpp"

#include "modulewidget.hpp"

ModuleWidget::ModuleWidget()
    :comm1st(NULL),comm2nd(NULL)
{
    setupUi(this);
    setEnabledAtClose();
    //连接到界面调整槽
    connect(pushOpen,SIGNAL(clicked()),this,SLOT(setEnabledAtOpen()));
    connect(pushClose,SIGNAL(clicked()),this,SLOT(setEnabledAtClose()));
    //连接到新定义的信号
    connect(pushOpen,SIGNAL(clicked()),this,SIGNAL(pushOpenClicked()));
    connect(pushClose,SIGNAL(clicked()),this,SIGNAL(pushCloseClicked()));
    connect(pushAuto,SIGNAL(clicked()),this,SIGNAL(pushAutoClicked()));
    connect(pushSend1st,SIGNAL(clicked()),this,SIGNAL(pushSend1stClicked()));
    connect(pushSend2nd,SIGNAL(clicked()),this,SIGNAL(pushSend2ndClicked()));
    //新信号连接到槽
    connect(this,SIGNAL(pushCloseClicked()),this,SLOT(onPushCloseClicked()));
    connect(this,SIGNAL(pushAutoClicked()),this,SLOT(onPushAutoClicked()));
    connect(this,SIGNAL(pushSend1stClicked()),this,SLOT(onPushSend1stClicked()));
    connect(this,SIGNAL(pushSend2ndClicked()),this,SLOT(onPushSend2ndClicked()));
    //触发接收动作
    connect(this,SIGNAL(comm1stSended()),this,SLOT(onComm1stSended()));
    connect(this,SIGNAL(comm2ndSended()),this,SLOT(onComm2ndSended()));
}

ModuleWidget::~ModuleWidget()
{
}

string ModuleWidget::getTextLineSend1st()
{
    return lineSend1st->text().toStdString();
}
string ModuleWidget::getTextLineSend2nd()
{
    return lineSend2nd->text().toStdString();
}
string ModuleWidget::getTextLineRecv1st()
{
    return lineRecv1st->text().toStdString();
}
string ModuleWidget::getTextLineRecv2nd()
{
    return lineRecv2nd->text().toStdString();
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

void ModuleWidget::setTextLineSend1st(const string& text)
{
    lineSend1st->setText(QString::fromStdString(text));
}
void ModuleWidget::setTextLineSend2nd(const string& text)
{
    lineSend2nd->setText(QString::fromStdString(text));
}
void ModuleWidget::setTextLineRecv1st(const string& text)
{
    lineRecv1st->setText(QString::fromStdString(text));
}
void ModuleWidget::setTextLineRecv2nd(const string& text)
{
    lineRecv2nd->setText(QString::fromStdString(text));
}

void ModuleWidget::setLcdSendCount1st(int count)
{
    lcdSendCount1st->display(count);
}
void ModuleWidget::setLcdSendCount2nd(int count)
{
    lcdSendCount2nd->display(count);
}
void ModuleWidget::setLcdLostRate1st(double rate)
{
    lcdLostRate1st->display(rate);   
}
void ModuleWidget::setLcdLostRate2nd(double rate)
{
    lcdLostRate2nd->display(rate);
}
void ModuleWidget::setLcdErroRate1st(double rate)
{
    lcdErrorRate1st->display(rate);
}
void ModuleWidget::setLcdErroRate2nd(double rate)
{
    lcdErrorRate2nd->display(rate);
}

void ModuleWidget::onPushCloseClicked()
{
    clearComms();
}

void ModuleWidget::onPushAutoClicked()
{
    int i;
    (*g_log)<< "auto test start..."<< ENDL;
    QProgressBar processBar;
    processBar.setMinimum(1);
    processBar.setMaximum(COMM_AUTO_TEST_NUM);
    processBar.show();
    for (i = 1; i <= COMM_AUTO_TEST_NUM; ++i)
    {
        emit pushSend1stClicked();
        emit pushSend2ndClicked();
        processBar.setValue(i);
    }
    
    (*g_log)<< "auto test end... " << ENDL;
}

void ModuleWidget::onPushSend1stClicked()
{
    int ret;
    string sendData = getTextLineSend1st();
    (*g_log)<< "comm1st sending data: " << sendData << ENDL;
    ret = comm1st->send(sendData);
    if (ret != COMM_SUC)
    {
        msgBox.setText(tr("ERROR: comm1st send data failed: %1").arg(ret));
        msgBox.exec();
        return;
    }
    OS::wait(20);

    emit comm1stSended();
    setTextLineSend1st(OS::genVisibleString(8));
}

void ModuleWidget::onPushSend2ndClicked()
{
    int ret;
    string sendData = getTextLineSend2nd();
    (*g_log)<< "comm2nd sending data: " << sendData << ENDL;
    ret = comm2nd->send(sendData);
    if (ret != COMM_SUC)
    {
        msgBox.setText(tr("ERROR: comm2nd send data failed: %1").arg(ret));
        msgBox.exec();
        return;
    }
    OS::wait(20);
    
    emit comm2ndSended();
    setTextLineSend2nd(OS::genVisibleString(8));
}

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
    (*g_log)<< "comm2nd recv failed... " << ENDL;
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

void ModuleWidget::clearComms()
{
    comm1st->close();
    comm2nd->close();
    if (comm1st != NULL)
    {
        delete comm1st;
        comm1st = NULL;
    }

    if (comm2nd != NULL)
    {
        delete comm2nd;
        comm2nd = NULL;
    }
}

