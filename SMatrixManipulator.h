/*
 * SMatrixManipulator.h
 *
 *  Created on: Aug 4, 2012
 *      Author: Daniel Pelikan
 */

#ifndef SMATRIXMANIPULATOR_H_
#define SMATRIXMANIPULATOR_H_
#include <QtGui>
#include "SudokuMatrixWidget.h"

class SMatrixManipulator : public SudokuMatrixWidget {
	Q_OBJECT;
public:

	SMatrixManipulator(const SudokuMap &SM);
	virtual ~SMatrixManipulator();

protected:
	void mousePressEvent( QMouseEvent* ev );

signals:
	void mousePressed( const QPoint& );
	void MatrixHasChanged();

public slots:
	void setNumberViaClick(const QPoint& p);

};

#endif /* SMATRIXMANIPULATOR_H_ */
