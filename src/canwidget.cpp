#include "canwidget.hpp"
#include "os.hpp"
#include "log.hpp"

CanWidget::CanWidget()
{
    addSettings();
    fillCombos();
}
CanWidget::~CanWidget()
{
}

void CanWidget::on_pushOpen_clicked()
{
    int devno = comboCanPairDev->itemData(comboBaudRate->currentIndex()).toInt();
    int baudRate = comboBaudRate->itemData(comboBaudRate->currentIndex()).toInt();

    clearTextBrowsers();

    int ret = initComms(devno,baudRate);
    if (COMM_SUC != ret)
    {
        showMsgBox("ERROR: call initCans failed");
        clearComms();
        setEnabledAtClose();
        return;
    } 
    setLineSendText(QString::fromStdString(OS::genVisibleString(8)));
}

void CanWidget::on_pushClose_clicked()
{
    clearComms();
}


void CanWidget::addSettings()
{
    
    hLayout = new QHBoxLayout;
    labelCanPairDev = new QLabel(tr(" Device:"));
    comboCanPairDev = new QComboBox;
    labelBaudRate = new QLabel(tr(" Baud Rate:"));
    comboBaudRate = new QComboBox;
    hLayout->addWidget(labelCanPairDev);
    hLayout->addWidget(comboCanPairDev);
    hLayout->insertStretch(-1);
    hLayout->addWidget(labelBaudRate);
    hLayout->addWidget(comboBaudRate);

    groupSetting->setLayout(hLayout);
}

void CanWidget::fillCombos()
{
    map<string,int>::const_iterator iter;
    
    const map<string,int>& mapDevice = Can::enumSettingDevice();
    for(iter=mapDevice.begin();iter!=mapDevice.end();++iter)
    {
        comboCanPairDev->addItem(QString::fromStdString(iter->first), iter->second);
    }

    const map<string,int>& mapBaudRate = Can::enumSettingBaudRate();
    for(iter=mapBaudRate.begin();iter!=mapBaudRate.end();++iter)
    {
        comboBaudRate->addItem(QString::fromStdString(iter->first), iter->second);
    }
}

int CanWidget::initComms(int devno, int baudRate)
{
    commReceiver = new Can(devno*2,baudRate);
    commSender = new Can(devno*2+1,baudRate);

    int ret;
    ret = commReceiver->open();
    if (COMM_SUC != ret) return ret;
    ret = commSender->open();
    if (COMM_SUC != ret) return ret;

    commRecvThread.bind(commReceiver);
    commRecvThread.start();
    
    return COMM_SUC;
}
                         



