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
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelCANDev;
    QComboBox *comboDevIndex;
    QPushButton *pushCANOpen;
    QPushButton *pushCANClose;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupChannel_1;
    QHBoxLayout *horizontalLayout;
    QLabel *labelSendData_1;
    QLineEdit *lineSendData_1;
    QLabel *labelRecvData_1;
    QLineEdit *lineRecvData_1;
    QPushButton *pushSend_1;
    QGroupBox *groupChannel_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelSendData_2;
    QLineEdit *lineSendData_2;
    QLabel *labelRecvData_2;
    QLineEdit *lineRecvData_2;
    QPushButton *pushSend_2;
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
        verticalLayout_2 = new QVBoxLayout(tabCAN);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelCANDev = new QLabel(tabCAN);
        labelCANDev->setObjectName(QString::fromUtf8("labelCANDev"));

        horizontalLayout_3->addWidget(labelCANDev);

        comboDevIndex = new QComboBox(tabCAN);
        comboDevIndex->setObjectName(QString::fromUtf8("comboDevIndex"));

        horizontalLayout_3->addWidget(comboDevIndex);

        pushCANOpen = new QPushButton(tabCAN);
        pushCANOpen->setObjectName(QString::fromUtf8("pushCANOpen"));

        horizontalLayout_3->addWidget(pushCANOpen);

        pushCANClose = new QPushButton(tabCAN);
        pushCANClose->setObjectName(QString::fromUtf8("pushCANClose"));
        pushCANClose->setEnabled(false);

        horizontalLayout_3->addWidget(pushCANClose);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_3);

        groupChannel_1 = new QGroupBox(tabCAN);
        groupChannel_1->setObjectName(QString::fromUtf8("groupChannel_1"));
        groupChannel_1->setEnabled(false);
        horizontalLayout = new QHBoxLayout(groupChannel_1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelSendData_1 = new QLabel(groupChannel_1);
        labelSendData_1->setObjectName(QString::fromUtf8("labelSendData_1"));

        horizontalLayout->addWidget(labelSendData_1);

        lineSendData_1 = new QLineEdit(groupChannel_1);
        lineSendData_1->setObjectName(QString::fromUtf8("lineSendData_1"));

        horizontalLayout->addWidget(lineSendData_1);

        labelRecvData_1 = new QLabel(groupChannel_1);
        labelRecvData_1->setObjectName(QString::fromUtf8("labelRecvData_1"));

        horizontalLayout->addWidget(labelRecvData_1);

        lineRecvData_1 = new QLineEdit(groupChannel_1);
        lineRecvData_1->setObjectName(QString::fromUtf8("lineRecvData_1"));

        horizontalLayout->addWidget(lineRecvData_1);

        pushSend_1 = new QPushButton(groupChannel_1);
        pushSend_1->setObjectName(QString::fromUtf8("pushSend_1"));

        horizontalLayout->addWidget(pushSend_1);


        verticalLayout_2->addWidget(groupChannel_1);

        groupChannel_2 = new QGroupBox(tabCAN);
        groupChannel_2->setObjectName(QString::fromUtf8("groupChannel_2"));
        groupChannel_2->setEnabled(false);
        horizontalLayout_2 = new QHBoxLayout(groupChannel_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelSendData_2 = new QLabel(groupChannel_2);
        labelSendData_2->setObjectName(QString::fromUtf8("labelSendData_2"));

        horizontalLayout_2->addWidget(labelSendData_2);

        lineSendData_2 = new QLineEdit(groupChannel_2);
        lineSendData_2->setObjectName(QString::fromUtf8("lineSendData_2"));

        horizontalLayout_2->addWidget(lineSendData_2);

        labelRecvData_2 = new QLabel(groupChannel_2);
        labelRecvData_2->setObjectName(QString::fromUtf8("labelRecvData_2"));

        horizontalLayout_2->addWidget(labelRecvData_2);

        lineRecvData_2 = new QLineEdit(groupChannel_2);
        lineRecvData_2->setObjectName(QString::fromUtf8("lineRecvData_2"));

        horizontalLayout_2->addWidget(lineRecvData_2);

        pushSend_2 = new QPushButton(groupChannel_2);
        pushSend_2->setObjectName(QString::fromUtf8("pushSend_2"));

        horizontalLayout_2->addWidget(pushSend_2);


        verticalLayout_2->addWidget(groupChannel_2);

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
        pushCANOpen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        pushCANClose->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
        groupChannel_1->setTitle(QApplication::translate("MainWindow", "\351\200\232\351\201\2231", 0, QApplication::UnicodeUTF8));
        labelSendData_1->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        labelRecvData_1->setText(QApplication::translate("MainWindow", "\346\216\245\346\224\266\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        pushSend_1->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        groupChannel_2->setTitle(QApplication::translate("MainWindow", "\351\200\232\351\201\2232", 0, QApplication::UnicodeUTF8));
        labelSendData_2->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        labelRecvData_2->setText(QApplication::translate("MainWindow", "\346\216\245\346\224\266\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        pushSend_2->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
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
