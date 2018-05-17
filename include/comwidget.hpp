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
    QLabel *labelComReceiver;
    QLabel *labelComSender;
    QComboBox *comboComReceiver;
    QComboBox *comboComSender;
    
    QHBoxLayout *hLayoutDown;
    QLabel *labelBaudRate;
    QLabel *labelDataBit;
    QLabel *labelStopBit;
    QLabel *labelParity;
    QComboBox *comboBaudRate;
    QComboBox *comboDataBit;
    QComboBox *comboStopBit;
    QComboBox *comboParity;
    QCheckBox *checkRts;
    
    QVBoxLayout *vLayoutMain;

public slots:
    void on_pushOpen_clicked();
    void on_pushClose_clicked();

private:
    void addSettings();
    void fillCombos();
    int initComms(const string& com1stName, const string& com2ndName, bool isRtsOn,
                         int baudRate, int dataBit, int stopBit, int parity);

};


#endif

