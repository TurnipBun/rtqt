#include <cassert>
#include <QtGui>

#include "mainwindow.hpp"

/*构造函数
 *1.初始化UI
 */
MainWindow::MainWindow()
{
	setupUi(this);
    createStatusBar();
    pCan = new Can(0);
}

void MainWindow::createStatusBar()
{
    statusLabel = new QLabel(tr("windows initialized ok ..."));
    statusLabel->setAlignment(Qt::AlignHCenter);

    statusBar()->addWidget(statusLabel);
    connect(this,SIGNAL(statusChanged(const QString &)),
            this, SLOT(const updateStatusBar(QString &)));
}

void MainWindow::updateStatusBar(const QString &status)
{
    statusLabel->setText(status);
}

void MainWindow::on_comboDevIndex_currentIndexChanged(const QString &text)
{
    bool result;
    int devNo = text.toInt(&result,10);
    assert(result == true);
    pCan->reset(devNo);
    updateStatusBar(tr("current CAN dev is %1 ...").arg(text));
    
}

void MainWindow::on_pushCANOpen_clicked()
{
    int ret;
    ret = pCan->initAll();
    if (ret == CAN_ERR)
    {
        updateStatusBar(tr("init CAN dev failed ..."));
        //return;
    }

    ret = pCan->openAll();
    if (ret == CAN_ERR)
    {
        updateStatusBar(tr("open CAN channels failed ..."));
        //return;
    }

    comboDevIndex->setEnabled(false);
    pushCANOpen->setEnabled(false);
    pushCANClose->setEnabled(true);
    groupChannel_1->setEnabled(true);
    groupChannel_2->setEnabled(true);
    
    return;
}

void MainWindow::on_pushCANClose_clicked()
{
    QString text = comboDevIndex->currentText();
    bool result;
    int devNo = text.toInt(&result,10);
    assert(result == true);
    pCan->reset(devNo);
    
    comboDevIndex->setEnabled(true);
    pushCANOpen->setEnabled(true);
    pushCANClose->setEnabled(false);
    groupChannel_1->setEnabled(false);
    groupChannel_2->setEnabled(false);

    updateStatusBar(tr("current CAN dev is %1 ...").arg(text));
}

void MainWindow::on_pushSend_1_clicked()
{
}

void MainWindow::on_pushSend_2_clicked()
{
}
