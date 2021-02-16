/********************************************************************************
** Form generated from reading UI file 'pvpwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PVPWINDOW_H
#define UI_PVPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PVPWindow
{
public:
    QLabel *label;
    QPushButton *backMain;

    void setupUi(QWidget *PVPWindow)
    {
        if (PVPWindow->objectName().isEmpty())
            PVPWindow->setObjectName(QStringLiteral("PVPWindow"));
        PVPWindow->resize(1920, 1080);
        label = new QLabel(PVPWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(820, 320, 320, 121));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        font.setPointSize(32);
        label->setFont(font);
        backMain = new QPushButton(PVPWindow);
        backMain->setObjectName(QStringLiteral("backMain"));
        backMain->setGeometry(QRect(790, 770, 401, 181));
        backMain->setFont(font);

        retranslateUi(PVPWindow);

        QMetaObject::connectSlotsByName(PVPWindow);
    } // setupUi

    void retranslateUi(QWidget *PVPWindow)
    {
        PVPWindow->setWindowTitle(QApplication::translate("PVPWindow", "\345\235\246\345\205\213\345\212\250\350\215\241\357\274\232\345\217\214\344\272\272\345\257\271\346\210\230", nullptr));
        label->setText(QApplication::translate("PVPWindow", "\345\217\214\344\272\272\345\257\271\346\210\230\347\225\214\351\235\242", nullptr));
        backMain->setText(QApplication::translate("PVPWindow", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PVPWindow: public Ui_PVPWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PVPWINDOW_H
