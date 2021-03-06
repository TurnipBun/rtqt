#include "comwidget.hpp"
#include "os.hpp"
#include "log.hpp"

ComWidget::ComWidget()
{
    addSettings();
    fillCombos();
}
ComWidget::~ComWidget()
{
}

void ComWidget::on_pushOpen_clicked()
{
    int ret;

    clearTextBrowsers();
    
    string com1stName = comboComReceiver->currentText().toStdString();
    string com2ndName = comboComSender->currentText().toStdString();
    if (com1stName == com2ndName)
    {
        showMsgBox("ERROR: two ports can not be the same.");
        setEnabledAtClose();
        return;
    }

    int baudRate = comboBaudRate->itemData(comboBaudRate->currentIndex()).toInt();
    int dataBit = comboDataBit->itemData(comboDataBit->currentIndex()).toInt();
    int stopBit = comboStopBit->itemData(comboStopBit->currentIndex()).toInt();
    int parity = comboParity->itemData(comboParity->currentIndex()).toInt();
    bool isRtsOn = checkRts->isChecked();
    
    ret = initComms(com1stName, com2ndName,isRtsOn, baudRate, dataBit, stopBit, parity);
    if (COMM_SUC != ret)
    {
        showMsgBox("ERROR: call initComs failed");
        clearComms();
        setEnabledAtClose();
        return;
    }
    setLineSendText(QString::fromStdString(OS::genVisibleString(8)));
}

void ComWidget::on_pushClose_clicked()
{
    clearComms();
}


void ComWidget::addSettings()
{
    hLayoutUp = new QHBoxLayout;
    labelComReceiver = new QLabel(tr(" Receiver COM:"));
    labelComSender = new QLabel(tr(" Sender COM:"));
    comboComReceiver = new QComboBox;
    comboComSender = new QComboBox;
    checkRts = new QCheckBox("RTS");
    hLayoutUp->addWidget(labelComReceiver);
    hLayoutUp->addWidget(comboComReceiver);
    hLayoutUp->addWidget(labelComSender);
    hLayoutUp->addWidget(comboComSender);
    hLayoutUp->addWidget(comboComSender);
    hLayoutUp->insertStretch(-1);
    hLayoutUp->addWidget(checkRts);
    
    hLayoutDown = new QHBoxLayout;
    labelBaudRate = new QLabel(tr(" Boud Rate:"));
    labelDataBit = new QLabel(tr(" Data Bit:"));
    labelStopBit = new QLabel(tr(" Stop Bit:"));
    labelParity = new QLabel(tr(" Parity:"));
    comboBaudRate = new QComboBox;
    comboDataBit = new QComboBox;
    comboStopBit = new QComboBox;
    comboParity = new QComboBox;
    hLayoutDown->addWidget(labelBaudRate);
    hLayoutDown->addWidget(comboBaudRate);
    hLayoutDown->addWidget(labelDataBit);
    hLayoutDown->addWidget(comboDataBit);
    hLayoutDown->addWidget(labelStopBit);
    hLayoutDown->addWidget(comboStopBit);
    hLayoutDown->addWidget(labelParity);
    hLayoutDown->addWidget(comboParity);
    
    vLayoutMain = new QVBoxLayout;
    vLayoutMain->addLayout(hLayoutUp);
    vLayoutMain->addLayout(hLayoutDown);

    groupSetting->setLayout(vLayoutMain);
}

void ComWidget::fillCombos()
{
    map<string,int>::const_iterator iter;
    
    const map<string,int>& mapPort = DEF_COM::enumSettingPort();
    for(iter=mapPort.begin();iter!=mapPort.end();++iter)
    {
        comboComReceiver->addItem(QString::fromStdString(iter->first), iter->second);
        comboComSender->addItem(QString::fromStdString(iter->first), iter->second);
    }

    const map<string,int>& mapBaudRate = DEF_COM::enumSettingBaudRate();
    for(iter=mapBaudRate.begin();iter!=mapBaudRate.end();++iter)
    {
        comboBaudRate->addItem(QString::fromStdString(iter->first), iter->second);
    }

    const map<string,int>& mapDataBit = DEF_COM::enumSettingDataBit();
    for(iter=mapDataBit.begin();iter!=mapDataBit.end();++iter)
    {
        comboDataBit->addItem(QString::fromStdString(iter->first), iter->second);
    }

    const map<string,int>& mapStopBit = DEF_COM::enumSettingStopBit();
    for(iter=mapStopBit.begin();iter!=mapStopBit.end();++iter)
    {
        comboStopBit->addItem(QString::fromStdString(iter->first), iter->second);
    }

    const map<string,int>& mapParity = DEF_COM::enumSettingParity();
    for(iter=mapParity.begin();iter!=mapParity.end();++iter)
    {
        comboParity->addItem(QString::fromStdString(iter->first), iter->second);
    }
}

int ComWidget::initComms(const string& com1stName, const string& com2ndName, bool isRtsOn,
                             int baudRate, int dataBit, int stopBit, int parity)
{
    
    commReceiver = new DEF_COM(com1stName,baudRate,dataBit,stopBit,parity,isRtsOn);
    commSender = new DEF_COM(com2ndName,baudRate,dataBit,stopBit,parity,isRtsOn);
    int ret;
    ret = commReceiver->open();
    if (COMM_SUC != ret) return ret;
    ret = commSender->open();
    if (COMM_SUC != ret) return ret;
    
    commRecvThread.bind(commReceiver);
    commRecvThread.start();
    
    return COMM_SUC;
}

