#ifndef _MODULEWIDGET_HPP_
#define _MODULEWIDGET_HPP_

#include <QWidget>
#include <string>
#include "ui_formmodule.h"

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
    
public slots:
	//设置窗口部件的可用性
	void setEnabledAtOpen();
	void setEnabledAtClose();
	
	//设置行编辑器的显示文本
	void setTextLineSend1st(const string& text);
	void setTextLineSend2nd(const string& text);
	void setTextLineRecv1st(const string& text);
	void setTextLineRecv2nd(const string& text);

    void setLcdSendCount1st(int count);
    void setLcdSendCount2nd(int count);
    void setLcdLostRate1st(double rate);
    void setLcdLostRate2nd(double rate);
    void setLcdErroRate1st(double rate);
    void setLcdErroRate2nd(double rate);
    
//private:
};

#endif

