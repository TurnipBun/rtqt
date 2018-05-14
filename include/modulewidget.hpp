#ifndef _MODULEWIDGET_HPP_
#define _MODULEWIDGET_HPP_

#include <QtGui>
#include <string>
#include "ui_formmodule.h"
#include "comm.hpp"
#include "commthread.hpp"

using std::string;

class ModuleWidget : public QWidget, public Ui::FormModule
{
    Q_OBJECT
public:
    ModuleWidget();
    ~ModuleWidget();

    string getLineSendText();
    void setLineSendText(const QString& text);
    void appendBrowserSendText(const QString& text);
    void appendBrowserRecvText(const QString& text);
    void setLcdSendCount(int count);
    void setLcdRecvCount(int count);
    void showMsgBox(const QString& text);
    
public slots:
    //设置窗口部件的可用性
    void setEnabledAtOpen();
    void setEnabledAtClose();

    //子类需要实现的按钮点击槽函数
    virtual void on_pushOpen_clicked() = 0;
    virtual void on_pushClose_clicked() = 0;

    //按钮点击槽函数
    void on_pushAutoRecv_clicked();
    void on_pushAutoSend_clicked();
    void on_pushSend_clicked();
    
    //线程的接收数据槽函数
    void onCommRecved(double timestamp, const QString& text);

    //线程状态通知槽函数
    void onThreadStarted();
    void onThreadFinished();

    void clearComms();
    void clearTextBrowsers();
    
protected:

    //通信对象
    Comm * commReceiver;
    Comm * commSender;
    //线程对象
    CommThread commRecvThread;

    QMessageBox msgBox;
};

inline string ModuleWidget::getLineSendText()
{
    return lineSend->text().toStdString();
}

inline void ModuleWidget::setLineSendText(const QString& text)
{
    lineSend->setText(text);
}

inline void ModuleWidget::appendBrowserSendText(const QString& text)
{
    textSend->append(text);
}

inline void ModuleWidget::appendBrowserRecvText(const QString& text)
{
    textRecv->append(text);
}

inline void ModuleWidget::setLcdSendCount(int count)
{
    lcdSendCount->display(count);
}

inline void ModuleWidget::setLcdRecvCount(int count)
{
    lcdRecvCount->display(count);   
}

#endif

