#ifndef _COMWIDGET_HPP_
#define _COMWIDGET_HPP_
#include <QtGui>
#include "modulewidget.hpp"

#ifdef VXWORKS
#include "vxcom.hpp"
#define DEF_COM VxCom
#else
#include "wincom.hpp"
#define DEF_COM WinCom
#endif


class ComWidget : public ModuleWidget
{
    Q_OBJECT
public:
    ComWidget();
    ~ComWidget();

    QHBoxLayout *hLayoutUp;
    QLabel *labelComName1st;
    QLabel *labelComName2nd;
    QComboBox *comboComName1st;
    QComboBox *comboComName2nd;
    
    QHBoxLayout *hLayoutDown;
    QLabel *labelBaudRate;
    QLabel *labelDataBit;
    QLabel *labelStopBit;
    QLabel *labelParity;
    QComboBox *comboBaudRate;
    QComboBox *comboDataBit;
    QComboBox *comboStopBit;
    QComboBox *comboParity;
    
    QVBoxLayout *vLayoutMain;

public slots:
    void onPushOpenClicked();

private:
    void addSettings();
    void fillCombos();
    void connectSignalToSlot();
    int initComms(const string& com1stName, const string& com2ndName,
                         int baudRate, int dataBit, int stopBit, int parity);

};


#endif

