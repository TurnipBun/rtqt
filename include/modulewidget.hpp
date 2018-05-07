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

    //发送数据的行文本编辑框访问函数
    string getTextLineSend1st();
    string getTextLineSend2nd();
    void setTextLineSend1st(const QString& text);
    void setTextLineSend2nd(const QString& text);

    //发送和接受数据记录文本框访问函数
    void appendTextBrowserSend1st(const QString& text);
    void appendTextBrowserSend2nd(const QString& text);
    void appendTextBrowserRecv1st(const QString& text);
    void appendTextBrowserRecv2nd(const QString& text);

    //发送和接受统计显示框访问函数
    void setLcdSendCount1st(int count);
    void setLcdSendCount2nd(int count);
    void setLcdRecvCount1st(int count);
    void setLcdRecvCount2nd(int count);
    
    //显示消息框槽函数
    void showMsgBox(const QString& text);
    
signals:
    //发送成功后触发接受的信号,过时的
    //void comm1stSended();
    //void comm2ndSended();
    
public slots:
    //设置窗口部件的可用性
    void setEnabledAtOpen();
    void setEnabledAtClose();

    //子类需要实现的按钮点击槽函数
    virtual void on_pushOpen_clicked() = 0;
    virtual void on_pushClose_clicked() = 0;

    //按钮点击槽函数
    void on_pushAuto_clicked();
    void on_pushSend1st_clicked();
    void on_pushSend2nd_clicked();
    
    //自发自收情况下的接收数据处理，过时
    //void onComm1stSended();
    //void onComm2ndSended();
    
    //线程的接收数据槽函数
    void onComm1stRecved(const QString& text);
    void onComm2ndRecved(const QString& text);

    //线程状态通知槽函数
    void onThreadStarted();
    void onThreadFinished();

    void clearComms();
    void clearTextBrowsers();
    
protected:

    //通信对象
    Comm * comm1st;
    Comm * comm2nd;
    //线程对象
    CommThread comm1stThread;
    CommThread comm2ndThread;
    
    QMessageBox msgBox;
};

inline string ModuleWidget::getTextLineSend1st()
{
    return lineSend1st->text().toStdString();
}

inline string ModuleWidget::getTextLineSend2nd()
{
    return lineSend2nd->text().toStdString();
}

inline void ModuleWidget::setTextLineSend1st(const QString& text)
{
    lineSend1st->setText(text);
}

inline void ModuleWidget::setTextLineSend2nd(const QString& text)
{
    lineSend2nd->setText(text);
}

inline void ModuleWidget::appendTextBrowserSend1st(const QString& text)
{
    textSend1st->append(text);
}

inline void ModuleWidget::appendTextBrowserSend2nd(const QString& text)
{
    textSend2nd->append(text);
}

inline void ModuleWidget::appendTextBrowserRecv1st(const QString& text)
{
    textRecv1st->append(text);
}

inline void ModuleWidget::appendTextBrowserRecv2nd(const QString& text)
{
    textRecv2nd->append(text);
}

inline void ModuleWidget::setLcdSendCount1st(int count)
{
    lcdSendCount1st->display(count);
}

inline void ModuleWidget::setLcdSendCount2nd(int count)
{
    lcdSendCount2nd->display(count);
}

inline void ModuleWidget::setLcdRecvCount1st(int count)
{
    lcdRecvCount1st->display(count);   
}

inline void ModuleWidget::setLcdRecvCount2nd(int count)
{
    lcdRecvCount2nd->display(count);
}

#endif

