/*
 * MainWindow.h
 *
 *  Created on: Aug 3, 2012
 *      Author: Daniel Pelikan
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtGui>
#include "SMatrixManipulator.h"
#include "Sudoku/SudokuMap.h"
#include "InputWindow.h"
#include "OptionWindow.h"
#include "LogOutput.h"



class MainWindow : public QWidget{
	Q_OBJECT;
public:
	MainWindow();
	virtual ~MainWindow();
	void SetSudoku();
	void UpdateMatrixWidget();

private:
	QPushButton *TestButton;
	QPushButton *butStepForward;
	QPushButton *butStepBackward;
	QPushButton *butEnterMatrix;
	QPushButton *butSolve;
	QPushButton *butLogOutput;
	QPushButton *butOptions;
	QPushButton *butAbout;
	QHBoxLayout *HBox;
	QHBoxLayout *HBox2;
	QVBoxLayout *AllContent;


	QGridLayout *Grid;


	QGroupBox *GroupTools;
	QGroupBox *GroupSudokuMatrix;
	QGroupBox *GroupSolverTools;




	//widget with the map
	SMatrixManipulator *SudokuMatrix;

	InputWindow *inputWindow;
	OptionWindow *optionWindow;
	LogOutput *logOutput;

	SudokuMap m_SM;
	std::vector<SudokuMap> m_VecExMap;
	SudokuSolver m_SS;

	std::vector<SudokuMap> m_PreviewsMaps;

public slots:
	void getInputMatrix();
	void EnterSudoku() const;
	void getUpdatedWidgetMatrix();
	void showInputMatrix() const;
	void goOneStepBack();
	void tryToSolve();
	void showAboutBox() const;





};

#endif /* MAINWINDOW_H_ */
