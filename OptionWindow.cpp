/*
 * OptionWindow.cpp
 *
 *  Created on: Aug 4, 2012
 *      Author: Daniel Pelikan
 */

#include "OptionWindow.h"

OptionWindow::OptionWindow() {
	butSave= new QPushButton("Save");
	VBox=new QVBoxLayout;
	VBox2=new QVBoxLayout;
	GroupOptions=new QGroupBox("Options");

	CheckOption1=new QCheckBox("Option1");
	CheckOption2=new QCheckBox("Option2");

	QLabel *LabMaxInerations = new QLabel("Max Iterations:",this);
	MaxIter = new QLineEdit("100");
	LabMaxInerations->setBuddy(MaxIter);


	VBox->addWidget(CheckOption1);
	VBox->addWidget(CheckOption2);
	VBox->addWidget(LabMaxInerations);
	VBox->addWidget(MaxIter);

	setWindowTitle("Options");
//	resize(400,400);

	GroupOptions->setLayout(VBox);
	VBox2->addWidget(GroupOptions);
	VBox2->addWidget(butSave);

	setLayout(VBox2);

	CheckOption2->setCheckState(Qt::Checked);
}

OptionWindow::~OptionWindow() {
	// TODO Auto-generated destructor stub
}
