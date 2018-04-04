/********************************************************************************
** Form generated from reading UI file 'formmodule.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMMODULE_H
#define UI_FORMMODULE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormModule
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupSetting;
    QVBoxLayout *verticalLayout;
    QPushButton *pushOpen;
    QPushButton *pushClose;
    QPushButton *pushAuto;
    QGroupBox *group1st;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *lineSend1st;
    QLabel *label_11;
    QLineEdit *lineRecv1st;
    QPushButton *pushSend1st;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QLCDNumber *lcdSendCount1st;
    QLabel *label_9;
    QLCDNumber *lcdLostRate1st;
    QLabel *label_10;
    QLCDNumber *lcdErrorRate1st;
    QGroupBox *group2nd;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *lineSend2nd;
    QLabel *label_4;
    QLineEdit *lineRecv2nd;
    QPushButton *pushSend2nd;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLCDNumber *lcdSendCount2nd;
    QLabel *label_6;
    QLCDNumber *lcdLostRate2nd;
    QLabel *label_7;
    QLCDNumber *lcdErrorRate2nd;

    void setupUi(QWidget *FormModule)
    {
        if (FormModule->objectName().isEmpty())
            FormModule->setObjectName(QString::fromUtf8("FormModule"));
        FormModule->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(FormModule);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupSetting = new QGroupBox(FormModule);
        groupSetting->setObjectName(QString::fromUtf8("groupSetting"));

        horizontalLayout->addWidget(groupSetting);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushOpen = new QPushButton(FormModule);
        pushOpen->setObjectName(QString::fromUtf8("pushOpen"));

        verticalLayout->addWidget(pushOpen);

        pushClose = new QPushButton(FormModule);
        pushClose->setObjectName(QString::fromUtf8("pushClose"));

        verticalLayout->addWidget(pushClose);

        pushAuto = new QPushButton(FormModule);
        pushAuto->setObjectName(QString::fromUtf8("pushAuto"));

        verticalLayout->addWidget(pushAuto);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        group1st = new QGroupBox(FormModule);
        group1st->setObjectName(QString::fromUtf8("group1st"));
        verticalLayout_3 = new QVBoxLayout(group1st);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(group1st);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        lineSend1st = new QLineEdit(group1st);
        lineSend1st->setObjectName(QString::fromUtf8("lineSend1st"));

        horizontalLayout_5->addWidget(lineSend1st);

        label_11 = new QLabel(group1st);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_5->addWidget(label_11);

        lineRecv1st = new QLineEdit(group1st);
        lineRecv1st->setObjectName(QString::fromUtf8("lineRecv1st"));

        horizontalLayout_5->addWidget(lineRecv1st);

        pushSend1st = new QPushButton(group1st);
        pushSend1st->setObjectName(QString::fromUtf8("pushSend1st"));

        horizontalLayout_5->addWidget(pushSend1st);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_8 = new QLabel(group1st);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_3->addWidget(label_8);

        lcdSendCount1st = new QLCDNumber(group1st);
        lcdSendCount1st->setObjectName(QString::fromUtf8("lcdSendCount1st"));

        horizontalLayout_3->addWidget(lcdSendCount1st);

        label_9 = new QLabel(group1st);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_3->addWidget(label_9);

        lcdLostRate1st = new QLCDNumber(group1st);
        lcdLostRate1st->setObjectName(QString::fromUtf8("lcdLostRate1st"));

        horizontalLayout_3->addWidget(lcdLostRate1st);

        label_10 = new QLabel(group1st);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_3->addWidget(label_10);

        lcdErrorRate1st = new QLCDNumber(group1st);
        lcdErrorRate1st->setObjectName(QString::fromUtf8("lcdErrorRate1st"));

        horizontalLayout_3->addWidget(lcdErrorRate1st);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout_2->addWidget(group1st);

        group2nd = new QGroupBox(FormModule);
        group2nd->setObjectName(QString::fromUtf8("group2nd"));
        verticalLayout_4 = new QVBoxLayout(group2nd);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(group2nd);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        lineSend2nd = new QLineEdit(group2nd);
        lineSend2nd->setObjectName(QString::fromUtf8("lineSend2nd"));

        horizontalLayout_4->addWidget(lineSend2nd);

        label_4 = new QLabel(group2nd);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        lineRecv2nd = new QLineEdit(group2nd);
        lineRecv2nd->setObjectName(QString::fromUtf8("lineRecv2nd"));

        horizontalLayout_4->addWidget(lineRecv2nd);

        pushSend2nd = new QPushButton(group2nd);
        pushSend2nd->setObjectName(QString::fromUtf8("pushSend2nd"));

        horizontalLayout_4->addWidget(pushSend2nd);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(group2nd);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        lcdSendCount2nd = new QLCDNumber(group2nd);
        lcdSendCount2nd->setObjectName(QString::fromUtf8("lcdSendCount2nd"));

        horizontalLayout_2->addWidget(lcdSendCount2nd);

        label_6 = new QLabel(group2nd);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        lcdLostRate2nd = new QLCDNumber(group2nd);
        lcdLostRate2nd->setObjectName(QString::fromUtf8("lcdLostRate2nd"));

        horizontalLayout_2->addWidget(lcdLostRate2nd);

        label_7 = new QLabel(group2nd);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_2->addWidget(label_7);

        lcdErrorRate2nd = new QLCDNumber(group2nd);
        lcdErrorRate2nd->setObjectName(QString::fromUtf8("lcdErrorRate2nd"));

        horizontalLayout_2->addWidget(lcdErrorRate2nd);


        verticalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(group2nd);


        retranslateUi(FormModule);

        QMetaObject::connectSlotsByName(FormModule);
    } // setupUi

    void retranslateUi(QWidget *FormModule)
    {
        FormModule->setWindowTitle(QApplication::translate("FormModule", "Form", 0, QApplication::UnicodeUTF8));
        groupSetting->setTitle(QApplication::translate("FormModule", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        pushOpen->setText(QApplication::translate("FormModule", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        pushClose->setText(QApplication::translate("FormModule", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
        pushAuto->setText(QApplication::translate("FormModule", "\350\207\252\345\212\250", 0, QApplication::UnicodeUTF8));
        group1st->setTitle(QApplication::translate("FormModule", "1st", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FormModule", "\345\217\221\351\200\201\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("FormModule", "\346\216\245\346\224\266\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        pushSend1st->setText(QApplication::translate("FormModule", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("FormModule", "\345\217\221\345\214\205\346\225\260", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("FormModule", "\344\270\242\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("FormModule", "\351\224\231\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        group2nd->setTitle(QApplication::translate("FormModule", "2nd", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FormModule", "\345\217\221\351\200\201\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FormModule", "\346\216\245\346\224\266\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        pushSend2nd->setText(QApplication::translate("FormModule", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FormModule", "\345\217\221\345\214\205\346\225\260", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FormModule", "\344\270\242\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FormModule", "\351\224\231\345\214\205\347\216\207", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormModule: public Ui_FormModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMMODULE_H
