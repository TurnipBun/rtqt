#include "os.hpp"
#include "log.hpp"

#include "modulewidget.hpp"
#include "os.hpp"

ModuleWidget::ModuleWidget()
    :commReceiver(NULL),commSender(NULL)
{
    setupUi(this);
    setEnabledAtClose();
    //连接到界面调整信号
    connect(pushOpen,SIGNAL(clicked()),this,SLOT(setEnabledAtOpen()));
    connect(pushClose,SIGNAL(clicked()),this,SLOT(setEnabledAtClose()));
    //连接线程信号
    connect(&commRecvThread,SIGNAL(started()),this,SLOT(onThreadStarted()));
    connect(&commRecvThread,SIGNAL(finished()),this,SLOT(onThreadFinished()));
    connect(&commRecvThread,SIGNAL(dataRecved(double, const QString&)),this,SLOT(onCommRecved(double, const QString&)));
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
    
    groupRecv->setEnabled(true);
    groupSend->setEnabled(true);
    pushClose->setEnabled(true);
}

void ModuleWidget::setEnabledAtClose()
{
    pushOpen->setEnabled(true);
    groupSetting->setEnabled(true);
    
    groupRecv->setEnabled(false);
    groupSend->setEnabled(false);
    pushClose->setEnabled(false);
}


void ModuleWidget::on_pushAutoSend_clicked()
{
    int i;
    QProgressBar processBar;
    int waitTime = lineInterval->text().toInt();
    int autoNum = lineNum->text().toInt();
    
    (*g_log)<< "auto send start..."<< ENDL;
    processBar.setMinimum(1);
    processBar.setMaximum(autoNum);
    processBar.show();
    for (i = 1; i <= autoNum; ++i)
    {
        on_pushSend_clicked();
        OS::wait(waitTime);
        processBar.setValue(i);
    }
    (*g_log)<< "auto send end... " << ENDL;
}

void ModuleWidget::on_pushAutoRecv_clicked()
{
    int i;
    QProgressBar processBar;
    
    (*g_log)<< "auto recv start..."<< ENDL;
    commRecvThread.recordTime(true);
    processBar.setMinimum(1);
    processBar.setMaximum(20);
    processBar.show();
    for (i = 1; i <= 10; ++i)
    {
        OS::wait(1000);//每次停1s供停20s
        processBar.setValue(i);
    }
    showMsgBox(tr("max interval %1").arg(commRecvThread.getMaxInterval(),0,'f',6));
    commRecvThread.recordTime(false);
    (*g_log)<< "auto recv end... " << ENDL;
}


void ModuleWidget::on_pushSend_clicked()
{
    int ret;
    string sendData = getLineSendText();
    (*g_log)<< "Sender sending data: " << sendData << ENDL;
    ret = commSender->send(sendData);
    if (ret != COMM_SUC)
    {
        showMsgBox(tr("ERROR: commSender send data failed: %1").arg(ret));
        return;
    }

    setLcdSendCount(commSender->getSendCount());
    appendBrowserSendText(QString::fromStdString(sendData));
    setLineSendText(QString::fromStdString(OS::genVisibleString(8)));
}

void ModuleWidget::onCommRecved(double timestamp, const QString& data)
{
    appendBrowserRecvText(tr("[%1] %2 ").arg(timestamp, 0,'f',6).arg(data));
    if (commReceiver != NULL)
    {
        setLcdRecvCount(commReceiver->getRecvCount());
    }
    const string& temp = data.toStdString();
    (*g_log)<< "commSender recving data: " << temp << ENDL;
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
    if (commReceiver != NULL)
    {
        commRecvThread.stop();
        commReceiver->close();//能使socket从阻塞中返回
        commRecvThread.wait();
        delete commReceiver;
        commReceiver = NULL;
    }

    if (commSender != NULL)
    {
        commSender->close();
        delete commSender;
        commSender = NULL;
    }
}


void ModuleWidget::clearTextBrowsers()
{
    textSend->clear();
    textRecv->clear();
}


