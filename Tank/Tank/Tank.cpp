#include "Tank.h"

Tank::Tank(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//setWindowTitle(QObject::trUtf8("Ì¹¿Ë¶¯µ´"));
	setObjectName("Tank");
	resize(1920, 1080);
	setStyleSheet("#Tank{border-image:url(c:/Users/10407/source/repos/Tank/Tank/image/menu_background.png);}");
}