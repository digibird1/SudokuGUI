/*
 * MainWindow.cpp
 *
 *  Created on: Aug 3, 2012
 *      Author: Daniel Pelikan
 */

#include "MainWindow.h"

MainWindow::MainWindow():m_SS(m_SM) {


	TestButton=new QPushButton("TestButton");
	butStepForward=new QPushButton("Step >>");
	butStepBackward=new QPushButton("Step <<");
	butEnterMatrix=new QPushButton("Enter Sudoku");
	butLogOutput= new QPushButton("Log Output");
	butOptions= new QPushButton("Options");
	butSolve = new QPushButton("Solve");
	butAbout = new QPushButton("About");

	AllContent=new QVBoxLayout;
	HBox=new QHBoxLayout;
	HBox->addWidget(TestButton);
	HBox->addWidget(butStepBackward);
	HBox->addWidget(butStepForward);
	HBox->addWidget(butEnterMatrix);

	HBox2=new QHBoxLayout;
	HBox2->addWidget(butSolve);
	HBox2->addWidget(butOptions);
	HBox2->addWidget(butLogOutput);
	HBox2->addWidget(butAbout);

	GroupTools= new QGroupBox("Tools");
	GroupTools->setLayout(HBox);

	GroupSolverTools= new QGroupBox("Solver Tools");
	GroupSolverTools->setLayout(HBox2);

	GroupSudokuMatrix = new QGroupBox("Sudoku Matrix");
	Grid = new QGridLayout;

	//own widget
	SudokuMatrix = new SMatrixManipulator(m_SM);
	Grid->addWidget(SudokuMatrix);
	GroupSudokuMatrix->setLayout(Grid);
	AllContent->addWidget(GroupSudokuMatrix);
	AllContent->addWidget(GroupTools);
	AllContent->addWidget(GroupSolverTools);

	setLayout(AllContent);
	setWindowTitle("Sudoku GUI");

	//setSizeIncrement(500,500);

	SetSudoku();//for testing

	inputWindow = new InputWindow();
	butStepBackward->setEnabled(false);
	optionWindow = new OptionWindow();
	logOutput = new LogOutput();


	QObject::connect(inputWindow,SIGNAL(InputWasSaved()),this,SLOT(getInputMatrix()));
	QObject::connect(butEnterMatrix,SIGNAL(clicked()),this,SLOT(showInputMatrix()));
	QObject::connect(SudokuMatrix,SIGNAL(MatrixHasChanged()),this,SLOT(getUpdatedWidgetMatrix()));
	QObject::connect(butStepBackward,SIGNAL(clicked()),this,SLOT(goOneStepBack()));
	QObject::connect(butSolve,SIGNAL(clicked()),this,SLOT(tryToSolve()));
	QObject::connect(butAbout,SIGNAL(clicked()),this,SLOT(showAboutBox()));
	QObject::connect(butOptions,SIGNAL(clicked()),optionWindow,SLOT(show()));
	QObject::connect(butLogOutput,SIGNAL(clicked()),logOutput,SLOT(show()));




	//may change
	butStepForward->setEnabled(false);
	//butLogOutput->setEnabled(false);
}

MainWindow::~MainWindow() {
	// TODO Auto-generated destructor stub
}

void MainWindow::SetSudoku(){
	m_SM.FillMapByLine("   26 7 1",0);
	m_SM.FillMapByLine("68  7  9 ",1);
	m_SM.FillMapByLine("19   45  ",2);
	m_SM.FillMapByLine("82 1   4 ",3);
	m_SM.FillMapByLine("  46 29  ",4);
	m_SM.FillMapByLine(" 5   3 28",5);
	m_SM.FillMapByLine("  93   74",6);
	m_SM.FillMapByLine(" 4  5  36",7);
	m_SM.FillMapByLine("7 3 18   ",8);

//	SudokuSolver SS(m_SM);
/*	SudokuMap ExMap;
	m_VecExMap.clear();
	for(int Num=1;Num<=9;Num++){
		m_VecExMap.push_back(m_SS.calculateExclusionMap(ExMap,Num));
	}

	SudokuMatrix->UpdateWidget(m_SM,m_VecExMap);*/
	UpdateMatrixWidget();
}

void MainWindow::getInputMatrix(){
	m_SM=inputWindow->getSudokuMap();
	UpdateMatrixWidget();

/*	m_SS=SudokuSolver(m_SM);
	SudokuMap ExMap;
	m_VecExMap.clear();
	for(int Num=1;Num<=9;Num++){
		m_VecExMap.push_back(m_SS.calculateExclusionMap(ExMap,Num));
	}

	SudokuMatrix->UpdateWidget(m_SM,m_VecExMap);*/
}

void MainWindow::EnterSudoku() const{
	inputWindow->show();
}

void MainWindow::UpdateMatrixWidget(){

	m_SS=SudokuSolver(m_SM);//fixme this should be a function call of something like set new map
	SudokuMap ExMap;
	m_VecExMap.clear();
	for(int Num=1;Num<=9;Num++){
		m_VecExMap.push_back(m_SS.calculateExclusionMap(ExMap,Num));
	}

	SudokuMatrix->UpdateWidget(m_SM,m_VecExMap);
}

void MainWindow::getUpdatedWidgetMatrix(){
	m_PreviewsMaps.push_back(m_SM);//backward function
	butStepBackward->setEnabled(true);

	m_SM=SudokuMatrix->GetSudokuMap();
	UpdateMatrixWidget();
}

void MainWindow::showInputMatrix() const{
	inputWindow->SetSudokuMap(m_SM);
	inputWindow->show();
}

void MainWindow::goOneStepBack(){
	m_SM=m_PreviewsMaps.at(m_PreviewsMaps.size()-1);
	m_PreviewsMaps.erase(m_PreviewsMaps.end());
	if(m_PreviewsMaps.size()<1)butStepBackward->setEnabled(false);
	UpdateMatrixWidget();
}
void MainWindow::tryToSolve(){
	m_SS.SolvSudoku();
	m_SM=m_SS.getSudokuMap();
	UpdateMatrixWidget();
}

void MainWindow::showAboutBox() const{
	QString Text ="This application is develoved by:\nDaniel Pelikan\n(c) August 2012";
	QMessageBox msg(QMessageBox::Information,"About",Text,QMessageBox::Ok);
	msg.exec();
}
