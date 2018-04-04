#include "comwidget.hpp"

ComWidget::ComWidget()
{
    addSettingelements();
    //TODO:为各个下拉框填充内容
    fillComboContent();
}
ComWidget::~ComWidget()
{
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
void ComWidget::addSettingelements()
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
    labelBoudRate = new QLabel(tr(" Bound Rate:"));
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

void ComWidget::fillComboContent()
{
    comboDataBit->addItem("8", CS8);
    comboDataBit->addItem("7", CS7);
    comboDataBit->addItem("6", CS6);
    comboDataBit->addItem("5", CS5);

    comboStopBit->addItem("1", 0);
    comboStopBit->addItem("2", STOPB);

    comboParity->addItem("none", 0);
    comboParity->addItem("even", PARENB);
    comboParity->addItem("odd", PARENB|PARODD);
}


