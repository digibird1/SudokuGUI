/*
 * SMatrixManipulator.cpp
 *
 *  Created on: Aug 4, 2012
 *      Author: Daniel Pelikan
 */

#include "SMatrixManipulator.h"

SMatrixManipulator::SMatrixManipulator(const SudokuMap &SM) : SudokuMatrixWidget(SM) {
	QObject::connect(this,SIGNAL(mousePressed(QPoint)),this,SLOT(setNumberViaClick(QPoint)));

}

SMatrixManipulator::~SMatrixManipulator() {
	// TODO Auto-generated destructor stub
}

void SMatrixManipulator::mousePressEvent( QMouseEvent* ev )
{
    const QPoint p = ev->pos();
    emit mousePressed( p );
}

void SMatrixManipulator::setNumberViaClick(const QPoint& p){


	//p.x()



	const int MainBlockLength=648;
	const int MainOffset=50;

	int SubBlockLength=MainBlockLength/3;
	int SubSubBlockLength=SubBlockLength/3;
	int SubSubSubBlockLength=SubSubBlockLength/3;//8

	//check the border
	if(p.x()<MainOffset || p.x()>(MainOffset+MainBlockLength) || p.y()<MainOffset || p.y()>(MainOffset+MainBlockLength)) return;

	//determine Pos in small fields and pos in big field

	int SubSubBlock_i=(p.x()-MainOffset)/SubSubBlockLength;
	int SubSubBlock_j=(p.y()-MainOffset)/SubSubBlockLength;

	int SubSubSubBlock_i = (p.x()-MainOffset - SubSubBlock_i * SubSubBlockLength)/SubSubSubBlockLength;
	int SubSubSubBlock_j = (p.y()-MainOffset - SubSubBlock_j * SubSubBlockLength)/SubSubSubBlockLength;

	int Num=SubSubSubBlock_j*3+SubSubSubBlock_i+1;

	if(GetExMap(Num-1).GetElement(SubSubBlock_i,SubSubBlock_j)!=-1){
		if(GetSudokuMap().GetElement(SubSubBlock_i,SubSubBlock_j)==0){
			SetSudokuMapElement(SubSubBlock_i,SubSubBlock_j,Num);
			emit MatrixHasChanged();
		}
	}

	/*
	UpdateWidget(GetSudokuMap());


	QString Text = "Hallo" + QString::number(SubSubBlock_i) + "\t" + QString::number(SubSubBlock_j)
	+ "\t" + QString::number(SubSubSubBlock_j*3+SubSubSubBlock_i+1);
	QMessageBox msg (QMessageBox::Warning,"Test",Text,QMessageBox::Yes);
	msg.exec();
*/


/*	//fill the small blocks
	QRectF rect;
	painter.setPen(QPen(Qt::red,2));
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(m_SM.GetElement(i,j)==0){
				for(int k=0;k<3;k++){
					for(int l=0;l<3;l++){
						if(m_VecExMap[k*3+l].GetElement(i,j)!=-1){
							rect.setRect(MainOffset+i*SubSubBlockLength+l*SubSubSubBlockLength,MainOffset+j*SubSubBlockLength+k*SubSubSubBlockLength,24,24);
							painter.drawText(rect,Qt::AlignCenter,QString(IntToChar(k*3+l+1)));
						}
					}
				}
			}
		}
	}
*/

}
