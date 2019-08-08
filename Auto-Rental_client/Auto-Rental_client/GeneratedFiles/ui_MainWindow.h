/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *Title;
    QLabel *Lpic;
    QLineEdit *inID;
    QLineEdit *inPW;
    QPushButton *PBapply;
    QPushButton *PBapply_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(481, 630);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(72, 72, 72);\n"
"color: rgb(255, 255, 255);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Title = new QLabel(centralWidget);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setGeometry(QRect(80, 80, 321, 41));
        Title->setStyleSheet(QString::fromUtf8("font: 22pt \"\354\225\274\353\206\200\354\236\220 \354\225\274\354\262\264 B\";\n"
"color: rgb(255, 255, 255);"));
        Title->setAlignment(Qt::AlignCenter);
        Lpic = new QLabel(centralWidget);
        Lpic->setObjectName(QString::fromUtf8("Lpic"));
        Lpic->setGeometry(QRect(180, 190, 100, 100));
        inID = new QLineEdit(centralWidget);
        inID->setObjectName(QString::fromUtf8("inID"));
        inID->setGeometry(QRect(80, 360, 321, 43));
        inID->setStyleSheet(QString::fromUtf8("background-color: rgb(206, 206, 206);\n"
"font: 13pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\n"
"border-radius:5px;\n"
"color: rgb(0, 0, 0);"));
        inPW = new QLineEdit(centralWidget);
        inPW->setObjectName(QString::fromUtf8("inPW"));
        inPW->setGeometry(QRect(80, 420, 321, 43));
        inPW->setStyleSheet(QString::fromUtf8("background-color: rgb(206, 206, 206);\n"
"font: 13pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\n"
"border-radius:5px;\n"
"color: rgb(0, 0, 0);"));
        inPW->setEchoMode(QLineEdit::Password);
        inPW->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        PBapply = new QPushButton(centralWidget);
        PBapply->setObjectName(QString::fromUtf8("PBapply"));
        PBapply->setGeometry(QRect(240, 500, 161, 43));
        PBapply->setStyleSheet(QString::fromUtf8("background-color: rgb(127, 190, 0);\n"
"font: 13pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\n"
"color: rgb(72, 72, 72);\n"
"border-radius:5px;"));
        PBapply_2 = new QPushButton(centralWidget);
        PBapply_2->setObjectName(QString::fromUtf8("PBapply_2"));
        PBapply_2->setGeometry(QRect(80, 500, 161, 43));
        PBapply_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 182, 182);\n"
"font: 13pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\n"
"color: rgb(72, 72, 72);\n"
"border-radius:5px;"));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        Title->setText(QApplication::translate("MainWindow", "\354\230\244\355\206\240\353\240\214\355\203\210(Auto-Rental)", nullptr));
        Lpic->setText(QString());
        inID->setText(QString());
        PBapply->setText(QApplication::translate("MainWindow", "\354\213\240\354\262\255", nullptr));
        PBapply_2->setText(QApplication::translate("MainWindow", "\353\271\204\353\262\210\353\263\200\352\262\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
