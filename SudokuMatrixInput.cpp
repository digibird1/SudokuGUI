/*
 * SudokuMatrixInputWindow.cpp
 *
 *  Created on: Aug 4, 2012
 *      Author: Daniel Pelikan
 */

#include "SudokuMatrixInput.h"


SudokuMatrixInput::SudokuMatrixInput(const SudokuMap &SM):SudokuMatrixWidget(SM) {
	// TODO Auto-generated constructor stub

	setBackgroundRole(QPalette::Base);

	setMinimumSize(748,748);

	setWindowTitle("Input Matrix");

	int MainBlockLength=648;
	int MainOffset=50;

	int SubBlockLength=MainBlockLength/3;
	int SubSubBlockLength=SubBlockLength/3;
	int SubSubSubBlockLength=SubSubBlockLength/3;//8

	QFont font;
	font.setPointSize(50);

	Grid = new QGridLayout;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			InputMatrix[i][j]=new QLineEdit;
			InputMatrix[i][j]->setFixedSize(SubSubBlockLength-10,SubSubBlockLength-10);
			InputMatrix[i][j]->setFont(font);
			InputMatrix[i][j]->setAlignment(Qt::AlignCenter);
			Grid->addWidget(InputMatrix[i][j],i,j);
		}
	}

	Grid->setMargin(50);

	setLayout(Grid);

	setFixedSize(748,748);


}

SudokuMatrixInput::~SudokuMatrixInput() {
	// TODO Auto-generated destructor stub
}

void SudokuMatrixInput::paintEvent(QPaintEvent *event){
	QPainter painter(this);

	int MainBlockLength=648;
	int MainOffset=50;

	int SubBlockLength=MainBlockLength/3;
	int SubSubBlockLength=SubBlockLength/3;
	int SubSubSubBlockLength=SubSubBlockLength/3;//8

	DrawMatrix(painter);

	painter.end();
}

void SudokuMatrixInput::saveValues(){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(InputMatrix[j][i]->text()!=""){
				SetSudokuMapElement(i,j,InputMatrix[j][i]->text().toInt());
			}
			else{
				SetSudokuMapElement(i,j,0);
			}
		}
	}
}

void SudokuMatrixInput::updateInputMatrix(){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(GetSudokuMap().GetElement(i,j)!=0){
				InputMatrix[j][i]->setText(QString::number(GetSudokuMap().GetElement(i,j)));
			}
			else{
				InputMatrix[j][i]->setText("");
			}

		}
	}
}


