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
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QScrollArea *listscrollArea;
    QWidget *scrollContents;
    QLabel *Llistname;
    QLabel *Ldate;
    QPushButton *PBexcelsto;
    QPushButton *PBwoman;
    QPushButton *PBman;
    QPushButton *PBben;
    QLineEdit *LEclass;
    QLabel *Lclass;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(481, 630);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(72, 72, 72);\n"
"color: rgb(255, 255, 255);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        listscrollArea = new QScrollArea(centralWidget);
        listscrollArea->setObjectName(QString::fromUtf8("listscrollArea"));
        listscrollArea->setGeometry(QRect(80, 150, 321, 361));
        listscrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(206, 206, 206);\n"
"font: 12pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\n"
""));
        listscrollArea->setWidgetResizable(true);
        scrollContents = new QWidget();
        scrollContents->setObjectName(QString::fromUtf8("scrollContents"));
        scrollContents->setGeometry(QRect(0, 0, 319, 359));
        listscrollArea->setWidget(scrollContents);
        Llistname = new QLabel(centralWidget);
        Llistname->setObjectName(QString::fromUtf8("Llistname"));
        Llistname->setGeometry(QRect(80, 120, 321, 31));
        Llistname->setStyleSheet(QString::fromUtf8("font: 12pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(124, 124, 124);"));
        Ldate = new QLabel(centralWidget);
        Ldate->setObjectName(QString::fromUtf8("Ldate"));
        Ldate->setGeometry(QRect(260, 40, 141, 39));
        QFont font;
        font.setFamily(QString::fromUtf8("08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B"));
        font.setPointSize(13);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        Ldate->setFont(font);
        Ldate->setContextMenuPolicy(Qt::PreventContextMenu);
        Ldate->setStyleSheet(QString::fromUtf8("font: 13pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\n"
"color: rgb(206, 206, 206);"));
        PBexcelsto = new QPushButton(centralWidget);
        PBexcelsto->setObjectName(QString::fromUtf8("PBexcelsto"));
        PBexcelsto->setGeometry(QRect(80, 560, 321, 31));
        PBexcelsto->setStyleSheet(QString::fromUtf8("background-color: rgb(127, 190, 0);\n"
"font: 12pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\n"
"border-radius:5px;\n"
"color: rgb(0, 0, 0);\n"
""));
        PBwoman = new QPushButton(centralWidget);
        PBwoman->setObjectName(QString::fromUtf8("PBwoman"));
        PBwoman->setGeometry(QRect(290, 80, 111, 31));
        PBwoman->setStyleSheet(QString::fromUtf8("background-color: rgb(157, 105, 157);\n"
"font: 12pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\n"
"border-radius:5px;\n"
"color: rgb(206, 206, 206);"));
        PBman = new QPushButton(centralWidget);
        PBman->setObjectName(QString::fromUtf8("PBman"));
        PBman->setGeometry(QRect(170, 80, 111, 31));
        PBman->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 108, 162);\n"
"font: 12pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\n"
"border-radius:5px;\n"
"color: rgb(206, 206, 206);\n"
""));
        PBben = new QPushButton(centralWidget);
        PBben->setObjectName(QString::fromUtf8("PBben"));
        PBben->setGeometry(QRect(310, 520, 91, 31));
        PBben->setAutoFillBackground(false);
        PBben->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(180, 60, 0);\n"
"font: 12pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\n"
"border-radius:5px;\n"
"color: rgb(206, 206, 206);"));
        LEclass = new QLineEdit(centralWidget);
        LEclass->setObjectName(QString::fromUtf8("LEclass"));
        LEclass->setGeometry(QRect(140, 520, 161, 31));
        LEclass->setStyleSheet(QString::fromUtf8("background-color: rgb(206, 206, 206);\n"
"font: 12pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\n"
"border-radius:5px;\n"
"color: rgb(0, 0, 0);"));
        Lclass = new QLabel(centralWidget);
        Lclass->setObjectName(QString::fromUtf8("Lclass"));
        Lclass->setGeometry(QRect(80, 520, 61, 31));
        Lclass->setStyleSheet(QString::fromUtf8("font: 12pt \"08\354\204\234\354\232\270\353\202\250\354\202\260\354\262\264 B\";\n"
"color: rgb(206, 206, 206);"));
        Lclass->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        Llistname->setText(QApplication::translate("MainWindow", "  \355\225\231\353\262\210               \354\204\261\353\263\204               \354\235\264\353\246\204", nullptr));
        Ldate->setText(QString());
        PBexcelsto->setText(QApplication::translate("MainWindow", "\353\254\270\354\204\234 \354\240\200\354\236\245", nullptr));
        PBwoman->setText(QApplication::translate("MainWindow", "\354\227\254\354\236\220", nullptr));
        PBman->setText(QApplication::translate("MainWindow", "\353\202\250\354\236\220", nullptr));
        PBben->setText(QApplication::translate("MainWindow", "\353\214\200\354\227\254\352\270\210\354\247\200", nullptr));
        Lclass->setText(QApplication::translate("MainWindow", "  \355\225\231\353\262\210   ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
