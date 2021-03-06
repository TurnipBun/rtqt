#include "os.hpp"
#include "sockwidget.hpp"

SockWidget::SockWidget()
    :bClientEnabled(true)
{
    addSettings();
    fillParams();
    connect(checkClient,SIGNAL(clicked(bool)),this,SLOT(onClientStateChanged(bool)));
}

SockWidget::~SockWidget()
{
}

void SockWidget::on_pushOpen_clicked()
{
    string serverIp, clientIp, connectIp, protocol;
    unsigned int serverPort, clientPort, connectPort;
    bool convOk;
    int ret;
    serverIp = comboServerIp->currentText().toStdString();
    serverPort = lineServerPort->text().toInt(&convOk,10);
    
    clientIp = comboClientIp->currentText().toStdString();
    clientPort = lineClientPort->text().toInt(&convOk,10);
    
    connectIp = lineConnectIp->text().toStdString();
    connectPort = lineConnectPort->text().toInt(&convOk,10);

    protocol = comboProtocol->currentText().toStdString();    

    clearTextBrowsers();

    ret = initSockLib();
    if (COMM_SUC != ret)
    {
        showMsgBox("ERROR: call initSockLib failed");
        setEnabledAtClose();
        return;
    }

    ret = initComms(serverIp, serverPort,
                    clientIp, clientPort,
                    connectIp, connectPort,
                    protocol);
    if (COMM_SUC != ret)
    {
        showMsgBox("ERROR: call initComs failed");
        clearComms();
        setEnabledAtClose();
        return;
    }
    setLineSendText(QString::fromStdString(OS::genVisibleString(8)));
    return;
}

void SockWidget::on_pushClose_clicked()
{
    clearComms();
    releaseSockLib();
}

void SockWidget::onClientStateChanged(bool state)
{
    bClientEnabled = state;
}

void SockWidget::addSettings()
{
    labelServerIp = new QLabel(tr(" Receiver IP:"));
    labelServerPort = new QLabel(tr(" Receiver Port:"));
    comboServerIp = new QComboBox;
    lineServerPort = new QLineEdit(tr("5005"));
    hLayoutUp = new QHBoxLayout;
    hLayoutUp->addWidget(labelServerIp);
    hLayoutUp->addWidget(comboServerIp);
    hLayoutUp->addWidget(labelServerPort);
    hLayoutUp->addWidget(lineServerPort);
    hLayoutUp->insertStretch(-1);

    checkClient = new QCheckBox();
    labelClientIp = new QLabel(tr(" Sender IP:"));
    labelClientPort = new QLabel(tr(" Sender Port:"));
    comboClientIp = new QComboBox;
    lineClientPort= new QLineEdit(tr("5006"));

    hLayoutMid1 = new QHBoxLayout;
    hLayoutMid1->addWidget(checkClient);
    hLayoutMid1->addWidget(labelClientIp);
    hLayoutMid1->addWidget(comboClientIp);
    hLayoutMid1->addWidget(labelClientPort);
    hLayoutMid1->addWidget(lineClientPort);
    hLayoutMid1->insertStretch(-1);
    
    labelConnectIp = new QLabel(tr(" Target IP:"));
    labelConnectPort = new QLabel(tr(" Target Port:"));
    lineConnectIp = new QLineEdit();
    lineConnectPort = new QLineEdit();

    hLayoutMid2 = new QHBoxLayout;
    hLayoutMid2->addWidget(labelConnectIp);
    hLayoutMid2->addWidget(lineConnectIp);
    hLayoutMid2->addWidget(labelConnectPort);
    hLayoutMid2->addWidget(lineConnectPort);
    hLayoutMid2->insertStretch(-1);

    labelProtocol = new QLabel(tr(" Protocol:"));
    comboProtocol = new QComboBox;
    
    hLayoutDown = new QHBoxLayout;
    hLayoutDown->addWidget(labelProtocol);
    hLayoutDown->addWidget(comboProtocol);
    hLayoutDown->insertStretch(-1);

    vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayoutUp);
    vLayout->addLayout(hLayoutMid1);
    vLayout->addLayout(hLayoutMid2);
    vLayout->addLayout(hLayoutDown);

    groupSetting->setLayout(vLayout);
    return;
}
void SockWidget::fillParams()
{
    map<string,int>::const_iterator iter;
    
    const map<string,int>& mapSysIp = Sock::enumSysIpAddr();
    for(iter=mapSysIp.begin();iter!=mapSysIp.end();++iter)
    {
        comboServerIp->addItem(QString::fromStdString(iter->first), iter->second);
        comboClientIp->addItem(QString::fromStdString(iter->first), iter->second);
    }
    comboServerIp->setEditable(true);
    comboClientIp->setEditable(true);

    comboProtocol->addItem(tr("UDP"));
    comboProtocol->addItem(tr("TCP"));

    lineConnectIp->setText(comboServerIp->currentText());
    lineConnectPort->setText(lineServerPort->text());
    checkClient->setChecked(bClientEnabled);
    return;
}

int SockWidget::initSockLib()
{
#ifndef VXWORKS
    int ret;
    WSADATA wsaData;
    ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0) return COMM_ERR_OPEN;
#endif
    return COMM_SUC;
}

void SockWidget::releaseSockLib()
{
#ifndef VXWORKS
    WSACleanup();
#endif
}

int SockWidget::initComms(const string& serverIp, unsigned int serverPort,
                             const string& clientIp, unsigned int clientPort,
                             const string& connectIp, unsigned int connectPort,
                             const string& protocol)
{   
    int ret;
    
    commReceiver = new Sock(serverIp, serverPort, protocol);
    ret = commReceiver->open();
    if (COMM_SUC != ret) return ret;
    commRecvThread.bind(commReceiver);
    commRecvThread.start();

    if (bClientEnabled)
    {
        commSender = new Sock(clientIp, clientPort, protocol);
        reinterpret_cast<Sock*>(commSender)->connect(connectIp, connectPort);
        ret = commSender->open();
        if (COMM_SUC != ret) return ret;
    }
    
    return COMM_SUC;
}

