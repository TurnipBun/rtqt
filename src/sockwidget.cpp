#include "os.hpp"
#include "sockwidget.hpp"

SockWidget::SockWidget()
{
    addSettings();
    fillCombos();
    connectSignalToSlot();
}

SockWidget::~SockWidget()
{
}

void SockWidget::onPushOpenClicked()
{
    //TODO:依据界面元素的参数初始化通信对象
    string serverIp, clientIp;
    unsigned int serverPort, clientPort;
    bool convOk;
    int ret;
    serverIp = comboServerIp->currentText().toStdString();
    clientIp = comboClientIp->currentText().toStdString();
    serverPort = lineServerPort->text().toInt(&convOk,10);
    clientPort = lineClientPort->text().toInt(&convOk,10);

    ret = initComms(serverIp,serverPort,clientIp,clientPort);
    if (COMM_SUC != ret)
    {
        msgBox.setText("ERROR: call initComs failed");
        msgBox.exec();
        clearComms();
        setEnabledAtClose();
        return;
    }
    
    setTextLineSend1st(OS::genVisibleString(8));
    setTextLineSend2nd(OS::genVisibleString(8));
    return;
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
    hLayoutDown = new QHBoxLayout;
    hLayoutDown->addWidget(labelClientIp);
    hLayoutDown->addWidget(comboClientIp);
    hLayoutDown->addWidget(labelClientPort);
    hLayoutDown->addWidget(lineClientPort);
    hLayoutDown->insertStretch(-1);

    vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayoutUp);
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
    return;
}
void SockWidget::connectSignalToSlot()
{
    connect(this,SIGNAL(pushOpenClicked()),this,SLOT(onPushOpenClicked()));
    return;
}


int SockWidget::initComms(const string& serverIp, unsigned int serverPort,
                             const string& clientIp, unsigned int clientPort)
{
    comm1st = new DEF_SOCK(serverIp, serverPort);
    comm2nd = new DEF_SOCK(clientIp, clientPort);
    reinterpret_cast<DEF_SOCK*>(comm2nd)->connect(serverIp,serverPort);
    int ret;
    ret = comm1st->open();
    if (COMM_SUC != ret) return ret;
    ret = comm2nd->open();
    if (COMM_SUC != ret) return ret;
    return COMM_SUC;
}

