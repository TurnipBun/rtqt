#include "modulewidget.hpp"

ModuleWidget::ModuleWidget()
{
	setupUi(this);
	setEnabledAtClose();
	//调整窗口部件的可用性
	connect(pushOpen,SIGNAL(clicked()),this,SLOT(setEnabledAtOpen()));
	connect(pushClose,SIGNAL(clicked()),this,SLOT(setEnabledAtClose()));
	//链接按钮信号(也可在上层类中直接connect按钮的信号)
	connect(pushOpen,SIGNAL(clicked()),this,SIGNAL(pushOpenClicked()));
	connect(pushClose,SIGNAL(clicked()),this,SIGNAL(pushCloseClicked()));
	connect(pushAuto,SIGNAL(clicked()),this,SIGNAL(pushAutoClicked()));
	connect(pushSend1st,SIGNAL(clicked()),this,SIGNAL(pushSend1stClicked()));
	connect(pushSend2nd,SIGNAL(clicked()),this,SIGNAL(pushSend2ndClicked()));
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