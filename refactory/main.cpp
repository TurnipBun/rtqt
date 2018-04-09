#include <QApplication>
#include <QtGui>
//#include "modulewidget.hpp"
#include "comwidget.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	ComWidget comWidget;
	comWidget.show();
	//ModuleWidget mwidget;
	//mwidget.show();
	return app.exec();
}
