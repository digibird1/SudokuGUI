/*
 * SudokuMap.h
 *
 *  Created on: Jul 29, 2012
 *      Author: Daniel Pelikan
 */

#ifndef SUDOKUMAP_H_
#define SUDOKUMAP_H_

#include <iostream>
#include <cstring>
#include <cmath>
#include "Tools.h"
#include "GroupExclusion.h"

enum StatusCode { SUCCESS , FAILURE };

class SudokuMap {
public:
	SudokuMap();
	virtual ~SudokuMap();
	void PrintMap() const;
	void EnterMap();
	int GetElement(const int &i,const int &j) const;
	void SetElement(const int &i,const int &j,const int &Num);
	StatusCode FillMapByLine(const std::string &LineIn, const int &EditLine);
	std::pair<int,int> locateBlock(const int &i, const int &j) const;
	void printBlock(const std::pair<int,int> &Block) const;

private:
	int SudMap[9][9];
};

#endif /* SUDOKUMAP_H_ */
