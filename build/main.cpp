#include <QApplication>
#include <QtGui>
#include "os.hpp"
#include "mainwindow.hpp"

#define LAUNCH_WAIT_TIME 2
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
	OS::wait(LAUNCH_WAIT_TIME);
	
	MainWindow mainWin;
	mainWin.show();
	
	pSplash->finish(&mainWin);
	delete pSplash;
	
	return app.exec();
}
