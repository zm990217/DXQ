#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tank.h"

class Tank : public QMainWindow
{
	Q_OBJECT

public:
	Tank(QWidget *parent = Q_NULLPTR);

private:
	Ui::TankClass ui;
};
