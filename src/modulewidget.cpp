#include "os.hpp"
#include "log.hpp"

#include "modulewidget.hpp"
#include "os.hpp"

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
    connect(&comm1stThread,SIGNAL(dataRecved(double, const QString&)),this,SLOT(onComm1stRecved(double, const QString&)));
    connect(&comm2ndThread,SIGNAL(dataRecved(double, const QString&)),this,SLOT(onComm2ndRecved(double, const QString&)));
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
    pushAuto12->setEnabled(true);
    pushAuto21->setEnabled(true);
}

void ModuleWidget::setEnabledAtClose()
{
    pushOpen->setEnabled(true);
    groupSetting->setEnabled(true);
    
    group1st->setEnabled(false);
    group2nd->setEnabled(false);
    pushClose->setEnabled(false);
    pushAuto12->setEnabled(false);
    pushAuto21->setEnabled(false);
}


void ModuleWidget::on_pushAuto12_clicked()
{
    int i;
    QProgressBar processBar;
    comm2ndThread.recordTime(true);
    (*g_log)<< "auto test start..."<< ENDL;
    processBar.setMinimum(1);
    processBar.setMaximum(COMM_AUTO_TEST_NUM);
    processBar.show();
    for (i = 1; i <= COMM_AUTO_TEST_NUM; ++i)
    {
        on_pushSend1st_clicked();
        processBar.setValue(i);
    }
    showMsgBox(tr("max interval %1").arg(comm2ndThread.getMaxInterval(),0,'f',6));
    (*g_log)<< "auto test end... " << ENDL;
    comm2ndThread.recordTime(false);
}

void ModuleWidget::on_pushAuto21_clicked()
{
    int i;
    QProgressBar processBar;
    comm1stThread.recordTime(true);
    (*g_log)<< "auto test start..."<< ENDL;
    processBar.setMinimum(1);
    processBar.setMaximum(COMM_AUTO_TEST_NUM);
    processBar.show();
    for (i = 1; i <= COMM_AUTO_TEST_NUM; ++i)
    {
        on_pushSend2nd_clicked();
        processBar.setValue(i);
    }
    showMsgBox(tr("max interval %1").arg(comm1stThread.getMaxInterval(),0,'f',6));
    (*g_log)<< "auto test end... " << ENDL;
    comm1stThread.recordTime(false);
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
    OS::wait(1);

    
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
    OS::wait(1);

    setLcdSendCount2nd(comm2nd->getSendCount());
    appendTextBrowserSend2nd(QString::fromStdString(sendData));
    setTextLineSend2nd(QString::fromStdString(OS::genVisibleString(8)));
}

void ModuleWidget::onComm1stRecved(double timestamp, const QString& data)
{
    appendTextBrowserRecv1st(tr("[%1] %2 ").arg(timestamp, 0,'f',6).arg(data));
    if (comm1st != NULL)
    {
        setLcdRecvCount1st(comm1st->getRecvCount());
    }
    const string& temp = data.toStdString();
    (*g_log)<< "comm1st recving data: " << temp << ENDL;
}

void ModuleWidget::onComm2ndRecved(double timestamp, const QString& data)
{
    appendTextBrowserRecv2nd(tr("[%1] %2 ").arg(timestamp, 0,'f',6).arg(data));
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


