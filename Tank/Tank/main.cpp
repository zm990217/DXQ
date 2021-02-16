#include "tank.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPixmap pixmap("c:/QtProject/Tank/image/menu_background.png");
    QSplashScreen splash(pixmap);
    splash.show();
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash.showMessage(QObject::tr("Setting up main Window..."), topRight, Qt::red);
    app.processEvents();
    Tank window;
    splash.showMessage(QObject::tr("Loading modules..."), topRight, Qt::red);
    splash.finish(&window);
    window.show();
    return app.exec();
}
