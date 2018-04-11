#ifndef _MODULEWIDGET_HPP_
#define _MODULEWIDGET_HPP_

#include <QtGui>
#include <string>
#include "ui_formmodule.h"
#include "comm.hpp"

using std::string;

class ModuleWidget : public QWidget, public Ui::FormModule
{
    Q_OBJECT
public:
    ModuleWidget();
    ~ModuleWidget();

    //获取行编辑器的显示文本
    string getTextLineSend1st();
    string getTextLineSend2nd();
    string getTextLineRecv1st();
    string getTextLineRecv2nd();    
    
signals:
    //按钮点击信号
    void pushOpenClicked();
    void pushCloseClicked();
    void pushAutoClicked();
    void pushSend1stClicked();
    void pushSend2ndClicked();

    //发送成功后触发接受的信号
    void comm1stSended();
    void comm2ndSended();
    
public slots:
    //设置窗口部件的可用性
    void setEnabledAtOpen();
    void setEnabledAtClose();
    
    //设置行编辑器的显示文本
    void setTextLineSend1st(const string& text);
    void setTextLineSend2nd(const string& text);
    void setTextLineRecv1st(const string& text);
    void setTextLineRecv2nd(const string& text);

    //设置统计数据
    void setLcdSendCount1st(int count);
    void setLcdSendCount2nd(int count);
    void setLcdLostRate1st(double rate);
    void setLcdLostRate2nd(double rate);
    void setLcdErroRate1st(double rate);
    void setLcdErroRate2nd(double rate);

    //子类需要实现open槽函数，用于创建通信对象
    virtual void onPushOpenClicked() = 0;
    
    void onPushCloseClicked();
    void onPushAutoClicked();
    void onPushSend1stClicked();
    void onPushSend2ndClicked();

    void onComm1stSended();
    void onComm2ndSended();
    
protected:
    //销毁通信对象
    void clearComms();

    //通信对象
    Comm * comm1st;
    Comm * comm2nd;
    
    QMessageBox msgBox;
};

#endif

