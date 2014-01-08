/*
 * LogOutput.h
 *
 *  Created on: Aug 5, 2012
 *      Author: Daniel Pelikan
 */

#ifndef LOGOUTPUT_H_
#define LOGOUTPUT_H_

#include <QtGui>

#include "qdebugstream.h"

class LogOutput : public QWidget {
	Q_OBJECT;
public:
	LogOutput();
	virtual ~LogOutput();


private:

	QTextEdit *LogText;
	QPushButton *butClose;
	QVBoxLayout *VBox;

	QDebugStream *qout;
	QDebugStream *qouterr;

};

#endif /* LOGOUTPUT_H_ */
