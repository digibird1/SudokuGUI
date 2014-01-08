/*
 * LogOutput.cpp
 *
 *  Created on: Aug 5, 2012
 *      Author: Daniel Pelikan
 */

#include "LogOutput.h"

LogOutput::LogOutput() {
	VBox = new QVBoxLayout;
	butClose = new QPushButton("Close");
	LogText = new QTextEdit();


	QFont font("Monospace");
	font.setStyleHint(QFont::TypeWriter);
	LogText->setFont (font);
	LogText->setReadOnly(true);

	VBox->addWidget(LogText);
	VBox->addWidget(butClose);

	setLayout(VBox);
	setWindowTitle("Log Output");
	resize(600,800);

	QObject::connect(butClose,SIGNAL(clicked()),this,SLOT(close()));

	qout = new QDebugStream(std::cout, LogText);
	qouterr = new QDebugStream(std::cerr, LogText,Qt::red);
}

LogOutput::~LogOutput() {
	// TODO Auto-generated destructor stub
}
