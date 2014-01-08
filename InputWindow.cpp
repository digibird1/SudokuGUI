/*
 * InputWindow.cpp
 *
 *  Created on: Aug 4, 2012
 *      Author: Daniel Pelikan
 */

#include "InputWindow.h"

InputWindow::InputWindow() {
	setWindowTitle("Sudoku Input");
	Layout = new QVBoxLayout;
	InputMatrix = new SudokuMatrixInput(SudokuMap ());
	butSave = new QPushButton("Save");

	Layout->addWidget(InputMatrix);
	Layout->addWidget(butSave);
	setLayout(Layout);


	QObject::connect(butSave,SIGNAL(clicked()),this,SLOT(saveAndCloseWindow()));

}

InputWindow::~InputWindow() {
	// TODO Auto-generated destructor stub
}
void InputWindow::saveAndCloseWindow(){
	InputMatrix->saveValues();
	//m_SM=InputMatrix->getSudokuMap();
	emit InputWasSaved();
	this->close();
}

SudokuMap InputWindow::getSudokuMap() const{
	return InputMatrix->GetSudokuMap();
}

void InputWindow::SetSudokuMap(const SudokuMap &SM){
	InputMatrix->SetSudokuMap(SM);
	InputMatrix->updateInputMatrix();
}


