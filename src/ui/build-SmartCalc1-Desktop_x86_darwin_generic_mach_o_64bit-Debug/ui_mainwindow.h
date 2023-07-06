/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *PushButton_del;
    QPushButton *PushButton_plus_minus;
    QPushButton *PushButton_4;
    QPushButton *PushButton_5;
    QPushButton *PushButton_1;
    QPushButton *PushButton_0;
    QPushButton *PushButton_2;
    QPushButton *PushButton_percent;
    QPushButton *PushButton_6;
    QPushButton *PushButton_minus;
    QPushButton *PushButton_div;
    QPushButton *PushButton_3;
    QPushButton *PushButton_dot;
    QPushButton *PushButton_equals;
    QPushButton *PushButton_plus;
    QPushButton *PushButton_7;
    QPushButton *PushButton_mult;
    QPushButton *PushButton_8;
    QPushButton *PushButton_9;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(290, 385);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 271, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8(".AppleSystemUIFont")});
        font.setPointSize(20);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"  qproperty-alignment: 'AlignVCenter | AlignRight';\n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"background-color : white;"));
        PushButton_del = new QPushButton(centralwidget);
        PushButton_del->setObjectName(QString::fromUtf8("PushButton_del"));
        PushButton_del->setGeometry(QRect(10, 80, 61, 61));
        PushButton_plus_minus = new QPushButton(centralwidget);
        PushButton_plus_minus->setObjectName(QString::fromUtf8("PushButton_plus_minus"));
        PushButton_plus_minus->setGeometry(QRect(80, 80, 61, 61));
        PushButton_4 = new QPushButton(centralwidget);
        PushButton_4->setObjectName(QString::fromUtf8("PushButton_4"));
        PushButton_4->setGeometry(QRect(10, 200, 61, 61));
        PushButton_5 = new QPushButton(centralwidget);
        PushButton_5->setObjectName(QString::fromUtf8("PushButton_5"));
        PushButton_5->setGeometry(QRect(80, 200, 61, 61));
        PushButton_1 = new QPushButton(centralwidget);
        PushButton_1->setObjectName(QString::fromUtf8("PushButton_1"));
        PushButton_1->setGeometry(QRect(10, 260, 61, 61));
        PushButton_0 = new QPushButton(centralwidget);
        PushButton_0->setObjectName(QString::fromUtf8("PushButton_0"));
        PushButton_0->setGeometry(QRect(10, 320, 131, 61));
        PushButton_2 = new QPushButton(centralwidget);
        PushButton_2->setObjectName(QString::fromUtf8("PushButton_2"));
        PushButton_2->setGeometry(QRect(80, 260, 61, 61));
        PushButton_percent = new QPushButton(centralwidget);
        PushButton_percent->setObjectName(QString::fromUtf8("PushButton_percent"));
        PushButton_percent->setGeometry(QRect(150, 80, 61, 61));
        PushButton_6 = new QPushButton(centralwidget);
        PushButton_6->setObjectName(QString::fromUtf8("PushButton_6"));
        PushButton_6->setGeometry(QRect(150, 200, 61, 61));
        PushButton_minus = new QPushButton(centralwidget);
        PushButton_minus->setObjectName(QString::fromUtf8("PushButton_minus"));
        PushButton_minus->setGeometry(QRect(220, 200, 61, 61));
        PushButton_div = new QPushButton(centralwidget);
        PushButton_div->setObjectName(QString::fromUtf8("PushButton_div"));
        PushButton_div->setGeometry(QRect(220, 80, 61, 61));
        PushButton_3 = new QPushButton(centralwidget);
        PushButton_3->setObjectName(QString::fromUtf8("PushButton_3"));
        PushButton_3->setGeometry(QRect(150, 260, 61, 61));
        PushButton_dot = new QPushButton(centralwidget);
        PushButton_dot->setObjectName(QString::fromUtf8("PushButton_dot"));
        PushButton_dot->setGeometry(QRect(150, 320, 61, 61));
        PushButton_equals = new QPushButton(centralwidget);
        PushButton_equals->setObjectName(QString::fromUtf8("PushButton_equals"));
        PushButton_equals->setGeometry(QRect(220, 320, 61, 61));
        PushButton_plus = new QPushButton(centralwidget);
        PushButton_plus->setObjectName(QString::fromUtf8("PushButton_plus"));
        PushButton_plus->setGeometry(QRect(220, 260, 61, 61));
        PushButton_7 = new QPushButton(centralwidget);
        PushButton_7->setObjectName(QString::fromUtf8("PushButton_7"));
        PushButton_7->setGeometry(QRect(10, 140, 61, 61));
        PushButton_mult = new QPushButton(centralwidget);
        PushButton_mult->setObjectName(QString::fromUtf8("PushButton_mult"));
        PushButton_mult->setGeometry(QRect(220, 140, 61, 61));
        PushButton_8 = new QPushButton(centralwidget);
        PushButton_8->setObjectName(QString::fromUtf8("PushButton_8"));
        PushButton_8->setGeometry(QRect(80, 140, 61, 61));
        PushButton_9 = new QPushButton(centralwidget);
        PushButton_9->setObjectName(QString::fromUtf8("PushButton_9"));
        PushButton_9->setGeometry(QRect(150, 140, 61, 61));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        PushButton_del->setText(QCoreApplication::translate("MainWindow", "AC", nullptr));
        PushButton_plus_minus->setText(QCoreApplication::translate("MainWindow", "+/-", nullptr));
        PushButton_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        PushButton_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        PushButton_1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        PushButton_0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        PushButton_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        PushButton_percent->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        PushButton_6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        PushButton_minus->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        PushButton_div->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        PushButton_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        PushButton_dot->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        PushButton_equals->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        PushButton_plus->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        PushButton_7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        PushButton_mult->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        PushButton_8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        PushButton_9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
