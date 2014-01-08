/*
 * main.cpp
 *
 *  Created on: Aug 3, 2012
 *      Author: Daniel Pelikan
 */

#include <QtGui>
#include "MainWindow.h"

int main(int argc, char **argv) {
	QApplication app(argc,argv);
	MainWindow *mainWindow = new MainWindow;
	mainWindow->show();


	return app.exec();
}
