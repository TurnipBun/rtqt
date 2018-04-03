#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <pthread.h>
#include "log.hpp"
#include "can.hpp"
#ifdef VXWORKS
#else
#include "wincom.hpp"
#endif
#include "ui_mainwindow.h"

class QLabel;
typedef int TabIndex;

class MainWindow : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT
public:
	MainWindow();
    ~MainWindow();

    friend void *canRecv1(void *arg);
    friend void *canRecv2(void *arg);
    friend void *comRecv1(void *arg);
    friend void *comRecv2(void *arg);
    
//signals:
    
private slots:
    void on_tabWidget_currentChanged(int index);

    void on_pushCANOpen_clicked();
    void on_pushCANClose_clicked();
    void on_pushCANSend1_clicked();
    void on_pushCANSend2_clicked();

    void on_pushCOMOpen_clicked();
    void on_pushCOMClose_clicked();
    void on_pushCOMSend1_clicked();
    void on_pushCOMSend2_clicked();
    
private:
    void createStatusBar();
    void updateStatus(const QString &text);
    
    int createCAN(int devNo, int canRate);
    void deleteCAN();
    int createCANRecvThread();
    void destoryCANRecvThread();
    
    int createCOM();
    void deleteCOM();
    int createCOMRecvThread();
    void destoryCOMRecvThread();
    
    QLabel *pStatusLabel;
    Log* pLog;
    
    CAN *pCan1;
    CAN *pCan2;
    COM *pCom1;
    COM *pCom2;
    pthread_t* pCanTh1;
    pthread_t* pCanTh2;
    pthread_t* pComTh1;
    pthread_t* pComTh2;

};

#endif
