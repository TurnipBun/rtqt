#include "os.hpp"
#include "sockwidget.hpp"

SockWidget::SockWidget()
{
    addSettings();
    fillCombos();
}

SockWidget::~SockWidget()
{
}

void SockWidget::on_pushOpen_clicked()
{
    string serverIp, clientIp;
    unsigned int serverPort, clientPort;
    bool convOk;
    int ret;
    serverIp = comboServerIp->currentText().toStdString();
    clientIp = comboClientIp->currentText().toStdString();
    serverPort = lineServerPort->text().toInt(&convOk,10);
    clientPort = lineClientPort->text().toInt(&convOk,10);

    clearTextBrowsers();

    ret = initSockLib();
    if (COMM_SUC != ret)
    {
        showMsgBox("ERROR: call initSockLib failed");
        setEnabledAtClose();
        return;
    }

    ret = initComms(serverIp,serverPort,clientIp,clientPort);
    if (COMM_SUC != ret)
    {
        showMsgBox("ERROR: call initComs failed");
        clearComms();
        setEnabledAtClose();
        return;
    }
    setTextLineSend1st(QString::fromStdString(OS::genVisibleString(8)));
    setTextLineSend2nd(QString::fromStdString(OS::genVisibleString(8)));
    return;
}

void SockWidget::on_pushClose_clicked()
{
    clearComms();
    releaseSockLib();
}


void SockWidget::addSettings()
{
    labelServerIp = new QLabel(tr(" Server IP:"));
    labelServerPort = new QLabel(tr(" Server Port:"));
    comboServerIp = new QComboBox;
    lineServerPort = new QLineEdit(tr("5005"));
    hLayoutUp = new QHBoxLayout;
    hLayoutUp->addWidget(labelServerIp);
    hLayoutUp->addWidget(comboServerIp);
    hLayoutUp->addWidget(labelServerPort);
    hLayoutUp->addWidget(lineServerPort);
    hLayoutUp->insertStretch(-1);
    
    labelClientIp = new QLabel(tr(" Client IP:"));
    labelClientPort = new QLabel(tr(" Client Port:"));
    comboClientIp = new QComboBox;
    lineClientPort= new QLineEdit(tr("5006"));

    hLayoutMid = new QHBoxLayout;
    hLayoutMid->addWidget(labelClientIp);
    hLayoutMid->addWidget(comboClientIp);
    hLayoutMid->addWidget(labelClientPort);
    hLayoutMid->addWidget(lineClientPort);
    hLayoutMid->insertStretch(-1);

    labelProtocol = new QLabel(tr(" Protocol:"));
    comboProtocol = new QComboBox;
    
    hLayoutDown = new QHBoxLayout;
    hLayoutDown->addWidget(labelProtocol);
    hLayoutDown->addWidget(comboProtocol);
    hLayoutMid->insertStretch(-1);

    vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayoutUp);
    vLayout->addLayout(hLayoutMid);
    vLayout->addLayout(hLayoutDown);

    groupSetting->setLayout(vLayout);
    return;
}
void SockWidget::fillCombos()
{
    map<string,int>::const_iterator iter;
    
    const map<string,int>& mapSysIp = DEF_SOCK::enumSysIpAddr();
    for(iter=mapSysIp.begin();iter!=mapSysIp.end();++iter)
    {
        comboServerIp->addItem(QString::fromStdString(iter->first), iter->second);
        comboClientIp->addItem(QString::fromStdString(iter->first), iter->second);
    }
    comboServerIp->setEditable(true);
    comboClientIp->setEditable(true);
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
                             const string& clientIp, unsigned int clientPort)
{   
    int ret;
    comm1st = new DEF_SOCK(serverIp, serverPort);
    comm2nd = new DEF_SOCK(clientIp, clientPort);
    reinterpret_cast<DEF_SOCK*>(comm2nd)->connect(serverIp,serverPort);

    ret = comm1st->open();
    if (COMM_SUC != ret) return ret;
    ret = comm2nd->open();
    if (COMM_SUC != ret) return ret;
    
    comm1stThread.bind(comm1st);
    comm1stThread.start();
    comm2ndThread.bind(comm2nd);
    comm2ndThread.start();
    return COMM_SUC;
}

