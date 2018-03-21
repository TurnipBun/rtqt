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
    QPushButton *pushSend_1;
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
    QPushButton *pushSend_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelSendNum_2;
    QLCDNumber *lcdSendNum_2;
    QLabel *labelLostRate_2;
    QLCDNumber *lcdLostRate_2;
    QLabel *labelErrRate_2;
    QLCDNumber *lcdErrRate_2;
    QWidget *tabSerial;
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

        pushSend_1 = new QPushButton(groupChannel_1);
        pushSend_1->setObjectName(QString::fromUtf8("pushSend_1"));

        horizontalLayout_5->addWidget(pushSend_1);


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

        pushSend_2 = new QPushButton(groupChannel_2);
        pushSend_2->setObjectName(QString::fromUtf8("pushSend_2"));

        horizontalLayout_6->addWidget(pushSend_2);


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
        tabSerial = new QWidget();
        tabSerial->setObjectName(QString::fromUtf8("tabSerial"));
        tabWidget->addTab(tabSerial, QString());

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
        pushSend_1->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        labelSendNum_1->setText(QApplication::translate("MainWindow", "\345\217\221\345\214\205\344\270\252\346\225\260", 0, QApplication::UnicodeUTF8));
        labelLostRate_1->setText(QApplication::translate("MainWindow", "\344\270\242\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        labelErrRate_1->setText(QApplication::translate("MainWindow", "\351\224\231\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        groupChannel_2->setTitle(QApplication::translate("MainWindow", "\351\200\232\351\201\2232", 0, QApplication::UnicodeUTF8));
        labelSendData_2->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        labelRecvData_2->setText(QApplication::translate("MainWindow", "\346\216\245\346\224\266\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        pushSend_2->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        labelSendNum_2->setText(QApplication::translate("MainWindow", "\345\217\221\345\214\205\344\270\252\346\225\260", 0, QApplication::UnicodeUTF8));
        labelLostRate_2->setText(QApplication::translate("MainWindow", "\344\270\242\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        labelErrRate_2->setText(QApplication::translate("MainWindow", "\351\224\231\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabCAN), QApplication::translate("MainWindow", "&CAN\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabSerial), QApplication::translate("MainWindow", "&Serial\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
