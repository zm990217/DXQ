/********************************************************************************
** Form generated from reading UI file 'pvewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PVEWINDOW_H
#define UI_PVEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PVEWindow
{
public:
    QPushButton *backMain;
    QLabel *label;

    void setupUi(QWidget *PVEWindow)
    {
        if (PVEWindow->objectName().isEmpty())
            PVEWindow->setObjectName(QStringLiteral("PVEWindow"));
        PVEWindow->resize(1920, 1080);
        backMain = new QPushButton(PVEWindow);
        backMain->setObjectName(QStringLiteral("backMain"));
        backMain->setGeometry(QRect(790, 770, 401, 181));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        font.setPointSize(30);
        backMain->setFont(font);
        label = new QLabel(PVEWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(820, 320, 320, 121));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        font1.setPointSize(32);
        label->setFont(font1);

        retranslateUi(PVEWindow);

        QMetaObject::connectSlotsByName(PVEWindow);
    } // setupUi

    void retranslateUi(QWidget *PVEWindow)
    {
        PVEWindow->setWindowTitle(QApplication::translate("PVEWindow", "\345\235\246\345\205\213\345\244\247\346\210\230\357\274\232\344\272\272\346\234\272\345\257\271\346\210\230", nullptr));
        backMain->setText(QApplication::translate("PVEWindow", "\350\277\224\345\233\236\344\270\273\350\217\234\345\215\225", nullptr));
        label->setText(QApplication::translate("PVEWindow", "\344\272\272\346\234\272\345\257\271\346\210\230\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PVEWindow: public Ui_PVEWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PVEWINDOW_H
