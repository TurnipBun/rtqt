#include "canwidget.hpp"
#include "os.hpp"
#include "log.hpp"

CanWidget::CanWidget()
{
    addSettings();
    fillCombos();
    connectSignalToSlot();
}
CanWidget::~CanWidget()
{
}

void CanWidget::onPushOpenClicked()
{
    int devno = comboCanPairDev->itemData(comboBaudRate->currentIndex()).toInt();
    int baudRate = comboBaudRate->itemData(comboBaudRate->currentIndex()).toInt();

    int ret = initComms(devno,baudRate);
    if (COMM_SUC != ret)
    {
        msgBox.setText("ERROR: call initCans failed");
        msgBox.exec();
        clearComms();
        setEnabledAtClose();
        return;
    } 
    
    setTextLineSend1st(OS::genVisibleString(8));
    setTextLineSend2nd(OS::genVisibleString(8));
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

void CanWidget::connectSignalToSlot()
{
    connect(this,SIGNAL(pushOpenClicked()),this,SLOT(onPushOpenClicked()));
}

int CanWidget::initComms(int devno, int baudRate)
{
    comm1st = new Can(devno*2,baudRate);
    comm2nd = new Can(devno*2+1,baudRate);

    int ret;
    ret = comm1st->open();
    if (COMM_SUC != ret) return ret;
    ret = comm2nd->open();
    if (COMM_SUC != ret) return ret;
    return COMM_SUC;
}
                         



