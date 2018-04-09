#ifndef _COMWIDGET_HPP_
#define _COMWIDGET_HPP_
#include <QtGui>
#include "modulewidget.hpp"
#include "vxcom.hpp"

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

signals:
    void com1stSended();
    void com2ndSended();

public slots:
    void onPushOpenClicked();
    void onPushCloseClicked();
    void onPushAutoClicked();
    void onPushSend1stClicked();
    void onPushSend2ndClicked();

    void onCom1stSended();
    void onCom2ndSended();

private:
    void addSettings();
    void fillCombos();
    void connectSignalToSlot();
    int initComs(const string& com1stName, const string& com2ndName,
                         int baudRate, int dataBit, int stopBit, int parity);
    void clearComs();

    VxCom * com1st;
    VxCom * com2nd;
    QMessageBox msgBox;
};


#endif

