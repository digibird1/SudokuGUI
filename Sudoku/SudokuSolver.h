/*
 * SudokuSolver.h
 *
 *  Created on: Jul 29, 2012
 *      Author: Daniel Pelikan
 */

#ifndef SUDOKUSOLVER_H_
#define SUDOKUSOLVER_H_
#include "SudokuMap.h"
#include <iostream>
#include <utility>
#include <vector>

enum SolverCode {UNIQUE,AMBIGUOUS, NOSOLUTION};

class SudokuSolver {
public:
	SudokuSolver(const SudokuMap &SM);
	virtual ~SudokuSolver();
//	SolverCode ScanSudoku(int Num);
	bool checkBlockContains(const int &i,const int &j,const int &Num, int &true_i, int &true_j) const;//Check if a block contains a certain number
	SudokuMap calculateExclusionMap(SudokuMap ExMap, const int &Num) const;
	void PrintExclusionMap(const SudokuMap &ExMap)const;
	void PrintPossibleNumPerElement(const std::vector<SudokuMap> &VecExMap) const;

	SolverCode BlockStatus(const std::pair<int,int> &Block, const SudokuMap &ExMap,int &true_i, int &true_j) const;//returns if the block can be unique/ambiguous solution
	bool FillUniqueSol(const SudokuMap &ExMap, const int &Num);//retruns true if at least one uniq solution was found
	void PrintSolvedStatusMap() const;

	int solveBySimpleExclusion(std::vector<SudokuMap> &VecExMap);

	SolverCode LineStatus(const std::vector<SudokuMap> &VecExMap, const int &i,const int &j,const int &Num) const;//check if there is only one possible position in a block,raw,column for a certain number
	int runLineStatusElimination(const std::vector<SudokuMap> &VecExMap);

	bool checkForInconsistencySinglePairRecursion(std::vector< std::vector<int> > PlaceWithPossibleNum, const int &UniqNum) const;
	bool checkForInconsistency(const std::vector<int> &PlacesForNum,const std::vector< std::vector<int> > &PlaceWithPossibleNum,const int &OpenSpacesCounter) const;
	bool checkForInconsistencyInVerticalLine(const std::vector<SudokuMap> &VecExMap,const int &LineNo)const;
	bool checkForInconsistencyInHorizontalLine(const std::vector<SudokuMap> &VecExMap,const int &LineNo) const;
	bool checkForInconsistencyInBlock(const std::vector<SudokuMap> &VecExMap,const std::pair<int,int> &Block) const;
	bool IsInconsistent(const int &i,const int &j,const int &TestNum, std::vector<SudokuMap> VecExMap,const int &MaxSteps);
	int ExcludeByInconsistency(std::vector<SudokuMap> &VecExMap);


	int GroupExclusionVerticalLine(std::vector<SudokuMap> &VecExMap, const int &Line) const;
	int GroupExclusionHorizontalLine(std::vector<SudokuMap> &VecExMap,const int &Line) const;
	int GroupExclusionBlock(std::vector<SudokuMap> &VecExMap, const std::pair<int,int> &Block) const;
	int checkForInconsistencyByGroupExclusion(std::vector<SudokuMap> &VecExMap) const;

	bool checkMapConsistancy(std::vector<std::pair<int, std::pair<int,int> > > &InconsistancyPos) const;
	bool checkMapCompleatness()const;

	int checkForInconsistencyByStepForward(std::vector<SudokuMap> &VecExMap);
	void setMaxStep(const int &MaxStep);//set the max step width for checkForInconsistencyByStepForward();



	void SolvSudoku();

	SudokuMap getSudokuMap() const;
	void setSudokuMap(const SudokuMap &SM);





private:
	SudokuMap m_SM;
	int m_MaxStep;
	bool m_debug;
};

#endif /* SUDOKUSOLVER_H_ */
