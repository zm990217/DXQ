#include "pvpwindow.h"
#include "ui_pvpwindow.h"

PVPWindow::PVPWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PVPWindow)
{
    ui->setupUi(this);
    connect(ui->backMain,&QPushButton::pressed,this,&PVPWindow::sendSlot);
}
void PVPWindow::sendSlot()
{
    emit signalBack();
}
PVPWindow::~PVPWindow()
{
    delete ui;
}
