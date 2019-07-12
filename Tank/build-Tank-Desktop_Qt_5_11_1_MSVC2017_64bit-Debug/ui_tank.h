/********************************************************************************
** Form generated from reading UI file 'tank.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TANK_H
#define UI_TANK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tank
{
public:
    QWidget *centralWidget;
    QPushButton *PVE;
    QPushButton *PVP;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Tank)
    {
        if (Tank->objectName().isEmpty())
            Tank->setObjectName(QStringLiteral("Tank"));
        Tank->resize(1960, 1080);
        centralWidget = new QWidget(Tank);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PVE = new QPushButton(centralWidget);
        PVE->setObjectName(QStringLiteral("PVE"));
        PVE->setGeometry(QRect(300, 775, 155, 67));
        PVE->setAutoDefault(false);
        PVE->setFlat(true);
        PVP = new QPushButton(centralWidget);
        PVP->setObjectName(QStringLiteral("PVP"));
        PVP->setGeometry(QRect(800, 775, 155, 67));
        PVP->setAutoDefault(false);
        PVP->setFlat(true);
        Tank->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Tank);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1960, 26));
        Tank->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Tank);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Tank->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Tank);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Tank->setStatusBar(statusBar);

        retranslateUi(Tank);

        PVE->setDefault(false);


        QMetaObject::connectSlotsByName(Tank);
    } // setupUi

    void retranslateUi(QMainWindow *Tank)
    {
        Tank->setWindowTitle(QApplication::translate("Tank", "\345\235\246\345\205\213\345\212\250\350\215\241", nullptr));
        PVE->setText(QString());
        PVP->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Tank: public Ui_Tank {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TANK_H
