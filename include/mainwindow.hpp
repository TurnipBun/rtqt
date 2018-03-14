#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <pthread.h>
#include "can.hpp"
#include "ui_mainwindow.h"

class QLabel;
using TabIndex = int;

class MainWindow : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT
public:
	MainWindow();

    friend void *recvFirst(void *arg);
    friend void *recvSecond(void *arg);
    
signals:
    //void dataReceived(ChannelNo ch, string data);/*收到数据*/
    
private slots:
    //void showReceivedData(ChannelNo ch, string data);/*显示数据*/
    void on_comboDevIndex_currentIndexChanged(const QString &text);
    void on_pushCANOpen_clicked();
    void on_pushCANClose_clicked();
    void on_pushSend_1_clicked();
    void on_pushSend_2_clicked();
    
private:
    void createStatusBar();
    void updateStatus(const QString &text);
    int createCANRecvThread();/*创建2个接收线程*/
    int destoryCANRecvThread();
    
    QLabel *pStatusLabel;/*状态栏*/
    CAN *pFirstCh;/*通道1*/
    CAN *pSecondCh;/*通道2*/
    pthread_t* pFirstTh;/*通道1接收线程*/
    pthread_t* pSecondTh;/*通道2接收线程*/

};

#endif