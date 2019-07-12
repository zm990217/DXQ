#include "tank.h"
#include "ui_tank.h"
#include <QIcon>

Tank::Tank(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tank)
{
    ui->setupUi(this);
    setStyleSheet("#Tank{border-image:url(c:/QtProject/Tank/image/menu_background1.png);}");

    ui->PVP->setStyleSheet(QStringLiteral("background-image:url(c:/QtProject/Tank/image/PVP0.png);"));
    ui->PVE->setStyleSheet(QStringLiteral("background-image:url(c:/QtProject/Tank/image/PVE0.png);"));

    connect(ui->PVE,&QPushButton::pressed,this,&Tank::goToPVEWindow);
    connect(ui->PVP,&QPushButton::pressed,this,&Tank::goToPVPWindow);

    connect(&pveWindow,&PVEWindow::signalBack,this,&Tank::dealSlotPVE);
    connect(&pvpWindow,&PVPWindow::signalBack,this,&Tank::dealSlotPVP);
}
void Tank::goToPVEWindow()
{
    pveWindow.show();
    this->hide();
}
void Tank::dealSlotPVE()
{
    this->show();
    pveWindow.hide();
}
void Tank::goToPVPWindow()
{
    pvpWindow.show();
    this->hide();
}
void Tank::dealSlotPVP()
{
    this->show();
    pvpWindow.hide();
}
Tank::~Tank()
{
    delete ui;
}
