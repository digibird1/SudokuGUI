/*
 * OptionWindow.h
 *
 *  Created on: Aug 4, 2012
 *      Author: Daniel Pelikan
 */

#ifndef OPTIONWINDOW_H_
#define OPTIONWINDOW_H_
#include <QtGui>

class OptionWindow : public QWidget{
	Q_OBJECT;
public:
	OptionWindow();
	virtual ~OptionWindow();

private:
	QPushButton *butSave;
	QVBoxLayout *VBox;
	QVBoxLayout *VBox2;
	QGroupBox *GroupOptions;
	QLineEdit *MaxIter;

	QCheckBox *CheckOption1;
	QCheckBox *CheckOption2;

};

#endif /* OPTIONWINDOW_H_ */
