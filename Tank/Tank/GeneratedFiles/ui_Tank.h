/********************************************************************************
** Form generated from reading UI file 'Tank.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TANK_H
#define UI_TANK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TankClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TankClass)
    {
        if (TankClass->objectName().isEmpty())
            TankClass->setObjectName(QString::fromUtf8("TankClass"));
        TankClass->resize(800, 600);
        menuBar = new QMenuBar(TankClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        TankClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TankClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TankClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TankClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        TankClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TankClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TankClass->setStatusBar(statusBar);

        retranslateUi(TankClass);

        QMetaObject::connectSlotsByName(TankClass);
    } // setupUi

    void retranslateUi(QMainWindow *TankClass)
    {
        TankClass->setWindowTitle(QCoreApplication::translate("TankClass", "Tank", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TankClass: public Ui_TankClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TANK_H
