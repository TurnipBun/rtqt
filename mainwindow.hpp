#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT
public:
	MainWindow();
//signals:
//public slots:
//private:
};

#endif