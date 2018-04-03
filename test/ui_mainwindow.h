/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAboutSoftware;
    QAction *actionAboutCompany;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabCAN;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelCANDev;
    QComboBox *comboDevIndex;
    QLabel *labelCANRate;
    QComboBox *comboCANRate;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushCANOpen;
    QPushButton *pushCANClose;
    QGroupBox *groupChannel_1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelSendData_1;
    QLineEdit *lineSendData_1;
    QLabel *labelRecvData_1;
    QLineEdit *lineRecvData_1;
    QPushButton *pushCANSend1;
    QHBoxLayout *horizontalLayout;
    QLabel *labelSendNum_1;
    QLCDNumber *lcdSendNum_1;
    QLabel *labelLostRate_1;
    QLCDNumber *lcdLostRate_1;
    QLabel *labelErrRate_1;
    QLCDNumber *lcdErrRate_1;
    QGroupBox *groupChannel_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelSendData_2;
    QLineEdit *lineSendData_2;
    QLabel *labelRecvData_2;
    QLineEdit *lineRecvData_2;
    QPushButton *pushCANSend2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelSendNum_2;
    QLCDNumber *lcdSendNum_2;
    QLabel *labelLostRate_2;
    QLCDNumber *lcdLostRate_2;
    QLabel *labelErrRate_2;
    QLCDNumber *lcdErrRate_2;
    QWidget *tabCOM;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupSetting;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelCOM1;
    QComboBox *comboCOMName1;
    QLabel *labelCOM2;
    QComboBox *comboCOMName2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushCOMOpen;
    QPushButton *pushCOMClose;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelRate;
    QComboBox *comboRate;
    QLabel *labelDataBit;
    QComboBox *comboDataBit;
    QLabel *labelStopBit;
    QComboBox *comboStopBit;
    QLabel *labelParity;
    QComboBox *comboParity;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupCOM1;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelCOMSendData1;
    QLineEdit *lineCOMSendData1;
    QLabel *labelCOMRecvData1;
    QLineEdit *lineCOMRecvData1;
    QPushButton *pushCOMSend1;
    QHBoxLayout *horizontalLayout_9;
    QLabel *labelCOMSendNum1;
    QLCDNumber *lcdCOMSendNum1;
    QLabel *labelCOMLostRate1;
    QLCDNumber *lcdCOMLostRate1;
    QLabel *labelCOMErrRate1;
    QLCDNumber *lcdCOMErrRate1;
    QGroupBox *groupCOM2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_10;
    QLabel *labelCOMSendData2;
    QLineEdit *lineCOMSendData2;
    QLabel *labelCOMRecvData2;
    QLineEdit *lineCOMRecvData2;
    QPushButton *pushCOMSend2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *labelCOMSendNum2;
    QLCDNumber *lcdCOMSendNum2;
    QLabel *labelCOMLostRate2;
    QLCDNumber *lcdCOMLostRate2;
    QLabel *labelCOMErrRate2;
    QLCDNumber *lcdCOMErrRate2;
    QMenuBar *menubar;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(678, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionAboutSoftware = new QAction(MainWindow);
        actionAboutSoftware->setObjectName(QString::fromUtf8("actionAboutSoftware"));
        actionAboutCompany = new QAction(MainWindow);
        actionAboutCompany->setObjectName(QString::fromUtf8("actionAboutCompany"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabCAN = new QWidget();
        tabCAN->setObjectName(QString::fromUtf8("tabCAN"));
        verticalLayout_4 = new QVBoxLayout(tabCAN);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelCANDev = new QLabel(tabCAN);
        labelCANDev->setObjectName(QString::fromUtf8("labelCANDev"));

        horizontalLayout_3->addWidget(labelCANDev);

        comboDevIndex = new QComboBox(tabCAN);
        comboDevIndex->setObjectName(QString::fromUtf8("comboDevIndex"));

        horizontalLayout_3->addWidget(comboDevIndex);

        labelCANRate = new QLabel(tabCAN);
        labelCANRate->setObjectName(QString::fromUtf8("labelCANRate"));

        horizontalLayout_3->addWidget(labelCANRate);

        comboCANRate = new QComboBox(tabCAN);
        comboCANRate->setObjectName(QString::fromUtf8("comboCANRate"));
        comboCANRate->setMaxVisibleItems(10);

        horizontalLayout_3->addWidget(comboCANRate);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pushCANOpen = new QPushButton(tabCAN);
        pushCANOpen->setObjectName(QString::fromUtf8("pushCANOpen"));

        horizontalLayout_3->addWidget(pushCANOpen);

        pushCANClose = new QPushButton(tabCAN);
        pushCANClose->setObjectName(QString::fromUtf8("pushCANClose"));
        pushCANClose->setEnabled(false);

        horizontalLayout_3->addWidget(pushCANClose);


        verticalLayout_4->addLayout(horizontalLayout_3);

        groupChannel_1 = new QGroupBox(tabCAN);
        groupChannel_1->setObjectName(QString::fromUtf8("groupChannel_1"));
        groupChannel_1->setEnabled(false);
        verticalLayout_2 = new QVBoxLayout(groupChannel_1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        labelSendData_1 = new QLabel(groupChannel_1);
        labelSendData_1->setObjectName(QString::fromUtf8("labelSendData_1"));

        horizontalLayout_5->addWidget(labelSendData_1);

        lineSendData_1 = new QLineEdit(groupChannel_1);
        lineSendData_1->setObjectName(QString::fromUtf8("lineSendData_1"));

        horizontalLayout_5->addWidget(lineSendData_1);

        labelRecvData_1 = new QLabel(groupChannel_1);
        labelRecvData_1->setObjectName(QString::fromUtf8("labelRecvData_1"));

        horizontalLayout_5->addWidget(labelRecvData_1);

        lineRecvData_1 = new QLineEdit(groupChannel_1);
        lineRecvData_1->setObjectName(QString::fromUtf8("lineRecvData_1"));

        horizontalLayout_5->addWidget(lineRecvData_1);

        pushCANSend1 = new QPushButton(groupChannel_1);
        pushCANSend1->setObjectName(QString::fromUtf8("pushCANSend1"));

        horizontalLayout_5->addWidget(pushCANSend1);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelSendNum_1 = new QLabel(groupChannel_1);
        labelSendNum_1->setObjectName(QString::fromUtf8("labelSendNum_1"));

        horizontalLayout->addWidget(labelSendNum_1);

        lcdSendNum_1 = new QLCDNumber(groupChannel_1);
        lcdSendNum_1->setObjectName(QString::fromUtf8("lcdSendNum_1"));

        horizontalLayout->addWidget(lcdSendNum_1);

        labelLostRate_1 = new QLabel(groupChannel_1);
        labelLostRate_1->setObjectName(QString::fromUtf8("labelLostRate_1"));

        horizontalLayout->addWidget(labelLostRate_1);

        lcdLostRate_1 = new QLCDNumber(groupChannel_1);
        lcdLostRate_1->setObjectName(QString::fromUtf8("lcdLostRate_1"));

        horizontalLayout->addWidget(lcdLostRate_1);

        labelErrRate_1 = new QLabel(groupChannel_1);
        labelErrRate_1->setObjectName(QString::fromUtf8("labelErrRate_1"));

        horizontalLayout->addWidget(labelErrRate_1);

        lcdErrRate_1 = new QLCDNumber(groupChannel_1);
        lcdErrRate_1->setObjectName(QString::fromUtf8("lcdErrRate_1"));

        horizontalLayout->addWidget(lcdErrRate_1);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(groupChannel_1);

        groupChannel_2 = new QGroupBox(tabCAN);
        groupChannel_2->setObjectName(QString::fromUtf8("groupChannel_2"));
        groupChannel_2->setEnabled(false);
        verticalLayout_3 = new QVBoxLayout(groupChannel_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        labelSendData_2 = new QLabel(groupChannel_2);
        labelSendData_2->setObjectName(QString::fromUtf8("labelSendData_2"));

        horizontalLayout_6->addWidget(labelSendData_2);

        lineSendData_2 = new QLineEdit(groupChannel_2);
        lineSendData_2->setObjectName(QString::fromUtf8("lineSendData_2"));

        horizontalLayout_6->addWidget(lineSendData_2);

        labelRecvData_2 = new QLabel(groupChannel_2);
        labelRecvData_2->setObjectName(QString::fromUtf8("labelRecvData_2"));

        horizontalLayout_6->addWidget(labelRecvData_2);

        lineRecvData_2 = new QLineEdit(groupChannel_2);
        lineRecvData_2->setObjectName(QString::fromUtf8("lineRecvData_2"));

        horizontalLayout_6->addWidget(lineRecvData_2);

        pushCANSend2 = new QPushButton(groupChannel_2);
        pushCANSend2->setObjectName(QString::fromUtf8("pushCANSend2"));

        horizontalLayout_6->addWidget(pushCANSend2);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelSendNum_2 = new QLabel(groupChannel_2);
        labelSendNum_2->setObjectName(QString::fromUtf8("labelSendNum_2"));

        horizontalLayout_2->addWidget(labelSendNum_2);

        lcdSendNum_2 = new QLCDNumber(groupChannel_2);
        lcdSendNum_2->setObjectName(QString::fromUtf8("lcdSendNum_2"));

        horizontalLayout_2->addWidget(lcdSendNum_2);

        labelLostRate_2 = new QLabel(groupChannel_2);
        labelLostRate_2->setObjectName(QString::fromUtf8("labelLostRate_2"));

        horizontalLayout_2->addWidget(labelLostRate_2);

        lcdLostRate_2 = new QLCDNumber(groupChannel_2);
        lcdLostRate_2->setObjectName(QString::fromUtf8("lcdLostRate_2"));

        horizontalLayout_2->addWidget(lcdLostRate_2);

        labelErrRate_2 = new QLabel(groupChannel_2);
        labelErrRate_2->setObjectName(QString::fromUtf8("labelErrRate_2"));

        horizontalLayout_2->addWidget(labelErrRate_2);

        lcdErrRate_2 = new QLCDNumber(groupChannel_2);
        lcdErrRate_2->setObjectName(QString::fromUtf8("lcdErrRate_2"));

        horizontalLayout_2->addWidget(lcdErrRate_2);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_4->addWidget(groupChannel_2);

        tabWidget->addTab(tabCAN, QString());
        tabCOM = new QWidget();
        tabCOM->setObjectName(QString::fromUtf8("tabCOM"));
        verticalLayout_8 = new QVBoxLayout(tabCOM);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        groupSetting = new QGroupBox(tabCOM);
        groupSetting->setObjectName(QString::fromUtf8("groupSetting"));
        verticalLayout_5 = new QVBoxLayout(groupSetting);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        labelCOM1 = new QLabel(groupSetting);
        labelCOM1->setObjectName(QString::fromUtf8("labelCOM1"));

        horizontalLayout_7->addWidget(labelCOM1);

        comboCOMName1 = new QComboBox(groupSetting);
        comboCOMName1->setObjectName(QString::fromUtf8("comboCOMName1"));

        horizontalLayout_7->addWidget(comboCOMName1);

        labelCOM2 = new QLabel(groupSetting);
        labelCOM2->setObjectName(QString::fromUtf8("labelCOM2"));

        horizontalLayout_7->addWidget(labelCOM2);

        comboCOMName2 = new QComboBox(groupSetting);
        comboCOMName2->setObjectName(QString::fromUtf8("comboCOMName2"));

        horizontalLayout_7->addWidget(comboCOMName2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        pushCOMOpen = new QPushButton(groupSetting);
        pushCOMOpen->setObjectName(QString::fromUtf8("pushCOMOpen"));

        horizontalLayout_7->addWidget(pushCOMOpen);

        pushCOMClose = new QPushButton(groupSetting);
        pushCOMClose->setObjectName(QString::fromUtf8("pushCOMClose"));
        pushCOMClose->setEnabled(false);

        horizontalLayout_7->addWidget(pushCOMClose);


        verticalLayout_5->addLayout(horizontalLayout_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        labelRate = new QLabel(groupSetting);
        labelRate->setObjectName(QString::fromUtf8("labelRate"));

        horizontalLayout_4->addWidget(labelRate);

        comboRate = new QComboBox(groupSetting);
        comboRate->setObjectName(QString::fromUtf8("comboRate"));

        horizontalLayout_4->addWidget(comboRate);

        labelDataBit = new QLabel(groupSetting);
        labelDataBit->setObjectName(QString::fromUtf8("labelDataBit"));

        horizontalLayout_4->addWidget(labelDataBit);

        comboDataBit = new QComboBox(groupSetting);
        comboDataBit->setObjectName(QString::fromUtf8("comboDataBit"));

        horizontalLayout_4->addWidget(comboDataBit);

        labelStopBit = new QLabel(groupSetting);
        labelStopBit->setObjectName(QString::fromUtf8("labelStopBit"));

        horizontalLayout_4->addWidget(labelStopBit);

        comboStopBit = new QComboBox(groupSetting);
        comboStopBit->setObjectName(QString::fromUtf8("comboStopBit"));

        horizontalLayout_4->addWidget(comboStopBit);

        labelParity = new QLabel(groupSetting);
        labelParity->setObjectName(QString::fromUtf8("labelParity"));

        horizontalLayout_4->addWidget(labelParity);

        comboParity = new QComboBox(groupSetting);
        comboParity->setObjectName(QString::fromUtf8("comboParity"));

        horizontalLayout_4->addWidget(comboParity);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout_8->addWidget(groupSetting);

        groupCOM1 = new QGroupBox(tabCOM);
        groupCOM1->setObjectName(QString::fromUtf8("groupCOM1"));
        groupCOM1->setEnabled(false);
        verticalLayout_6 = new QVBoxLayout(groupCOM1);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        labelCOMSendData1 = new QLabel(groupCOM1);
        labelCOMSendData1->setObjectName(QString::fromUtf8("labelCOMSendData1"));

        horizontalLayout_8->addWidget(labelCOMSendData1);

        lineCOMSendData1 = new QLineEdit(groupCOM1);
        lineCOMSendData1->setObjectName(QString::fromUtf8("lineCOMSendData1"));

        horizontalLayout_8->addWidget(lineCOMSendData1);

        labelCOMRecvData1 = new QLabel(groupCOM1);
        labelCOMRecvData1->setObjectName(QString::fromUtf8("labelCOMRecvData1"));

        horizontalLayout_8->addWidget(labelCOMRecvData1);

        lineCOMRecvData1 = new QLineEdit(groupCOM1);
        lineCOMRecvData1->setObjectName(QString::fromUtf8("lineCOMRecvData1"));

        horizontalLayout_8->addWidget(lineCOMRecvData1);

        pushCOMSend1 = new QPushButton(groupCOM1);
        pushCOMSend1->setObjectName(QString::fromUtf8("pushCOMSend1"));

        horizontalLayout_8->addWidget(pushCOMSend1);


        verticalLayout_6->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        labelCOMSendNum1 = new QLabel(groupCOM1);
        labelCOMSendNum1->setObjectName(QString::fromUtf8("labelCOMSendNum1"));

        horizontalLayout_9->addWidget(labelCOMSendNum1);

        lcdCOMSendNum1 = new QLCDNumber(groupCOM1);
        lcdCOMSendNum1->setObjectName(QString::fromUtf8("lcdCOMSendNum1"));

        horizontalLayout_9->addWidget(lcdCOMSendNum1);

        labelCOMLostRate1 = new QLabel(groupCOM1);
        labelCOMLostRate1->setObjectName(QString::fromUtf8("labelCOMLostRate1"));

        horizontalLayout_9->addWidget(labelCOMLostRate1);

        lcdCOMLostRate1 = new QLCDNumber(groupCOM1);
        lcdCOMLostRate1->setObjectName(QString::fromUtf8("lcdCOMLostRate1"));

        horizontalLayout_9->addWidget(lcdCOMLostRate1);

        labelCOMErrRate1 = new QLabel(groupCOM1);
        labelCOMErrRate1->setObjectName(QString::fromUtf8("labelCOMErrRate1"));

        horizontalLayout_9->addWidget(labelCOMErrRate1);

        lcdCOMErrRate1 = new QLCDNumber(groupCOM1);
        lcdCOMErrRate1->setObjectName(QString::fromUtf8("lcdCOMErrRate1"));

        horizontalLayout_9->addWidget(lcdCOMErrRate1);


        verticalLayout_6->addLayout(horizontalLayout_9);


        verticalLayout_8->addWidget(groupCOM1);

        groupCOM2 = new QGroupBox(tabCOM);
        groupCOM2->setObjectName(QString::fromUtf8("groupCOM2"));
        groupCOM2->setEnabled(false);
        verticalLayout_7 = new QVBoxLayout(groupCOM2);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        labelCOMSendData2 = new QLabel(groupCOM2);
        labelCOMSendData2->setObjectName(QString::fromUtf8("labelCOMSendData2"));

        horizontalLayout_10->addWidget(labelCOMSendData2);

        lineCOMSendData2 = new QLineEdit(groupCOM2);
        lineCOMSendData2->setObjectName(QString::fromUtf8("lineCOMSendData2"));

        horizontalLayout_10->addWidget(lineCOMSendData2);

        labelCOMRecvData2 = new QLabel(groupCOM2);
        labelCOMRecvData2->setObjectName(QString::fromUtf8("labelCOMRecvData2"));

        horizontalLayout_10->addWidget(labelCOMRecvData2);

        lineCOMRecvData2 = new QLineEdit(groupCOM2);
        lineCOMRecvData2->setObjectName(QString::fromUtf8("lineCOMRecvData2"));

        horizontalLayout_10->addWidget(lineCOMRecvData2);

        pushCOMSend2 = new QPushButton(groupCOM2);
        pushCOMSend2->setObjectName(QString::fromUtf8("pushCOMSend2"));

        horizontalLayout_10->addWidget(pushCOMSend2);


        verticalLayout_7->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        labelCOMSendNum2 = new QLabel(groupCOM2);
        labelCOMSendNum2->setObjectName(QString::fromUtf8("labelCOMSendNum2"));

        horizontalLayout_11->addWidget(labelCOMSendNum2);

        lcdCOMSendNum2 = new QLCDNumber(groupCOM2);
        lcdCOMSendNum2->setObjectName(QString::fromUtf8("lcdCOMSendNum2"));

        horizontalLayout_11->addWidget(lcdCOMSendNum2);

        labelCOMLostRate2 = new QLabel(groupCOM2);
        labelCOMLostRate2->setObjectName(QString::fromUtf8("labelCOMLostRate2"));

        horizontalLayout_11->addWidget(labelCOMLostRate2);

        lcdCOMLostRate2 = new QLCDNumber(groupCOM2);
        lcdCOMLostRate2->setObjectName(QString::fromUtf8("lcdCOMLostRate2"));

        horizontalLayout_11->addWidget(lcdCOMLostRate2);

        labelCOMErrRate2 = new QLabel(groupCOM2);
        labelCOMErrRate2->setObjectName(QString::fromUtf8("labelCOMErrRate2"));

        horizontalLayout_11->addWidget(labelCOMErrRate2);

        lcdCOMErrRate2 = new QLCDNumber(groupCOM2);
        lcdCOMErrRate2->setObjectName(QString::fromUtf8("lcdCOMErrRate2"));

        horizontalLayout_11->addWidget(lcdCOMErrRate2);


        verticalLayout_7->addLayout(horizontalLayout_11);


        verticalLayout_8->addWidget(groupCOM2);

        tabWidget->addTab(tabCOM, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 678, 23));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuAbout->menuAction());
        menuAbout->addAction(actionAboutSoftware);
        menuAbout->addAction(actionAboutCompany);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        comboCANRate->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "rtqt", 0, QApplication::UnicodeUTF8));
        actionAboutSoftware->setText(QApplication::translate("MainWindow", "Software", 0, QApplication::UnicodeUTF8));
        actionAboutCompany->setText(QApplication::translate("MainWindow", "Company", 0, QApplication::UnicodeUTF8));
        labelCANDev->setText(QApplication::translate("MainWindow", "CAN\345\215\241\350\256\276\345\244\207\345\217\267", 0, QApplication::UnicodeUTF8));
        comboDevIndex->clear();
        comboDevIndex->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "7", 0, QApplication::UnicodeUTF8)
        );
        labelCANRate->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", 0, QApplication::UnicodeUTF8));
        comboCANRate->clear();
        comboCANRate->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "50", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "100", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "125", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "250", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "500", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1000", 0, QApplication::UnicodeUTF8)
        );
        pushCANOpen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        pushCANClose->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
        groupChannel_1->setTitle(QApplication::translate("MainWindow", "\351\200\232\351\201\2231", 0, QApplication::UnicodeUTF8));
        labelSendData_1->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        labelRecvData_1->setText(QApplication::translate("MainWindow", "\346\216\245\346\224\266\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        pushCANSend1->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        labelSendNum_1->setText(QApplication::translate("MainWindow", "\345\217\221\345\214\205\344\270\252\346\225\260", 0, QApplication::UnicodeUTF8));
        labelLostRate_1->setText(QApplication::translate("MainWindow", "\344\270\242\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        labelErrRate_1->setText(QApplication::translate("MainWindow", "\351\224\231\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        groupChannel_2->setTitle(QApplication::translate("MainWindow", "\351\200\232\351\201\2232", 0, QApplication::UnicodeUTF8));
        labelSendData_2->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        labelRecvData_2->setText(QApplication::translate("MainWindow", "\346\216\245\346\224\266\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        pushCANSend2->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        labelSendNum_2->setText(QApplication::translate("MainWindow", "\345\217\221\345\214\205\344\270\252\346\225\260", 0, QApplication::UnicodeUTF8));
        labelLostRate_2->setText(QApplication::translate("MainWindow", "\344\270\242\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        labelErrRate_2->setText(QApplication::translate("MainWindow", "\351\224\231\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabCAN), QApplication::translate("MainWindow", "&CAN\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        groupSetting->setTitle(QApplication::translate("MainWindow", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        labelCOM1->setText(QApplication::translate("MainWindow", "\344\270\262\345\217\2431", 0, QApplication::UnicodeUTF8));
        labelCOM2->setText(QApplication::translate("MainWindow", "\344\270\262\345\217\2432", 0, QApplication::UnicodeUTF8));
        pushCOMOpen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        pushCOMClose->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
        labelRate->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", 0, QApplication::UnicodeUTF8));
        comboRate->clear();
        comboRate->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "110", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "300", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "4800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "14400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "38400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "56000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "57600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "115200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "128000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "256000", 0, QApplication::UnicodeUTF8)
        );
        labelDataBit->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", 0, QApplication::UnicodeUTF8));
        comboDataBit->clear();
        comboDataBit->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "8", 0, QApplication::UnicodeUTF8)
        );
        labelStopBit->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", 0, QApplication::UnicodeUTF8));
        comboStopBit->clear();
        comboStopBit->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "One", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Onehalf", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Two", 0, QApplication::UnicodeUTF8)
        );
        labelParity->setText(QApplication::translate("MainWindow", "\346\240\241\351\252\214\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
        comboParity->clear();
        comboParity->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Even", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Odd", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Mark", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Space", 0, QApplication::UnicodeUTF8)
        );
        groupCOM1->setTitle(QApplication::translate("MainWindow", "\344\270\262\345\217\2431", 0, QApplication::UnicodeUTF8));
        labelCOMSendData1->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        labelCOMRecvData1->setText(QApplication::translate("MainWindow", "\346\216\245\346\224\266\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        pushCOMSend1->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        labelCOMSendNum1->setText(QApplication::translate("MainWindow", "\345\217\221\345\214\205\344\270\252\346\225\260", 0, QApplication::UnicodeUTF8));
        labelCOMLostRate1->setText(QApplication::translate("MainWindow", "\344\270\242\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        labelCOMErrRate1->setText(QApplication::translate("MainWindow", "\351\224\231\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        groupCOM2->setTitle(QApplication::translate("MainWindow", "\344\270\262\345\217\2432", 0, QApplication::UnicodeUTF8));
        labelCOMSendData2->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        labelCOMRecvData2->setText(QApplication::translate("MainWindow", "\346\216\245\346\224\266\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        pushCOMSend2->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        labelCOMSendNum2->setText(QApplication::translate("MainWindow", "\345\217\221\345\214\205\344\270\252\346\225\260", 0, QApplication::UnicodeUTF8));
        labelCOMLostRate2->setText(QApplication::translate("MainWindow", "\344\270\242\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        labelCOMErrRate2->setText(QApplication::translate("MainWindow", "\351\224\231\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabCOM), QApplication::translate("MainWindow", "&COM\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
