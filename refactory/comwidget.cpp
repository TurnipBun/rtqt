#include "comwidget.hpp"

ComWidget::ComWidget()
    :com1st(NULL),com2nd(NULL)
{
    addSettings();
    fillCombos();
    connectSignalToSlot();
}
ComWidget::~ComWidget()
{
}

void ComWidget::onPushOpenClicked()
{
    string com1stName = comboComName1st->currentText().toStdString();
    string com2ndName = comboComName2nd->currentText().toStdString();
    if (com1stName == com2ndName)
    {
        msgBox.setText("ERROR: two ports can not be the same.");
        msgBox.exec();
        setEnabledAtClose();
        return;
    }

    int baudRate = comboBoudRate->itemData(comboBoudRate->currentIndex()).toInt();
    int dataBit = comboDataBit->itemData(comboDataBit->currentIndex()).toInt();
    int stopBit = comboStopBit->itemData(comboStopBit->currentIndex()).toInt();
    int parity = comboParity->itemData(comboParity->currentIndex()).toInt();
    
    if (COM_SUC != initComs(com1stName, com2ndName, baudRate, dataBit, stopBit, parity))
    {
        clearComs();
        setEnabledAtClose();
    }
}

void ComWidget::onPushCloseClicked()
{

}

void ComWidget::onPushAutoClicked()
{
    QMessageBox msgBox;
    msgBox.setText("button auto clicked.");
    msgBox.exec();
}

void ComWidget::onPushSend1stClicked()
{
    QMessageBox msgBox;
    msgBox.setText("button first-send clicked.");
    msgBox.exec();
}

void ComWidget::onPushSend2ndClicked()
{
    QMessageBox msgBox;
    msgBox.setText("button second-send clicked.");
    msgBox.exec();
}

/**C O M   W I D G E T . A D D   S E T T I N G E L E M E N T S*************
 * Create: BY Huang Cheng(turnipbun@icloud.com) ON 201844
 * Description: 添加设置组的带布局的配置元素
 * Parameters: 
   - void
 * Return: void
----------------------------C H A N G E   L O G----------------------------
 * 
**************************************************************************/
void ComWidget::addSettings()
{
    hLayoutUp = new QHBoxLayout;
    labelComName1st = new QLabel(tr(" 1st COM:"));
    labelComName2nd = new QLabel(tr(" 2nd COM:"));
    comboComName1st = new QComboBox;
    comboComName2nd = new QComboBox;
    hLayoutUp->addWidget(labelComName1st);
    hLayoutUp->addWidget(comboComName1st);
    hLayoutUp->addWidget(labelComName2nd);
    hLayoutUp->addWidget(comboComName2nd);
    hLayoutUp->addWidget(comboComName2nd);
    hLayoutUp->insertStretch(-1);
    
    hLayoutDown = new QHBoxLayout;
    labelBoudRate = new QLabel(tr(" Boud Rate:"));
    labelDataBit = new QLabel(tr(" Data Bit:"));
    labelStopBit = new QLabel(tr(" Stop Bit:"));
    labelParity = new QLabel(tr(" Parity:"));
    comboBoudRate = new QComboBox;
    comboDataBit = new QComboBox;
    comboStopBit = new QComboBox;
    comboParity = new QComboBox;
    hLayoutDown->addWidget(labelBoudRate);
    hLayoutDown->addWidget(comboBoudRate);
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

/**C O M   W I D G E T . F I L L   C O M B O S*****************************
 * Create: BY Huang Cheng(yelloworangecc@icloud.com) ON 201848
 * Description: 初始化界面中下拉框的可选项目
 * Parameters: 
   - void
 * Return: void
----------------------------C H A N G E   L O G----------------------------
 * 
**************************************************************************/
void ComWidget::fillCombos()
{
    map<string,int>::const_iterator iter;
    
    const map<string,int>& mapPort = VxCom::enumSettingPort();
    for(iter=mapPort.begin();iter!=mapPort.end();++iter)
    {
        comboComName1st->addItem(QString::fromStdString(iter->first), iter->second);
        comboComName2nd->addItem(QString::fromStdString(iter->first), iter->second);
    }

    const map<string,int>& mapBoudRate = VxCom::enumSettingBaudRate();
    for(iter=mapBoudRate.begin();iter!=mapBoudRate.end();++iter)
    {
        comboBoudRate->addItem(QString::fromStdString(iter->first), iter->second);
    }

    const map<string,int>& mapDataBit = VxCom::enumSettingDataBit();
    for(iter=mapDataBit.begin();iter!=mapDataBit.end();++iter)
    {
        comboDataBit->addItem(QString::fromStdString(iter->first), iter->second);
    }

    const map<string,int>& mapStopBit = VxCom::enumSettingStopBit();
    for(iter=mapStopBit.begin();iter!=mapStopBit.end();++iter)
    {
        comboStopBit->addItem(QString::fromStdString(iter->first), iter->second);
    }

    const map<string,int>& mapParity = VxCom::enumSettingParity();
    for(iter=mapParity.begin();iter!=mapParity.end();++iter)
    {
        comboParity->addItem(QString::fromStdString(iter->first), iter->second);
    }
}

void ComWidget::connectSignalToSlot()
{
    connect(this,SIGNAL(pushOpenClicked()),this,SLOT(onPushOpenClicked()));
    connect(this,SIGNAL(pushCloseClicked()),this,SLOT(onPushCloseClicked()));
    connect(this,SIGNAL(pushAutoClicked()),this,SLOT(onPushAutoClicked()));
    connect(this,SIGNAL(pushSend1stClicked()),this,SLOT(onPushSend1stClicked()));
    connect(this,SIGNAL(pushSend2ndClicked()),this,SLOT(onPushSend2ndClicked()));
}

int ComWidget::initComs(const string& com1stName, const string& com2ndName,
                         int baudRate, int dataBit, int stopBit, int parity)
{
    
    com1st = new VxCom(com1stName,baudRate,dataBit,stopBit,parity);
    com2nd = new VxCom(com2ndName,baudRate,dataBit,stopBit,parity);
    int ret;
    ret = com1st->open();
    if (COM_SUC != ret) return ret;
    ret = com2nd->open();
    if (COM_SUC != ret) return ret;
    return COM_SUC;
}
                         
int ComWidget::clearComs()
{
    com1st->close();
    com2nd->close();
    if (com1st != NULL)
    {
        delete com1st;
        com1st = NULL;
    }

    if (com2nd != NULL)
    {
        delete com2nd;
        com2nd = NULL;
    }
}

