#include "pvewindow.h"
#include "ui_pvewindow.h"

PVEWindow::PVEWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PVEWindow)
{
    ui->setupUi(this);
    connect(ui->backMain,&QPushButton::pressed,this,&PVEWindow::sendSlot);
}

void PVEWindow::sendSlot()
{
    emit signalBack();
}
PVEWindow::~PVEWindow()
{
    delete ui;
}
