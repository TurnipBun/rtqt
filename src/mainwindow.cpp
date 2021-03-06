#include "sockwidget.hpp"
#include "comwidget.hpp"
#include "canwidget.hpp"
#include "log.hpp"

#include "mainwindow.hpp"

MainWindow::MainWindow()
{
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    this->setWindowIcon(icon);
    
    this->resize(800, 600);
    
    QTabWidget *tabWidget = new QTabWidget(this);
    ComWidget *comWidget = new ComWidget;
    CanWidget *canWidget = new CanWidget;
    SockWidget *sockWidget = new SockWidget;
    tabWidget->addTab(comWidget, QString("Com Test"));
    tabWidget->addTab(canWidget, QString("Can Test"));
    tabWidget->addTab(sockWidget, QString("Net Test"));
    this->setCentralWidget(tabWidget);
    initGlobalLog();
}

MainWindow::~MainWindow()
{   
    delete g_log;
}


