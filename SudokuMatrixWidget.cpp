/*
 * SudokuMatrixWidget.cpp
 *
 *  Created on: Aug 3, 2012
 *      Author: Daniel Pelikan
 */

#include "SudokuMatrixWidget.h"



SudokuMatrixWidget::SudokuMatrixWidget(const SudokuMap &SM):m_SM(SM) {

	for(int i=0;i<9;i++)
		m_VecExMap.push_back(SudokuMap ());

	//setAttribute(Qt::WA_OpaquePaintEvent);

	/*but=new QPushButton("Test to remove");
	layout = new QHBoxLayout;
	layout->addWidget(but);

	setLayout(layout);*/



	setBackgroundRole(QPalette::Base);


	setMinimumSize(748,748);//648+2*50


	//fixme Make the Widget flexible or/and a bit smaller in standard







}

SudokuMatrixWidget::~SudokuMatrixWidget() {
	// TODO Auto-generated destructor stub
}

char SudokuMatrixWidget::IntToChar(const int &i){
	std::stringstream ss;
	ss<<i;
	char c;
	ss>>c;
	return c;
}
void SudokuMatrixWidget::DrawMatrix(QPainter &painter){
	const int MainBlockLength=648;
	const int MainOffset=50;

	int SubBlockLength=MainBlockLength/3;
	int SubSubBlockLength=SubBlockLength/3;
	int SubSubSubBlockLength=SubSubBlockLength/3;//8

	painter.setPen(QPen(Qt::green,2));//fixme will be removed
	painter.drawRect(MainOffset,MainOffset,MainBlockLength,MainBlockLength);
	for(int i=0;i<27;i++){
		for(int j=0;j<27;j++){
//			painter.drawRect(MainOffset+i*SubSubSubBlockLength,MainOffset+j*SubSubSubBlockLength,SubSubSubBlockLength,SubSubSubBlockLength);
		}
	}

	painter.setPen(QPen(Qt::gray,2));
	painter.drawRect(MainOffset,MainOffset,MainBlockLength,MainBlockLength);
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			painter.drawRect(MainOffset+i*SubSubBlockLength,MainOffset+j*SubSubBlockLength,SubSubBlockLength,SubSubBlockLength);
		}
	}
	painter.setPen(QPen(Qt::black,2));
	painter.drawRect(MainOffset,MainOffset,MainBlockLength,MainBlockLength);
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			painter.drawRect(MainOffset+i*SubBlockLength,MainOffset+j*SubBlockLength,SubBlockLength,SubBlockLength);
		}
	}
}

void SudokuMatrixWidget::paintEvent(QPaintEvent *event){
	QPainter painter(this);

	const int MainBlockLength=648; //fixme this should be at some point a member variable and the used also in the inheriting classes
	const int MainOffset=50;

	int SubBlockLength=MainBlockLength/3;
	int SubSubBlockLength=SubBlockLength/3;
	int SubSubSubBlockLength=SubSubBlockLength/3;//8

	DrawMatrix(painter);

/*
	painter.setPen(QPen(Qt::green,2));//fixme will be removed
	painter.drawRect(MainOffset,MainOffset,MainBlockLength,MainBlockLength);
	for(int i=0;i<27;i++){
		for(int j=0;j<27;j++){
//			painter.drawRect(MainOffset+i*SubSubSubBlockLength,MainOffset+j*SubSubSubBlockLength,SubSubSubBlockLength,SubSubSubBlockLength);
		}
	}

	painter.setPen(QPen(Qt::gray,2));
	painter.drawRect(MainOffset,MainOffset,MainBlockLength,MainBlockLength);
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			painter.drawRect(MainOffset+i*SubSubBlockLength,MainOffset+j*SubSubBlockLength,SubSubBlockLength,SubSubBlockLength);
		}
	}
	painter.setPen(QPen(Qt::black,2));
	painter.drawRect(MainOffset,MainOffset,MainBlockLength,MainBlockLength);
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			painter.drawRect(MainOffset+i*SubBlockLength,MainOffset+j*SubBlockLength,SubBlockLength,SubBlockLength);
		}
	}*/

	//fill the small blocks
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


	//fill the big blocks
	painter.setPen(QPen(Qt::black,2));
	QFont font;
	font.setPointSize(60);
	painter.setFont(font);
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(m_SM.GetElement(i,j)!=0){
				rect.setRect(MainOffset+i*SubSubBlockLength,MainOffset+j*SubSubBlockLength,72,72);
				painter.drawText(rect,Qt::AlignCenter,QString(IntToChar(m_SM.GetElement(i,j))));
			}
		}
	}


	painter.end();
}

void SudokuMatrixWidget::UpdateWidget(const SudokuMap &SM, const std::vector<SudokuMap> &VecExMap){
	m_VecExMap=VecExMap;
	UpdateWidget(SM);
}

void SudokuMatrixWidget::UpdateWidget(const SudokuMap &SM){
	m_SM=SM;
	update();
}

SudokuMap SudokuMatrixWidget::GetSudokuMap()const{
	return m_SM;
}
SudokuMap SudokuMatrixWidget::GetExMap(const int &i){
	return m_VecExMap[i];
}
std::vector<SudokuMap> SudokuMatrixWidget::GetVecExMap() const{
	return m_VecExMap;
}
void SudokuMatrixWidget::SetSudokuMapElement(const int &i,const int &j,const int &Num){
	m_SM.SetElement(i,j,Num);
}
void SudokuMatrixWidget::SetSudokuMap(const SudokuMap &SM){
	m_SM=SM;
}
