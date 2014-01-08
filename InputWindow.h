/*
 * InputWindow.h
 *
 *  Created on: Aug 4, 2012
 *      Author: Daniel Pelikan
 */

#ifndef INPUTWINDOW_H_
#define INPUTWINDOW_H_

#include <QtGui>
#include "SudokuMatrixInput.h"
#include "Sudoku/SudokuMap.h"



class InputWindow : public QWidget {
	Q_OBJECT;
public:
	InputWindow();
	virtual ~InputWindow();
	SudokuMap getSudokuMap() const;
	void SetSudokuMap(const SudokuMap &SM) ;


private:
	SudokuMatrixInput *InputMatrix;
	QVBoxLayout *Layout;
	QPushButton *butSave;

	//SudokuMap m_SM;

public slots:
	void saveAndCloseWindow();

signals:
	void InputWasSaved();

};

#endif /* INPUTWINDOW_H_ */
