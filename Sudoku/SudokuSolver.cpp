/*
 * SudokuSolver.cpp
 *
 *  Created on: Jul 29, 2012
 *      Author: Daniel Pelikan
 */

#include "SudokuSolver.h"

SudokuSolver::SudokuSolver(const SudokuMap &SM):m_SM(SM),m_MaxStep(4),m_debug(false) {


}

SudokuSolver::~SudokuSolver() {
	// TODO Auto-generated destructor stub
}

/*
SolverCode SudokuSolver::ScanSudoku(int Num){
	//Use Scan Technique to solv


}*/

bool SudokuSolver::checkBlockContains(const int &i,const int &j,const int &Num,int &true_i, int &true_j)const{
	true_i=-1;
	true_j=-1;
	std::pair<int,int> Block = m_SM.locateBlock(i,j);
	//m_SM.printBlock(Block);

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(m_SM.GetElement(Block.first*3+i,Block.second*3+j)==Num){
				true_i=Block.first*3+i;
				true_j=Block.second*3+j;
				return true;
			}
		}
	}
	return false;
}

void SudokuSolver::PrintSolvedStatusMap() const{
	m_SM.PrintMap();
}

SudokuMap SudokuSolver::calculateExclusionMap(SudokuMap ExMap ,const int &Num) const{
	int true_i=-1;//Coordinates of the value in the Block
	int true_j=-1;

	//SudokuMap ExMap;

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(checkBlockContains(i*3,j*3,Num,true_i,true_j)){//we find a number in the Block

				//mark whole block as occupied
				for(int k=0;k<3;k++){
					for(int l=0;l<3;l++){
						if(m_SM.GetElement(i*3+k,j*3+l)==0)ExMap.SetElement(i*3+k,j*3+l,-1);//exclusion elemnets have -1 set all whcih are free
						//else ExMap.SetElement(i*3+k,j*3+l,m_SM.GetElement(i*3+k,j*3+l));
					}
				}
				//Block End

				//Raw, Column exclusion for the found element
				for(int k=0;k<9;k++){//raw excluson //set all elements in this raw/column to -1
					if(m_SM.GetElement(true_i,k)==0)ExMap.SetElement(true_i,k,-1);
					if(m_SM.GetElement(k,true_j)==0)ExMap.SetElement(k,true_j,-1);
				}
				//end

			}
		}
	}

	//Fill all known elemnets into the map
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(ExMap.GetElement(i,j)!=-1)ExMap.SetElement(i,j,m_SM.GetElement(i,j));//exclusion elemnets have -1 set all whcih are free
		}
	}

	return ExMap;
}

void SudokuSolver::PrintExclusionMap(const SudokuMap &ExMap) const{



	//Prints the map
	std::cout<<"\n\n\n|-----------------------|\n";
	for(int i=0;i<9;i++){
		std::cout<<"| ";
		for(int j=0;j<9;j++){
			if(ExMap.GetElement(i,j)==-1)std::cout<<"X"<<" ";//Empty space in case of a 0
			else if(ExMap.GetElement(i,j)==0)std::cout<<" "<<" ";
			else std::cout<<ExMap.GetElement(i,j)<<" ";
			if((j+1)%3==0 && (j+1)!=9)std::cout<<"| ";
		}
		std::cout<<"|\n";
		if((i+1)%3==0)std::cout<<"|-----------------------|\n";
	}
	std::cout<<"\n\n\n"<<std::endl;
}

void SudokuSolver::PrintPossibleNumPerElement(const std::vector<SudokuMap> &VecExMap)const{
	std::cout<<"======================================================="<<std::endl;

		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				if(m_SM.GetElement(i,j)==0){//we find an empty element
					std::cout<<"Check Elemnet "<<i<<"\t"<<j<<": ";
					for(int Num=1;Num<=9;Num++){
						if(VecExMap[Num-1].GetElement(i,j)!=-1){//This Number is allowed at this place so we test if we find a inconstancy if we add it there.
							std::cout<<""<<Num<<",";
						}
					}
					std::cout<<"\n"<<std::endl;
				}
			}
		}
		std::cout<<"======================================================="<<std::endl;
}


SolverCode SudokuSolver::BlockStatus(const std::pair<int,int> &Block,const SudokuMap &ExMap,int &true_i, int &true_j) const{
	true_i=-1;
	true_j=-1;
	int EmptyElementCounter=0;
	//ExMap.printBlock(Block);

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(ExMap.GetElement(Block.first*3+i,Block.second*3+j)==0){
				true_i=Block.first*3+i;
				true_j=Block.second*3+j;
				EmptyElementCounter++;
			}
		}
	}

	if(EmptyElementCounter==0) return NOSOLUTION;
	else if(EmptyElementCounter==1) return UNIQUE;
	else return AMBIGUOUS;

}

bool SudokuSolver::FillUniqueSol(const SudokuMap &ExMap, const int &Num){
	int true_i=-1;
	int true_j=-1;
	int UniqSolCount=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(BlockStatus(std::make_pair(i,j),ExMap,true_i,true_j)==UNIQUE){
				m_SM.SetElement(true_i,true_j,Num);//Fixme here should be Num -2 is used as a marker
				UniqSolCount++;
			}
		}
	}
	if(UniqSolCount>0) return true;

	return false;
}

SolverCode SudokuSolver::LineStatus(const std::vector<SudokuMap> &VecExMap, const int &i, const int &j, const int &Num) const{
	SolverCode Value = AMBIGUOUS;
	if(VecExMap[Num-1].GetElement(i,j)==-1) return Value; //this number is already at this position excluded

	//Check for a certain block if there is only a certain number which fits

	/*
	 * Run over all empty elements in a block and checke if there is another place where Num could
	 * fit, if now place found we have a unique solution
	 */

	//raw/column
	//Check if in a raw are more than 1 possible place for Num


	int OpenPlacesCounter=0;

	for(int k=0;k<9;k++){
		if(VecExMap[Num-1].GetElement(i,k)==0 && k!=j)OpenPlacesCounter++;
	}
	if(OpenPlacesCounter==0) Value=UNIQUE;

	OpenPlacesCounter=0;
	for(int k=0;k<9;k++){
		if(VecExMap[Num-1].GetElement(k,j)==0 && k!=i)OpenPlacesCounter++;
	}
	if(OpenPlacesCounter==0) Value=UNIQUE;


	return Value;

}

int SudokuSolver::runLineStatusElimination(const std::vector<SudokuMap> &VecExMap){

	int Steps=0;

	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(m_SM.GetElement(i,j)==0){
				for(int Num=1;Num<=9;Num++){
					if(LineStatus(VecExMap,i,j,Num)==UNIQUE){
						m_SM.SetElement(i,j,Num);
						Steps++;
					}
				}
			}

		}
	}
	return Steps;
}

bool SudokuSolver::checkForInconsistencySinglePairRecursion(std::vector< std::vector<int> > PlaceWithPossibleNum, const int &UniqNum) const{
	//fixme check if PlaceWithPossibleNum could be a ref

	//This function follows a path and checks for inconsistency in case we have in our number set one entry with exactly one possibility
	/*check: 0 4: 2,5,
	 *check: 1 4: 2,4,5,
	 *check: 3 4: 2,4,5,
	 *check: 5 4: 2,
	 *
	 * This gives a conflict, due to -> 5 4 -> 2 --> 0 4 -> 5 --> 1 4 & 3 4 -> 4 ----> conflict
	 */

	//First STep should be to remove the uniq solution from all elements
	//recalculate the compare numbers and check if we find more exact sol


	for(int i=0;i<9;i++){
		for(int j=0;j<PlaceWithPossibleNum[i].size();j++){
			if(PlaceWithPossibleNum[i].at(j)==UniqNum){
				PlaceWithPossibleNum[i].erase(PlaceWithPossibleNum[i].begin()+j);
			}
		}
	}

	//now we check again for uniqu numbers
	bool isInconsistent=false;
	for(int i=0;i<9;i++){
		if(PlaceWithPossibleNum[i].size()==1){
			if(checkForInconsistencySinglePairRecursion(PlaceWithPossibleNum,PlaceWithPossibleNum[i].at(0))) isInconsistent=true;
		}
	}
	if(isInconsistent) return true;



	std::vector<int> CompareNumber;
	for(int i=0;i<9;i++){//we make for easy compare one number out of the amount of digits so that we can compare ne number if they are identical
						// 1,2,3 -> 123 and so on
		int Size=PlaceWithPossibleNum[i].size();
		int tmp=0;
		for(int j=0;j<Size;j++){
			//calculate number
			tmp+=PlaceWithPossibleNum[i].at(j)*std::pow(10,Size-j-1);
		}
		CompareNumber.push_back(tmp);
	}
	//these numbers we can now comapre
	for(int i=0;i<9;i++){
		int Counter=0;
		for(int j=i;j<9;j++){
			if(CompareNumber[i]==CompareNumber[j] && CompareNumber[i]!=0){
				Counter++;
			}
		}
		if(Counter>PlaceWithPossibleNum[i].size()){//we find more places with the same numbers as we have numbers
			std::cout<<"Counter>PlaceWithPossibleNum[i].size()"<<CompareNumber[i]<<" : "<<Counter<<">"<<PlaceWithPossibleNum[i].size()<<std::endl;
			return true;
		}
	}

	return false;
}


bool SudokuSolver::checkForInconsistency(const std::vector<int> &PlacesForNum,const std::vector< std::vector<int> > &PlaceWithPossibleNum, const int &OpenSpacesCounter) const{
	int SumOfAllPossibleNum=0;
	int AllPossibleNum=0;
	for(int i=0;i<9;i++){
		SumOfAllPossibleNum+=PlacesForNum[i];
		if(PlacesForNum[i]!=0)AllPossibleNum++;
	}



	if(AllPossibleNum<OpenSpacesCounter) return true;//less numbers possible as open spaces

	for(int i=0;i<9;i++){//isn't this part covered by the later general part?
		if(PlaceWithPossibleNum[i].size()==1){;
			//check if another place exists where exactly the same number is the only solution
			for(int j=i+1;j<9;j++){
				if(PlaceWithPossibleNum[j].size()==1){
					if(PlaceWithPossibleNum[i].at(0)==PlaceWithPossibleNum[j].at(0)){
						return true;
					}
				}
			}
		}
	}

	//Check if there are 2 places with <2 combination
	/* 3 places with <3
	 * 4<4 ....
	 */
	std::vector<int> CompareNumber;
	for(int i=0;i<9;i++){//we make for easy compare one number out of the amount of digits so that we can compare ne number if they are identical
						// 1,2,3 -> 123 and so on
		int Size=PlaceWithPossibleNum[i].size();
		int tmp=0;
		for(int j=0;j<Size;j++){
			//calculate number
			tmp+=PlaceWithPossibleNum[i].at(j)*std::pow(10,Size-j-1);
		}
		CompareNumber.push_back(tmp);
	}
	//these numbers we can now comapre
	for(int i=0;i<9;i++){
		int Counter=0;
		for(int j=i;j<9;j++){
			if(CompareNumber[i]==CompareNumber[j] && CompareNumber[i]!=0){
				Counter++;
			}
		}
		if(Counter>PlaceWithPossibleNum[i].size()){//we find more places with the same numbers as we have numbers
			std::cout<<"Counter>PlaceWithPossibleNum[i].size()"<<CompareNumber[i]<<" : "<<Counter<<">"<<PlaceWithPossibleNum[i].size()<<std::endl;
			return true;
		}
	}

	//
	//we need a check for in case we find a uniq solution that we continue the change and chack for inconsitancy
	//for ex
	/*check: 0 4: 2,5,
	 *check: 1 4: 2,4,5,
	 *check: 3 4: 2,4,5,
	 *check: 5 4: 2,
	 *
	 * This gives a conflict, due to -> 5 4 -> 2 --> 0 4 -> 5 --> 1 4 & 3 4 -> 4 ----> conflict
	 */

	bool isInconsistent=false;
	for(int i=0;i<9;i++){
		if(PlaceWithPossibleNum[i].size()==1){
			if(checkForInconsistencySinglePairRecursion(PlaceWithPossibleNum,PlaceWithPossibleNum[i].at(0))) isInconsistent=true;
		}
	}
	if(isInconsistent) return true;


	/*check: 0 4: 2,5,
	 *check: 1 4: 2,4,5,
	 *check: 3 4: 2,4,5,
	 *check: 5 4: 2,5
	 * What about this case?
	 */

	return false;
}


bool SudokuSolver::checkForInconsistencyInVerticalLine(const std::vector<SudokuMap> &VecExMap,const int &LineNo) const{//fixme this is in fact horizontal
	int OpenSpacesCounter=0;
	std::vector<int> PlacesForNum;//saves the amount of possible places for a certain number
	std::vector< std::vector<int> > PlaceWithPossibleNum;//This saves the pos and the possible elements
	for(int i=0;i<9;i++){
		PlacesForNum.push_back(0);

		PlaceWithPossibleNum.push_back(std::vector<int>());
	}

	for(int i=0;i<9;i++){
		if(m_SM.GetElement(LineNo,i)==0){
			OpenSpacesCounter++;
			//std::cout<<"check: "<<LineNo<<" "<<i<<": ";
			for(int Num=1;Num<=9;Num++){

				if(VecExMap[Num-1].GetElement(LineNo,i)!=-1){
					//std::cout<<Num<<",";
					PlacesForNum[Num-1]++;
					PlaceWithPossibleNum[i].push_back(Num);
				}
			}
		}
		//std::cout<<std::endl;
	}


	//Check if there are >1 solutions where only one number is allowed... (2 times the same number is not possible
	//or if there is open spaces but no number any longer possible

	return checkForInconsistency(PlacesForNum,PlaceWithPossibleNum,OpenSpacesCounter);
/*
	bool isInconsistent=false;

	int SumOfAllPossibleNum=0;
	int AllPossibleNum=0;
	for(int i=0;i<9;i++){
		SumOfAllPossibleNum+=PlacesForNum[i];
		if(PlacesForNum[i]!=0)AllPossibleNum++;
	}



	if(AllPossibleNum<OpenSpacesCounter) return true;//less numbers possible as open spaces

	for(int i=0;i<9;i++){
		if(PlaceWithPossibleNum[i].size()==1){;
			//check if another place exists where exactly the same number is the only solution
			for(int j=i+1;j<9;j++){
				if(PlaceWithPossibleNum[j].size()==1){
					if(PlaceWithPossibleNum[i].at(0)==PlaceWithPossibleNum[j].at(0)){
						return true;
					}
				}
			}
		}
	}

	//Check if there are 2 places with <2 combination

	std::vector<int> CompareNumber;
	for(int i=0;i<9;i++){//we make for easy compare one number out of the amount of digits so that we can compare ne number if they are identical
						// 1,2,3 -> 123 and so on
		int Size=PlaceWithPossibleNum[i].size();
		int tmp=0;
		for(int j=0;j<Size;j++){
			//calculate number
			tmp+=PlaceWithPossibleNum[i].at(j)*std::pow(10,Size-j-1);
		}
		CompareNumber.push_back(tmp);
	}
	//these numbers we can now comapre
	for(int i=0;i<9;i++){
		int Counter=0;
		for(int j=i;j<9;j++){
			if(CompareNumber[i]==CompareNumber[j] && CompareNumber[i]!=0){
				Counter++;
			}
		}
		if(Counter>PlaceWithPossibleNum[i].size()){//we find more places with the same numbers as we have numbers
			std::cout<<"Counter>PlaceWithPossibleNum[i].size()"<<CompareNumber[i]<<" : "<<Counter<<">"<<PlaceWithPossibleNum[i].size()<<std::endl;
			return true;
		}
	}


	return false;

*/
}

bool SudokuSolver::checkForInconsistencyInHorizontalLine(const std::vector<SudokuMap> &VecExMap,const int &LineNo) const{//fixme this is in fact vertical
	int OpenSpacesCounter=0;
	std::vector<int> PlacesForNum;//saves the amount of possible places for a certain number
	std::vector< std::vector<int> > PlaceWithPossibleNum;//This saves the pos and the possible elements
	for(int i=0;i<9;i++){
		PlacesForNum.push_back(0);

		PlaceWithPossibleNum.push_back(std::vector<int>());
	}

	for(int i=0;i<9;i++){
		if(m_SM.GetElement(i,LineNo)==0){
			OpenSpacesCounter++;
			if(m_debug)std::cout<<"check: "<<i<<" "<<LineNo<<": ";
			for(int Num=1;Num<=9;Num++){
				if(VecExMap[Num-1].GetElement(i,LineNo)!=-1){
					if(m_debug)std::cout<<Num<<",";
					PlacesForNum[Num-1]++;
					PlaceWithPossibleNum[i].push_back(Num);
				}
			}
		}
		if(m_debug)std::cout<<std::endl;
	}

	//Check if there are >1 solutions where only one number is allowed... (2 times the same number is not possible
	//or if there is open spaces but no number any longer possible

	return checkForInconsistency(PlacesForNum,PlaceWithPossibleNum,OpenSpacesCounter);
/*
	bool isInconsistent=false;

	int SumOfAllPossibleNum=0;
	int AllPossibleNum=0;
	for(int i=0;i<9;i++){
		SumOfAllPossibleNum+=PlacesForNum[i];
		if(PlacesForNum[i]!=0)AllPossibleNum++;
	}

	std::cout<<"Test:"<<std::endl;
	std::cout<<"SumOfAllPossibleNum"<<SumOfAllPossibleNum<<std::endl;
	std::cout<<"AllPossibleNum"<<AllPossibleNum<<std::endl;

	if(AllPossibleNum<OpenSpacesCounter) return true;//less numbers possible as open spaces

	for(int i=0;i<9;i++){
		if(PlaceWithPossibleNum[i].size()==1){;
			//check if another place exists where exactly the same number is the only solution
			for(int j=i+1;j<9;j++){
				if(PlaceWithPossibleNum[j].size()==1){
					if(PlaceWithPossibleNum[i].at(0)==PlaceWithPossibleNum[j].at(0)){
						return true;
					}
				}
			}
		}
	}

	//Check if there are 2 places with <2 combination

	std::vector<int> CompareNumber;
	for(int i=0;i<9;i++){//we make for easy compare one number out of the amount of digits so that we can compare ne number if they are identical
						// 1,2,3 -> 123 and so on
		int Size=PlaceWithPossibleNum[i].size();
		int tmp=0;
		for(int j=0;j<Size;j++){
			//calculate number
			tmp+=PlaceWithPossibleNum[i].at(j)*std::pow(10,Size-j-1);
		}
		CompareNumber.push_back(tmp);
	}
	//these numbers we can now comapre
	for(int i=0;i<9;i++){
		int Counter=0;
		for(int j=i;j<9;j++){
			if(CompareNumber[i]==CompareNumber[j] && CompareNumber[i]!=0){
				Counter++;
			}
		}
		if(Counter>PlaceWithPossibleNum[i].size()){//we find more places with the same numbers as we have numbers
			std::cout<<"Counter>PlaceWithPossibleNum[i].size()"<<CompareNumber[i]<<" : "<<Counter<<">"<<PlaceWithPossibleNum[i].size()<<std::endl;
			return true;
		}
	}
/*
	for(int i=0;i<9;i++){//how many numbers per place
		for(int Num=0;Num<9;Num++){
			for(int k=0;k<9;k++){//loop over all places
				if(PlaceWithPossibleNum[k].size()==(i+1)){

				}
			}
		}
	}


	return false;
*/
}

bool SudokuSolver::checkForInconsistencyInBlock(const std::vector<SudokuMap> &VecExMap,const std::pair<int,int> &Block) const{
	int OpenSpacesCounter=0;
	std::vector<int> PlacesForNum;//saves the amount of possible places for a certain number
	std::vector< std::vector<int> > PlaceWithPossibleNum;//This saves the pos and the possible elements
	for(int i=0;i<9;i++){
		PlacesForNum.push_back(0);

		PlaceWithPossibleNum.push_back(std::vector<int>());
	}

	int PosCounter=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			PosCounter++;
			if(m_SM.GetElement(Block.first*3+i,Block.second*3+j)==0){
				OpenSpacesCounter++;
				for(int Num=1;Num<=9;Num++){
					if(VecExMap[Num-1].GetElement(Block.first*3+i,Block.second*3+j)!=-1){
						PlacesForNum[Num-1]++;
						PlaceWithPossibleNum[PosCounter-1].push_back(Num);
					}
				}
			}
		}
	}

	//Check if there are >1 solutions where only one number is allowed... (2 times the same number is not possible
	//or if there is open spaces but no number any longer possible

	return checkForInconsistency(PlacesForNum,PlaceWithPossibleNum,OpenSpacesCounter);
/*
	bool isInconsistent=false;

	int SumOfAllPossibleNum=0;
	int AllPossibleNum=0;
	for(int i=0;i<9;i++){
		SumOfAllPossibleNum+=PlacesForNum[i];
		if(PlacesForNum[i]!=0)AllPossibleNum++;
	}

	if(AllPossibleNum<OpenSpacesCounter) return true;//less numbers possible as open spaces

	for(int i=0;i<9;i++){
		if(PlaceWithPossibleNum[i].size()==1){;
			//check if another place exists where exactly the same number is the only solution
			for(int j=i+1;j<9;j++){
				if(PlaceWithPossibleNum[j].size()==1){
					if(PlaceWithPossibleNum[i].at(0)==PlaceWithPossibleNum[j].at(0)){
						return true;
					}
				}
			}
		}
	}


	//Check if there are 2 places with <2 combination

	std::vector<int> CompareNumber;
	for(int i=0;i<9;i++){//we make for easy compare one number out of the amount of digits so that we can compare ne number if they are identical
						// 1,2,3 -> 123 and so on
		int Size=PlaceWithPossibleNum[i].size();
		int tmp=0;
		for(int j=0;j<Size;j++){
			//calculate number
			tmp+=PlaceWithPossibleNum[i].at(j)*std::pow(10,Size-j-1);
		}
		CompareNumber.push_back(tmp);
	}
	//these numbers we can now comapre
	for(int i=0;i<9;i++){
		int Counter=0;
		for(int j=i;j<9;j++){
			if(CompareNumber[i]==CompareNumber[j] && CompareNumber[i]!=0){
				Counter++;
			}
		}
		if(Counter>PlaceWithPossibleNum[i].size()){//we find more places with the same numbers as we have numbers
			std::cout<<"Counter>PlaceWithPossibleNum[i].size()"<<CompareNumber[i]<<" : "<<Counter<<">"<<PlaceWithPossibleNum[i].size()<<std::endl;
			return true;
		}
	}

	return false;*/
}

bool SudokuSolver::IsInconsistent(const int &i,const int &j,const int &TestNum, std::vector<SudokuMap> VecExMap,const int &MaxSteps){
	//Check for
	//87. (8,1) = 4, row insufficiency for [(2,[5,1]),(5,[5,7,1]),(6,[5,7,1]),(7,[1])] wrt [1], (8,1) now [7,2,1]



	//std::cout<<"IsInconsistent"<<std::endl;
	SudokuMap TmpMap=m_SM;//Make a copy
	m_SM.SetElement(i,j,TestNum);//place temporary a number
	VecExMap[TestNum-1] = calculateExclusionMap(VecExMap[TestNum-1],TestNum);//recalculate the exclusion map for this number
	bool isInconsitent=false;

/*	if(i==7 && j==0 && TestNum ==4){

		VecExMap[2-1].SetElement(7,6,-1);//remove test

		std::cout<<"\nWere are here\n"<<std::endl;
		m_SM.PrintMap();
		VecExMap[TestNum-1].PrintMap();

	}*/
/*
	Taken Element: 3 6: 2

	Check Elemnet 8	5: 4,5,7,8,9,
	Check Elemnet 8	3: 4,5,7,8,9,
	Check Elemnet 7	5: 4,5,7,8,
	Check Elemnet 7	3: 4,5,7,8,
	Check Elemnet 6	5: 5,7,8,9,

	cover 4,5,7,8,9

	so we can remove 4,5 from the ones below
	Check Elemnet 6	4: 1,3,5,
	Check Elemnet 7	4: 1,4,5,6,
	Check Elemnet 8	4: 3,4,5,6,
*/

	if(i==7 && j==4 && TestNum ==7){
		std::cout<<"\nWere are here\n"<<std::endl;
		m_SM.PrintMap();
		VecExMap[TestNum-1].PrintMap();
	}


	if(checkForInconsistencyInVerticalLine(VecExMap,i)){
		std::cout<<"Inconsistent Line V "<<TestNum<<std::endl;
		isInconsitent=true;
	}


	if(checkForInconsistencyInHorizontalLine(VecExMap,j)){
		std::cout<<"Inconsistent Line H "<<TestNum<<std::endl;
		isInconsitent=true;
	}


	if(checkForInconsistencyInBlock(VecExMap,std::make_pair(i/3,j/3))){
		std::cout<<"Inconsistent Block "<<TestNum<<std::endl;
		isInconsitent=true;
	}

	m_SM=TmpMap;//move the original Map back
	return isInconsitent;

/*
	//////////////////////////////////////////////////////////////////
	//Raw /column
	for(int Step=0;Step<MaxSteps;Step++){
		for(int k=0;k<9;k++){
			if(m_SM.GetElement(i,k)==0){
				for(int Num=1;Num<=9;Num++){
					if(LineStatus(VecExMap,i,k,Num)==UNIQUE){
						std::cout<<"LineStatus"<<std::endl;
						m_SM.SetElement(i,k,Num);
						VecExMap[Num-1] = calculateExclusionMap(Num);
						if(checkForInconsistencyInVerticalLine(VecExMap,i)){
							std::cout<<"checkForInconsistencyInVerticalLine=true"<<std::endl;
							isInconsitent=true;
						}
					}
				}
			}
		}
	}

	for(int Step=0;Step<MaxSteps;Step++){
		for(int k=0;k<9;k++){
			if(m_SM.GetElement(k,j)==0){
				for(int Num=1;Num<=9;Num++){
					if(LineStatus(VecExMap,k,j,Num)==UNIQUE){
						m_SM.SetElement(k,j,Num);
						VecExMap[Num-1] = calculateExclusionMap(Num);
						if(checkForInconsistencyInHorizontalLine(VecExMap,j)){
							std::cout<<"checkForInconsistencyInVerticalLine=true"<<std::endl;
							isInconsitent=true;
						}
					}
				}
			}
		}
	}


/*	//Block
	std::pair<int,int> Block=std::make_pair(i/3,j/3);
	for(int Step=0;Step<MaxSteps;Step++){
		for(int Num=1;Num<=9;Num++){
			int true_i=-1;
			int true_j=-1;
			if(BlockStatus(Block,VecExMap[Num-1],true_i,true_j)==UNIQUE){
				m_SM.SetElement(true_i,true_j,Num);
				VecExMap[Num-1] = calculateExclusionMap(Num);
				if(checkForInconsistencyInHorizontalBlock(VecExMap,j)){
					std::cout<<"checkForInconsistencyInBlock=true"<<std::endl;
					isInconsitent=true;
				}
			}
		}
	}




	m_SM=TmpMap;//move the original Map back
	return isInconsitent;*/
}

int SudokuSolver::ExcludeByInconsistency(std::vector<SudokuMap> &VecExMap){
	if(m_debug)std::cout<<"ExcludeByInconsistency"<<std::endl;

	bool changed=false;
	int Step=0;


//Set a number which could fit and check if we find a inconsistency
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(m_SM.GetElement(i,j)==0){//we find an empty element
				if(m_debug)std::cout<<"Check Elemnet "<<i<<"\t"<<j<<": ";
				for(int Num=1;Num<=9;Num++){
					if(VecExMap[Num-1].GetElement(i,j)!=-1){//This Number is allowed at this place so we test if we find a inconstancy if we add it there.
						if(m_debug)std::cout<<""<<Num<<",";
						if(IsInconsistent(i,j,Num,VecExMap,4)){
							VecExMap[Num-1].SetElement(i,j,-1);
							//VecExMap[Num-1].PrintMap();
							if(m_debug)std::cout<<"\nChange by Inconsistent"<<std::endl;
							changed=true;
							Step++;
						}
					}
				}
				if(m_debug)std::cout<<"\n"<<std::endl;
			}
		}
	}

	/* fixme isn't this done by another function? (120803-1411)
	//Check if after applying the inconsistency we find unique solutions
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(m_SM.GetElement(i,j)==0){//we find an empty element
				int PossibleSolCount=0;
				int Solution=0;
				for(int Num=1;Num<=9;Num++){
					if(VecExMap[Num-1].GetElement(i,j)!=-1){//This Number is allowed at this place so we test if we find a inconstancy if we add it there.
						PossibleSolCount++;
						Solution=Num;
					}
				}
				if(PossibleSolCount==1){//After consitency check there is only one possible solution for this filed left
					m_SM.SetElement(i,j,Solution);
				}
			}
		}
	}
	*/

	return Step;
}

int SudokuSolver::GroupExclusionVerticalLine(std::vector<SudokuMap> &VecExMap, const int &Line) const{
	std::vector< std::vector<int> > GroupVector;
	int ExtCounter=0;
	std::vector<int > ExtCounterPos;
	for(int j=0;j<9;j++){
		if(m_SM.GetElement(Line,j)==0){//we find an empty element
			GroupVector.push_back(std::vector<int>());
			for(int Num=1;Num<=9;Num++){
				if(VecExMap[Num-1].GetElement(Line,j)!=-1){
					GroupVector[ExtCounter].push_back(Num);
				}
			}
			ExtCounterPos.push_back(j);
			ExtCounter++;
		}
	}

	GroupExclusion GE;

	std::vector<std::pair<int,std::vector<int> > > Excluded= GE.CheckForExclusions(GroupVector);
	if(Excluded.size()==0) return 0;

	for(int i=0;i<Excluded.size();i++){
		for(int j=0;j<Excluded[i].second.size();j++){
			VecExMap[Excluded[i].second.at(j)-1].SetElement(Line,ExtCounterPos[Excluded[i].first],-1);
		}
	}

	return Excluded.size();
}
int SudokuSolver::GroupExclusionHorizontalLine(std::vector<SudokuMap> &VecExMap,const int &Line) const{
	std::vector< std::vector<int> > GroupVector;
	int ExtCounter=0;
	std::vector<int > ExtCounterPos;
	for(int i=0;i<9;i++){
		if(m_SM.GetElement(i,Line)==0){//we find an empty element
			GroupVector.push_back(std::vector<int>());
			for(int Num=1;Num<=9;Num++){
				if(VecExMap[Num-1].GetElement(i,Line)!=-1){
					GroupVector[ExtCounter].push_back(Num);
				}
			}
			ExtCounterPos.push_back(i);
			ExtCounter++;
		}
	}


	GroupExclusion GE;

	std::vector<std::pair<int,std::vector<int> > > Excluded= GE.CheckForExclusions(GroupVector);
	if(Excluded.size()==0) return 0;

	for(int i=0;i<Excluded.size();i++){
		for(int j=0;j<Excluded[i].second.size();j++){
			VecExMap[Excluded[i].second.at(j)-1].SetElement(ExtCounterPos[Excluded[i].first],Line,-1);
		}
	}

	return Excluded.size();

}
int SudokuSolver::GroupExclusionBlock(std::vector<SudokuMap> &VecExMap,const std::pair<int,int> &Block) const{
	std::vector< std::vector<int> > GroupVector;

	int ExtCounter=0;
	std::vector<std::pair<int,int> > ExtCounterPos;
	for(int i=0;i<3;i++){
		for(int j=3;j<3;j++){
			if(m_SM.GetElement(Block.first*3+i,Block.first*3+j)==0){
				GroupVector.push_back(std::vector<int>());
				for(int Num=1;Num<=9;Num++){
					if(VecExMap[Num-1].GetElement(Block.first*3+i,Block.first*3+j)!=-1){
						GroupVector[ExtCounter].push_back(Num);
					}
				}
				ExtCounterPos.push_back(std::make_pair(Block.first*3+i,Block.first*3+j));
				ExtCounter++;
			}
		}
	}


	GroupExclusion GE;

	std::vector<std::pair<int,std::vector<int> > > Excluded= GE.CheckForExclusions(GroupVector);
	if(Excluded.size()==0) return 0;

	for(int i=0;i<Excluded.size();i++){
		for(int j=0;j<Excluded[i].second.size();j++){
			VecExMap[Excluded[i].second.at(j)-1].SetElement(ExtCounterPos[Excluded[i].first].first,
					ExtCounterPos[Excluded[i].first].second,-1);
		}
	}

	return Excluded.size();
}


int SudokuSolver::checkForInconsistencyByGroupExclusion(std::vector<SudokuMap> &VecExMap) const{
	//one loop over all Horizontal lines
	//one loop over all vertical lines
	//one loop over all boxes

	int Step=0;

	bool changed=false;
//fixme maybe all in one loop is thsi possible?
	for(int i=0;i<9;i++){//horizontal lines
		Step+=GroupExclusionHorizontalLine(VecExMap,i);
		//if(GroupExclusionHorizontalLine(VecExMap,i)!=0)changed=true;
	}

	for(int i=0;i<9;i++){//Vertical lines
		Step+=GroupExclusionVerticalLine(VecExMap,i);
		//if(GroupExclusionVerticalLine(VecExMap,i)!=0)changed=true;
	}

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			Step+=GroupExclusionBlock(VecExMap,std::make_pair(i,j));
			//if(GroupExclusionBlock(VecExMap,std::make_pair(i,j))!=0)changed=true;
		}
	}

	return Step;

}

bool SudokuSolver::checkMapConsistancy(std::vector<std::pair<int, std::pair<int,int> > > &InconsistancyPos) const{
	bool MapIsCompleat=true;
	//returns true if the map is consistent with the Sudoku rules
	//false if a inconsistency is found
	//returns also the place of inconsistency if wanted with inconsisten number
	//the form is < Num, <i,j> >

	//creat our counter map

	bool isConsistent=true;

	std::vector<int> Counter;
	for(int i=0;i<9;i++){
		Counter.push_back(0);
	}

	//raw Test
	for(int i=0;i<9;i++){
		for( int j=0;j<9;j++){
			if(m_SM.GetElement(i,j)!=0)Counter[m_SM.GetElement(i,j)-1]++;
			if(m_SM.GetElement(i,j)==0) MapIsCompleat=false;
		}
		for(int Num=1;Num<=9;Num++){//check if we have >1 times a number in a raw and reset element
			if(Counter[Num-1]>1){
				isConsistent=false;
				for(int j=0;j<9;j++){//find the positin with the >1 number and save it's pos
					if(m_SM.GetElement(i,j)==Num)InconsistancyPos.push_back(std::make_pair(Num,std::make_pair(i,j)));
				}
			}
			Counter[Num-1]=0;//reset counter
		}
	}

	//column Test
	for(int j=0;j<9;j++){
		for( int i=0;i<9;i++){
			if(m_SM.GetElement(i,j)!=0)Counter[m_SM.GetElement(i,j)-1]++;
		}
		for(int Num=1;Num<=9;Num++){//check if we have >1 times a number in a raw and reset element
			if(Counter[Num-1]>1){
				isConsistent=false;
				for(int i=0;i<9;i++){//find the positin with the >1 number and save it's pos
					if(m_SM.GetElement(i,j)==Num)InconsistancyPos.push_back(std::make_pair(Num,std::make_pair(i,j)));
				}
			}
			Counter[Num-1]=0;//reset counter
		}
	}

	//Box Test
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){//run ovr all boxes
			//now run inside the boxes
			for(int k=0;k<3;k++){
				for(int l=0;l<3;l++){
					if(m_SM.GetElement(i*3+k,j*3+l)!=0)Counter[m_SM.GetElement(i*3+k,j*3+l)-1]++;
				}
			}
			for(int Num=1;Num<=9;Num++){//check if we have >1 times a number in a raw and reset element
				if(Counter[Num-1]>1){
					isConsistent=false;
					for(int k=0;k<3;k++){
						for(int l=0;l<3;l++){
							if(m_SM.GetElement(i*3+k,j*3+l)==Num)InconsistancyPos.push_back(std::make_pair(Num,std::make_pair(i*3+k,j*3+l)));
						}
					}

				}
				Counter[Num-1]=0;//reset counter
			}
			//now run outside the boxes
		}
	}

	if(!isConsistent){
		for(int i=0;i<InconsistancyPos.size();i++){
			std::cout<<"Inconsistent: Num "<<InconsistancyPos[i].first<<": ("<<InconsistancyPos[i].second.first
					<<","<<InconsistancyPos[i].second.second<<")"<<std::endl;
		}
	}
return isConsistent;
}

void SudokuSolver::setMaxStep(const int &MaxStep){
	m_MaxStep=MaxStep;
}

bool SudokuSolver::checkMapCompleatness() const{
	bool isCompleatMap=true;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(m_SM.GetElement(i,j)==0) isCompleatMap=false;
			if(!isCompleatMap) break;
		}
		if(!isCompleatMap) break;
	}
	return isCompleatMap;
}

int SudokuSolver::checkForInconsistencyByStepForward(std::vector<SudokuMap> &VecExMap){
	std::cout<<"checkForInconsistencyByStepForward Start"<<std::endl;
	//This function should be used if all the other methods do not help to get a step further.
	//It trays to find a inconsistency by checking the effect of setting a certain element to a allowed Value
	//and then checking if the map gets after MaxStep inconsistent.
	//if a inconsistency is found the element is excluded

	//fixme here one should think about opening a new instance to net get in conflict with the current session

	int Step=0;

	SudokuMap TmpSM=m_SM;
	std::vector<SudokuMap>TmpVecExMap=VecExMap;

	std::vector<std::pair<int, std::pair<int,int> > > InconsistancyPos;



	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			std::cout<<"checkForInconsistencyByStepForward "<<i<<","<<j<<std::endl;
			if(m_SM.GetElement(i,j)==0){
				for(int Num=1;Num<=9;Num++){
					if(VecExMap[Num-1].GetElement(i,j)!=-1){
						//we set a prov element
						m_SM.SetElement(i,j,Num);
						//and then we do MaxStep iterations and check for a conflict
						int TotalSteps=0;
						int Stop=0;
						bool isConsistentMap=true;
						int IterationsWithoutUniquSol=0;
						while(IterationsWithoutUniquSol<9 && TotalSteps<m_MaxStep){

							TotalSteps+=solveBySimpleExclusion(VecExMap);
							TotalSteps+=runLineStatusElimination(VecExMap);
							//check map consistency
							if(!checkMapConsistancy(InconsistancyPos)){
								isConsistentMap=false;
								break;
							}
							int TmpSteps=ExcludeByInconsistency(VecExMap);
							//check map consistency
							if(!checkMapConsistancy(InconsistancyPos)){
								isConsistentMap=false;
								break;
							}
							if(TmpSteps!=0){
								if(Stop<20)IterationsWithoutUniquSol=0;
								TotalSteps+=TmpSteps;
								//check map consistency
								if(!checkMapConsistancy(InconsistancyPos)){
									isConsistentMap=false;
									break;
								}
							}
							else{
								TmpSteps=checkForInconsistencyByGroupExclusion(VecExMap);
								if(TmpSteps!=0){
									TotalSteps+=TmpSteps;
									IterationsWithoutUniquSol=0;
									//check map consistency
									if(!checkMapConsistancy(InconsistancyPos)){
										isConsistentMap=false;
										break;
									}
								}
							}
							IterationsWithoutUniquSol++;
							if(m_debug)std::cout<<"TotalSteps "<<TotalSteps<<std::endl;
						}//end while

						if(!isConsistentMap){//we can exclude this Num from this map
							std::cout<<"isConsistentMap=false"<<Num<<" ("<<i<<","<<j<<")"<<std::endl;
							TmpVecExMap[Num-1].SetElement(i,j,-1);
							Step++;
						}
						else{
							if(checkMapCompleatness()) return TotalSteps;
						}
						//give back the SM map and the maybe changed TmpMap
						m_SM=TmpSM;
						VecExMap=TmpVecExMap;
					}
				}
			}
		}
	}
	std::cout<<"checkForInconsistencyByStepForward End"<<std::endl;
	return Step;
}

int SudokuSolver::solveBySimpleExclusion(std::vector<SudokuMap> &VecExMap){
	//this is the simplest exclusion check
	//it excludes lines and locks by checking if the lines or blocks are already blocked
	//and fills obvious solutions
	//the return value are the steps done before no more solutions could be found
	int Steps=0;

	int IterationsWithoutUniquSol=0;

	int Num=1;

	while(IterationsWithoutUniquSol<9){
		VecExMap[Num-1] = calculateExclusionMap(VecExMap[Num-1],Num);
		if(m_debug)std::cout<<"Exclusion Map for: "<<Num<<std::endl;
		//PrintExclusionMap(VecExMap[Num-1]);
		if(FillUniqueSol(VecExMap[Num-1],Num)){
			PrintSolvedStatusMap();//and check again
			IterationsWithoutUniquSol=0;
			Steps++;
		}
		else{
			Num++;
			if(Num>9) Num=1;
			IterationsWithoutUniquSol++;
		}
	}

	return Steps;

}



void SudokuSolver::SolvSudoku(){
	/*
	 * This should be the main function to solve the sudoku
	 * calling one by one differnet methods to solv the sudoku
	 *
	 * we should have  a loop starting from 0 and running to 9
	 * first we calculate a exclusion map
	 * Then we calculate FillUniqueSol
	 * if we find a uniqu solution we calculate exclusion map for the same number agin and check again
	 * no unique solutioon -> go one number up and check all steps....
	*/

	std::vector<SudokuMap> VecExMap; //Build a Vector with 9 maps
	for(int i=0;i<9;i++){
		SudokuMap Ex;
		VecExMap.push_back(Ex);
	}


//46. (5,5) = 5, column insufficiency for [(1,[7,1]),(8,[7,1]),(9,[7,1])] wrt [7,1], (5,5) now [8,9,1]


	int Num=1;
	int IterationsWithoutUniquSol=0;
	int Stop=0;

	int TotalSteps=0;

	while(IterationsWithoutUniquSol<9){

/*		VecExMap[Num-1] = calculateExclusionMap(VecExMap[Num-1],Num);
		std::cout<<"Exclusion Map for: "<<Num<<std::endl;
		PrintExclusionMap(VecExMap[Num-1]);
		if(FillUniqueSol(VecExMap[Num-1],Num)){
			PrintSolvedStatusMap();//and check again
			IterationsWithoutUniquSol=0;
		}
		else{
			Num++;
			if(Num>9) Num=1;
			IterationsWithoutUniquSol++;
		}*/

		TotalSteps+=solveBySimpleExclusion(VecExMap);
		TotalSteps+=runLineStatusElimination(VecExMap);

		int TmpSteps=ExcludeByInconsistency(VecExMap);
		if(TmpSteps!=0){
			if(Stop<20)IterationsWithoutUniquSol=0;
			TotalSteps+=TmpSteps;
		}
		else{
			TmpSteps=checkForInconsistencyByGroupExclusion(VecExMap);
			if(TmpSteps!=0){
				TotalSteps+=TmpSteps;
				IterationsWithoutUniquSol=0;
			}
			else {//if nothig else helps
				TmpSteps=checkForInconsistencyByStepForward(VecExMap);//very time expensive
				if(TmpSteps!=0){
					TotalSteps+=TmpSteps;
					IterationsWithoutUniquSol=0;
				}
				break;
			}
		}
		PrintPossibleNumPerElement(VecExMap);

		IterationsWithoutUniquSol++;
		if(checkMapCompleatness()) break;

/*
		if(IterationsWithoutUniquSol==9){//Simple algo did not help
			if(runLineStatusElimination(VecExMap))IterationsWithoutUniquSol=0;
			else if(ExcludeByInconsistency(VecExMap)){
				if(Stop<20)IterationsWithoutUniquSol=0;
				//Stop++;
			}
			else if(checkForInconsistencyByGroupExclusion(VecExMap))IterationsWithoutUniquSol=0;
			PrintPossibleNumPerElement(VecExMap);
		}*/

	}

	PrintPossibleNumPerElement(VecExMap);

	//final check if we dirived a consistent solution
	std::vector<std::pair<int, std::pair<int,int> > > InconsistancyPos;
	if(checkMapConsistancy(InconsistancyPos)) std::cout<<"We found a consistent solution 8)"<<std::endl;
	else std::cerr<<"Obs: Something went wrong we have an inconsistent solution :("<<std::endl;

	bool MapIsCompleat=checkMapCompleatness();
	if(!MapIsCompleat)std::cerr<<"Map is incomplete!!!"<<std::endl;

	std::cout<<"Solved in "<<TotalSteps<<" steps"<<std::endl;


}

SudokuMap SudokuSolver::getSudokuMap() const{
	return m_SM;
}
void SudokuSolver::setSudokuMap(const SudokuMap &SM){
	m_SM=SM;
}
