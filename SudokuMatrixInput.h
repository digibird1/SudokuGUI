/*
 * SudokuMatrixInputWindow.h
 *
 *  Created on: Aug 4, 2012
 *      Author: Daniel Pelikan
 */

#ifndef SUDOKUMATRIXINPUT_H_
#define SUDOKUMATRIXINPUT_H_

#include <QtGui>
#include "SudokuMatrixWidget.h"

class SudokuMatrixInput : public SudokuMatrixWidget {
	Q_OBJECT;
public:
	SudokuMatrixInput(const SudokuMap &SM);
	virtual ~SudokuMatrixInput();
	void saveValues();
	void updateInputMatrix();

private:
	QLineEdit *InputMatrix[9][9];
	QGridLayout *Grid;
	QGridLayout *GlobalGrid;

//	SudokuMap m_SM;

protected:
	void paintEvent(QPaintEvent *event);


};

#endif /* SUDOKUMATRIXINPUT_H_ */
