#ifndef TANK_H
#define TANK_H

#include <QMainWindow>
#include "pvewindow.h"
#include "pvpwindow.h"

namespace Ui {
class Tank;
}

class Tank : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tank(QWidget *parent = 0);
    ~Tank();
    void goToPVEWindow();
    void goToPVPWindow();
    void dealSlotPVE();
    void dealSlotPVP();
private slots:

private:
    Ui::Tank *ui;
    PVEWindow pveWindow;
    PVPWindow pvpWindow;
};

#endif // TANK_H
