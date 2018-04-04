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
    QLabel *labelBoudRate;
    QLabel *labelDataBit;
    QLabel *labelStopBit;
    QLabel *labelParity;
    QComboBox *comboBoudRate;
    QComboBox *comboDataBit;
    QComboBox *comboStopBit;
    QComboBox *comboParity;
    
    QVBoxLayout *vLayoutMain;
private:
    
    void addSettingelements();
    void fillComboContent();

    VxCom * vxCom;
};


#endif

