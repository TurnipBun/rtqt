#include <QApplication>
#include <QtGui>
#include "mainwindow.hpp"

/*main函数
 *1.展示启动界面
 *2.展示窗口
 */
int main(int argc, char *argv[])
{
	QApplication app(argc,argv);

	QSplashScreen *pSplash = new QSplashScreen;
	pSplash->setPixmap(QPixmap(":/images/launch.png"));
	pSplash->show();
	pSplash->showMessage(QObject::tr("loading"));
	
	MainWindow mainWin;
	mainWin.show();
	
	pSplash->finish(&mainWin);
	delete pSplash;
	
	return app.exec();
}
