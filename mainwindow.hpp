#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "can.hpp"
#include "ui_mainwindow.h"

class QLabel;
using TabIndex = int;

class MainWindow : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT
public:
	MainWindow();
    
signals:
    void statusChanged(const QString &status);
    
private slots:
    void updateStatusBar(const QString &status);
    void on_pushCANOpen_clicked();
    void on_pushCANClose_clicked();
    void on_pushSend_1_clicked();
    void on_pushSend_2_clicked();
    void on_comboDevIndex_currentIndexChanged(const QString &text);
    
private:
    void createStatusBar();

    QLabel *statusLabel;
    TabIndex pre;/*tab变化时用于清理*/
    Can *pCan;
    
};

#endif