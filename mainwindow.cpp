#include <cassert>
#include <QtGui>
//#include <pthread>

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

QString MainWindow::getMsgHex(CANRMMsg &msg)
{
    return tr("0x%1 0x%2 0x%3 0x%4 0x%5 0x%6 0x%7 0x%8").arg(msg.Data[0],0,16).arg(msg.Data[1],0,16).arg(msg.Data[2],0,16).arg(msg.Data[3],0,16).arg(msg.Data[4],0,16).arg(msg.Data[5],0,16).arg(msg.Data[6],0,16).arg(msg.Data[7],0,16);
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
    Can::defaultMsgData(firstChannelSendMsg);
    lineSendData_1->setText(getMsgHex(firstChannelSendMsg));

    Can::defaultMsgData(secondChannelSendMsg);
    lineSendData_2->setText(getMsgHex(secondChannelSendMsg));
    
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
    int ret;
    ret = pCan->send(firstChannelSendMsg, pCan->getFirstChannel());
    if (ret == CAN_SUC)
    {
        updateStatusBar(tr("send data using first channel success ..."));
    }
    else
    {
        updateStatusBar(tr("send data using first channel failed ..."));
    }
}

void MainWindow::on_pushSend_2_clicked()
{
    int ret;
    ret = pCan->send(secondChannelSendMsg, pCan->getSecondChannel());
    if (ret == CAN_SUC)
    {
        updateStatusBar(tr("send data using second channel success ..."));
    }
    else
    {
        updateStatusBar(tr("send data using second channel failed ..."));
    }
}
