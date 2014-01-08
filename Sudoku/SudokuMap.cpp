/*
 * SudokuMap.cpp
 *
 *  Created on: Jul 29, 2012
 *      Author: Daniel Pelikan
 */

#include "SudokuMap.h"

SudokuMap::SudokuMap() {

	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			SudMap[i][j]=0;
		}
	}


}

SudokuMap::~SudokuMap() {
	// TODO Auto-generated destructor stub
}

void SudokuMap::PrintMap() const{
	//Prints the map
	std::cout<<"\n\n\n|-----------------------|\n";
	for(int i=0;i<9;i++){
		std::cout<<"| ";
		for(int j=0;j<9;j++){
			if(SudMap[i][j]==0)std::cout<<" "<<" ";//Empty space in case of a 0
			else std::cout<<SudMap[i][j]<<" ";
			if((j+1)%3==0 && (j+1)!=9)std::cout<<"| ";
		}
		std::cout<<"|\n";
		if((i+1)%3==0)std::cout<<"|-----------------------|\n";
	}
	std::cout<<"\n\n\n"<<std::endl;
}

void SudokuMap::EnterMap(){

	std::cout<<"Fill the SudokuMap, space for empty element"<<std::endl;

	std::string SKLine="";

	for(int line=0;line<9;line++){
		std::cout<<"Line "<<line+1<<":";
		std::getline(std::cin, SKLine);
		//std::cin>>SKLine;
		if(FillMapByLine(SKLine,line)!=SUCCESS){
			std::cout<<"SKLine "<<SKLine<<std::endl;
			std::cerr<<"Try to enter again"<<std::endl;
			return;
		}
		SKLine="";
	}
}

StatusCode SudokuMap::FillMapByLine(const std::string &LineIn, const int &EditLine){
	if(LineIn.size()!=9){
		std::cerr<<"Error: Input is !=9 characters long"<<std::endl;
		return FAILURE;
	}
	if(EditLine>=9){
		std::cerr<<"LineNumber >=9"<<std::endl;
		return FAILURE;
	}
	//check for <10 and different 0-9," "

	for(int i=0;i<LineIn.size();i++){
		if(LineIn.at(i)==' ')SudMap[EditLine][i]=0;
		else SudMap[EditLine][i]=CharToInt(LineIn[i]);
	}

	return SUCCESS;
}

int SudokuMap::GetElement(const int &i,const int &j) const{
	if(i>=9 || j>=9 || i<0 || j<0){
		std::cerr<<"Out of Range"<<std::endl;
		return 0;
	}
	return SudMap[i][j];
}

void SudokuMap::SetElement(const int &i,const int &j,const int &Num){
	SudMap[i][j]=Num;
}

std::pair<int,int> SudokuMap::locateBlock(const int &i,const int &j) const{

	std::pair<int,int> Block=std::make_pair((i)/3,(j)/3);

	//std::cout<<"Pair "<<Block.first<<"\t"<<Block.second<<std::endl;

	return Block;
}

void SudokuMap::printBlock(const std::pair<int,int> &Block) const{
	std::cout<<"\n\n\n|-------|\n";

	for(int i=0;i<3;i++){
		std::cout<<"| ";
		for(int j=0;j<3;j++){
			if(GetElement(Block.first*3+i,Block.second*3+j)==0)std::cout<<" ";
			else std::cout<<GetElement(Block.first*3+i,Block.second*3+j);
			if(j+1!=3)std::cout<<" ";
			if((j+1)%3==0 && (j+1)!=3)std::cout<<"| ";
		}
		std::cout<<" |\n";
		if((i+1)%3==0)std::cout<<"|-------|\n";
	}
}
