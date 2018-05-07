#ifndef _CANWIDGET_HPP_
#define _CANWIDGET_HPP_
#include <QtGui>
#include <can.hpp>
#include "modulewidget.hpp"

class CanWidget : public ModuleWidget
{
    Q_OBJECT
public:
    CanWidget();
    ~CanWidget();

    QLabel *labelCanPairDev;
    QComboBox *comboCanPairDev;
    QLabel *labelBaudRate;
    QComboBox *comboBaudRate;
    
    QHBoxLayout *hLayout;

public slots:
    void on_pushOpen_clicked();
    void on_pushClose_clicked();

private:
    void addSettings();
    void fillCombos();
    int initComms(int devno, int baudRate);

    QMessageBox msgBox;
};

#endif

