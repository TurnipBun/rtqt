#include <QApplication>
#include <QtGui>
//#include "modulewidget.hpp"
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	MainWindow mainWin;
	mainWin.show();
	return app.exec();
}
