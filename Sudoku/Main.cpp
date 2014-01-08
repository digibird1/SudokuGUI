/*
 * Main.cpp
 *
 *  Created on: Jul 29, 2012
 *      Author: Daniel Pelikan
 */

#include <iostream>
#include <cmath>
#include <cstring>

#include "SudokuMap.h"
#include "SudokuSolver.h"




int main(){


	std::cout<<"Hallo World"<<std::endl;

	SudokuMap SM;

	//TestSudoku
/*	SM.FillMapByLine("53  7    ",0);
	SM.FillMapByLine("6  195   ",1);
	SM.FillMapByLine(" 98    6 ",2);
	SM.FillMapByLine("8   6   3",3);
	SM.FillMapByLine("4  8 3  1",4);
	SM.FillMapByLine("7   2   6",5);
	SM.FillMapByLine(" 6    28 ",6);
	SM.FillMapByLine("   419  5",7);
	SM.FillMapByLine("    8  79",8);
*/

	/*
	 * 534678912
	 * 672195348
	 * 198342567
	 * 859761423
	 * 426853791
	 * 713924856
	 * 961537284
	 * 287419635
	 * 345286179
	 */

	/*
	SM.FillMapByLine("   8   45",0);
	SM.FillMapByLine("46      1",1);
	SM.FillMapByLine("   9    8",2);
	SM.FillMapByLine(" 7  3 5  ",3);
	SM.FillMapByLine("  9 5 7 6",4);
	SM.FillMapByLine("    2 3  ",5);
	SM.FillMapByLine(" 5   2 6 ",6);
	SM.FillMapByLine(" 4   682 ",7);
	SM.FillMapByLine("63   4   ",8);

	*/


/*
	SM.FillMapByLine("53  7    ",0);
	SM.FillMapByLine("6  195   ",1);
	SM.FillMapByLine(" 98    6 ",2);
	SM.FillMapByLine("8   6   3",3);
	SM.FillMapByLine("4  8 3  1",4);
	SM.FillMapByLine("7   2   6",5);
	SM.FillMapByLine(" 6    28 ",6);
	SM.FillMapByLine("   419  5",7);
	SM.FillMapByLine("    8  79",8);
*/
	/////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////

	//Easy
/*	SM.FillMapByLine("   26 7 1",0);
	SM.FillMapByLine("68  7  9 ",1);
	SM.FillMapByLine("19   45  ",2);
	SM.FillMapByLine("82 1   4 ",3);
	SM.FillMapByLine("  46 29  ",4);
	SM.FillMapByLine(" 5   3 28",5);
	SM.FillMapByLine("  93   74",6);
	SM.FillMapByLine(" 4  5  36",7);
	SM.FillMapByLine("7 3 18   ",8);


	SM.FillMapByLine("1  489  6",0);
	SM.FillMapByLine("73     4 ",1);
	SM.FillMapByLine("     1295",2);
	SM.FillMapByLine("  712 6  ",3);
	SM.FillMapByLine("5  7 3  8",4);
	SM.FillMapByLine("  6 957  ",5);
	SM.FillMapByLine("9146     ",6);
	SM.FillMapByLine(" 2     37",7);
	SM.FillMapByLine("8  512  4",8);

	//Intermediate
	SM.FillMapByLine(" 2 6 8   ",0);
	SM.FillMapByLine("58   97  ",1);
	SM.FillMapByLine("    4    ",2);
	SM.FillMapByLine("37    5  ",3);
	SM.FillMapByLine("6       4",4);
	SM.FillMapByLine("  8    13",5);
	SM.FillMapByLine("    2    ",6);
	SM.FillMapByLine("  98   36",7);
	SM.FillMapByLine("   3 6 9 ",8);

	//Difficult
	SM.FillMapByLine("   6  4  ",0);
	SM.FillMapByLine("7    36  ",1);
	SM.FillMapByLine("    91 8 ",2);
	SM.FillMapByLine("         ",3);
	SM.FillMapByLine(" 5 18   3",4);
	SM.FillMapByLine("   3 6 45",5);
	SM.FillMapByLine(" 4 2   6 ",6);
	SM.FillMapByLine("9 3      ",7);
	SM.FillMapByLine(" 2    1  ",8);

	SM.FillMapByLine("2  3     ",0);
	SM.FillMapByLine("8 4 62  3",1);
	SM.FillMapByLine(" 138  2  ",2);
	SM.FillMapByLine("    2 39 ",3);
	SM.FillMapByLine("5 7   621",4);
	SM.FillMapByLine(" 32  6   ",5);
	SM.FillMapByLine(" 2   914 ",6);
	SM.FillMapByLine("6 125 8 9",7);
	SM.FillMapByLine("     1  2",8);*/

	//No Fun
	SM.FillMapByLine(" 2       ",0);
	SM.FillMapByLine("   6    3",1);
	SM.FillMapByLine(" 74 8    ",2);
	SM.FillMapByLine("     3  2",3);
	SM.FillMapByLine(" 8  4  1 ",4);
	SM.FillMapByLine("6  5     ",5);
	SM.FillMapByLine("    1 78 ",6);
	SM.FillMapByLine("5    9   ",7);
	SM.FillMapByLine("       4 ",8);
/**/

	/*Part Test
	SM.FillMapByLine(" 2 6 8   ",0);
	SM.FillMapByLine("58 2397 1",1);
	SM.FillMapByLine("    4  2 ",2);
	SM.FillMapByLine("37    5  ",3);
	SM.FillMapByLine("6   83 74",4);
	SM.FillMapByLine("  8    13",5);
	SM.FillMapByLine("   92  57",6);
	SM.FillMapByLine("  98   36",7);
	SM.FillMapByLine("   3 6 92",8);
*/
	/////////////////////////////////////////////////////////////////////////////////////////////////
/*	SM.FillMapByLine("         ",0);
	SM.FillMapByLine("         ",1);
	SM.FillMapByLine("         ",2);
	SM.FillMapByLine("1 789 234",3);
	SM.FillMapByLine("456 23789",4);
	SM.FillMapByLine("1   7  6 ",5);
	SM.FillMapByLine("         ",6);
	SM.FillMapByLine("         ",7);
	SM.FillMapByLine("         ",8);*/



	//SM.FillMapByLine(" 999 999 ",3);

	//SM.EnterMap();

	SM.PrintMap();


	SudokuSolver SS(SM);




/*
	SM.locateBlock(1,1);
	SM.locateBlock(3,3);
	SM.locateBlock(8,8);

	SM.printBlock(SM.locateBlock(1,1));
	SM.printBlock(SM.locateBlock(3,3));
	SM.printBlock(SM.locateBlock(8,8));
*/
/*
	SudokuMap TestExMap = SS.calculateExclusionMap(5);
	SS.PrintExclusionMap(TestExMap);

	SS.FillUniqueSol(TestExMap,5);
	SS.PrintSolvedStatusMap();


	int a_i=-1;
	int a_j=-1;
	SS.checkBlockContains(0,1,9,a_i,a_j);
	std::cout<<"\n\n"<<a_i<<"\t"<<a_j<<std::endl;
*/
	SS.setMaxStep(100);
	SS.SolvSudoku();
	SS.PrintSolvedStatusMap();

	return 0;
}
