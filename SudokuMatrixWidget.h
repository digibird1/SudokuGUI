/*
 * SudokuMatrixWidget.h
 *
 *  Created on: Aug 3, 2012
 *      Author: Daniel Pelikan
 */

#ifndef SUDOKUMATRIXWIDGET_H_
#define SUDOKUMATRIXWIDGET_H_

#include <QtGui>
#include <cstring>
#include <sstream>
#include "Sudoku/SudokuMap.h"
#include "Sudoku/SudokuSolver.h"

class SudokuMatrixWidget :public QWidget {
	Q_OBJECT;
public:
	SudokuMatrixWidget(const SudokuMap &SM);
	virtual ~SudokuMatrixWidget();
	char IntToChar(const int &i);
	void UpdateWidget(const SudokuMap &SM);
	void UpdateWidget(const SudokuMap &SM, const std::vector<SudokuMap> &VecExMap);
	void DrawMatrix(QPainter &painter);

	SudokuMap GetSudokuMap() const;
	SudokuMap GetExMap(const int &i);
	std::vector<SudokuMap> GetVecExMap() const;
	void SetSudokuMapElement(const int &i,const int &j,const int &Num);
	void SetSudokuMap(const SudokuMap &SM);


private:
	QPushButton *but;
	QHBoxLayout *layout;

	SudokuMap m_SM;
	std::vector<SudokuMap> m_VecExMap;//exclusion map



protected:
	void paintEvent(QPaintEvent *event);



};

#endif /* SUDOKUMATRIXWIDGET_H_ */
