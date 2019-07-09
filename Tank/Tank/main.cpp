#include "Tank.h"
#include <QApplication>
#include <QSplashScreen>
#include <QtGui>
#include <QTextCodec>

class Test :public QSplashScreen
{
public:
	Test();
	void drawContents(QPainter* painter);
};
Test::Test()
{
}
void Test::drawContents(QPainter* painter)
{
	painter->setFont(QFont("Helvetica", 32, QFont::Bold));
	QSplashScreen::drawContents(painter);
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QPixmap pixmap("image/menu_background.png");
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
