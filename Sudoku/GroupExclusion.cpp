/*
 * GroupExclusion.cpp
 *
 *  Created on: Aug 1, 2012
 *      Author: Daniel Pelikan
 */

#include "GroupExclusion.h"

GroupExclusion::GroupExclusion():m_debug(false) {
	// TODO Auto-generated constructor stub

}

GroupExclusion::~GroupExclusion() {
	// TODO Auto-generated destructor stub
}

bool GroupExclusion::find(const std::vector<int> &vec, const int &Num) const{
	//checks if a vector contains a certain number
	for(int i=0;i<vec.size();i++){
		if(vec[i]==Num) return true;
	}
return false;
}

std::vector<int> GroupExclusion::mergeVectors(const std::vector<int> &a, const std::vector<int> &b)const{
	std::vector<int> NewVec = a;
	//add the missing elements
	for(int i=0; i<b.size();i++){
		if(!find(a,b[i])) NewVec.push_back(b[i]);
	}
	std::sort(NewVec.begin(), NewVec.end());
	return NewVec;
}
/*
bool GroupExclusion::removeElemnetsWithSameContent(std::vector<std::vector<int> > &Vec){
	//returns true if an element was removed

//Fixme this functions seem to have a bug

	bool change=false;
/*
	std::vector<int> CompareNum;

	for(int i=0;i<Vec.size();i++){
		int tmp=0;
		for(int j=0;j<Vec[i].size();j++){
			tmp+=Vec[i].at(j)*std::pow(10,Vec[i].size()-j-1);
		}
		CompareNum.push_back(tmp);
	}

	//new we remove double elements
	for(int i=0;i<Vec.size();i++){
		for(int j=i+1;j<Vec.size();j++){
			if(CompareNum.at(i)==CompareNum.at(j)){
				Vec.erase(Vec.begin() + j);
				CompareNum.erase(CompareNum.begin() + j);
				j--;
				change=true;
			}
		}
	}

	//remove empty elements
	for(int i=0;i<Vec.size();i++){
		if(Vec[i].size()==0){
			Vec.erase(Vec.begin() + i--);
			change=true;
		}
	}


	return change;
}
*/
bool GroupExclusion::removeInclusivMergedElements(std::vector<std::vector<int> > &Vec, const std::vector<std::pair<int,int> > &MergedElements) const{
	//removes the elements which have been merged and whcih information is now included in alreadu one element

	for(int i=0;i<MergedElements.size();i++){
		if(Vec[MergedElements[i].first].size()>Vec[MergedElements[i].second].size()){
			bool isIncluded=true;
			for(int j=0;j<Vec[MergedElements[i].second].size();j++){
				if(!find(Vec[MergedElements[i].first],Vec[MergedElements[i].second].at(j)))isIncluded=false;
			}
			if(isIncluded) Vec.erase(Vec.begin()+MergedElements[i].second);
		}
		else{
			bool isIncluded=true;
			for(int j=0;j<Vec[MergedElements[i].first].size();j++){
				if(!find(Vec[MergedElements[i].second],Vec[MergedElements[i].first].at(j)))isIncluded=false;
			}
			if(isIncluded) Vec.erase(Vec.begin()+MergedElements[i].first);
		}

	}

}

std::vector<std::vector<int> > GroupExclusion::GroupAlgo(const std::vector<std::vector<int> > &GroupVector) const{
	//great empty map
	std::vector<std::vector<int> > GroupCombMap;
	for(int i=0;i<9;i++){
		GroupCombMap.push_back(std::vector<int>());
	}
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			GroupCombMap[i].push_back(0);
		}
	}

	//Grouping Algo
	for(int i=0;i<GroupVector.size();i++){//find couples of ij
		for(int j=i+1;j<GroupVector.size();j++){
			for(int Num=1;Num<=9;Num++){
				if(find(GroupVector[i],Num)&&find(GroupVector[j],Num)){
					GroupCombMap[i].at(j)++;
				}
			}
		}
	}


	//Print the map
	if(m_debug)std::cout<<"\t0 1 2 3 4 5 6 7 8"<<std::endl;
	for(int i=0;i<9;i++){//find couples of ij
		if(m_debug)std::cout<<i<<"\t";
		for(int j=0;j<9;j++){
			if(GroupCombMap[i].at(j)==0)if(m_debug)std::cout<<"  ";
			else if(m_debug)std::cout<<GroupCombMap[i].at(j)<<" ";
		}
		if(m_debug)std::cout<<std::endl;
	}

	return GroupCombMap;
}

void GroupExclusion::printGroupVector(const std::vector<std::vector<int> >&GroupVector) const{

	for(int i=0;i<GroupVector.size();i++){
		std::cout<<"Element"<<i<<": ";
		for(int j=0;j<GroupVector[i].size();j++){
			std::cout<<GroupVector[i].at(j)<<",";
		}
		std::cout<<"\n";
	}
	std::cout<<"\n\n"<<std::endl;
}

std::vector<std::pair<int,int> > GroupExclusion::mergeTheLargestGroups(const std::vector<std::vector<int> > &GroupCombMap, std::vector<std::vector<int> > &GroupVector) const{
	//returns a vector with which pairs had been merged

	std::vector<std::pair<int,int> > MergedElements;

	//find the largest Group(s)
	int LargestGroup=0;
	for(int i=0;i<9;i++){
		for(int j=i+1;j<9;j++){
			if(GroupCombMap[i].at(j)>LargestGroup) LargestGroup=GroupCombMap[i].at(j);
		}
	}

	//Merge the largest Group in case of multiple group we merge the first one and check again
	std::vector<int> OldGroupIdx;
	for(int i=0;i<9;i++){
		for(int j=i+1;j<9;j++){
			if(GroupCombMap[i].at(j)==LargestGroup && LargestGroup!=0){
				GroupVector[i]=mergeVectors(GroupVector[i],GroupVector[j]);
				MergedElements.push_back(std::make_pair(i,j));
			}
		}
	}

	return MergedElements;
}

bool GroupExclusion::removeElementsInclusivElements(std::vector<std::vector<int> > &GroupVector) const{
	//removes elements which are already included completely in a group
	/*
	 * for example
	 * element 1: 12
	 * element 2: 123456
	 * element 3: 45678
	 *
	 * element 1 can be removed since it is already included in element 2
	 */

	bool changed=false;

	bool CompleatlyIncluded=true;

	for(int i=0;i<GroupVector.size();i++){
		for(int j=i+1;j<GroupVector.size();j++){
			CompleatlyIncluded=true;
			for(int k=0;k<GroupVector[j].size();k++){
				if(!find(GroupVector[i],GroupVector[j].at(k))){//check if j is in subgroup i
					CompleatlyIncluded=false;
					break;
				}
			}
			if(CompleatlyIncluded){
				GroupVector.erase(GroupVector.begin() + j--);
				 changed=true;
			}
		}
	}
	return changed;
}

std::vector<std::pair<int,std::vector<int> > >  GroupExclusion::CheckForExclusions(std::vector< std::vector<int> > GroupVector) const{
//fixme check if GroupVector as a ref

	/*the output is:
	 * Element, excluded values
	 * for ex: Element 1: excude 1,4,5
	 */

	std::vector<std::pair<int,std::vector<int> > > Output;

	//input is a map which contains all excluded values for a certain element
	std::vector< std::vector<int> > GroupVectorCopy;
	GroupVectorCopy=GroupVector;

	//we now combine the largest group
	std::vector<std::vector<int> > GroupCombMap;
	std::vector<std::pair<int,int> > MergedElements;

	int MaxIterations=0;
	while(GroupVector.size()!=2 && GroupVector.size()>1 && MaxIterations<10){
		GroupCombMap = GroupAlgo(GroupVector);
		MergedElements = mergeTheLargestGroups(GroupCombMap,GroupVector);
		if(m_debug)printGroupVector(GroupVector);
		//removeElemnetsWithSameContent(GroupVector);//seems this function has a bug? and is not needed since in InclusiveMergedEl.
		removeInclusivMergedElements(GroupVector,MergedElements);
		removeElementsInclusivElements(GroupVector);
		if(m_debug)printGroupVector(GroupVector);

		MaxIterations++;
		//Max iteration check
	}

	if(GroupVector.size()!=2) return Output;

	//we check now which element belongs to which group
	std::vector<int> ElementsGroup1;
	std::vector<int> ElementsGroup2;

	for(int i=0;i<GroupVectorCopy.size();i++){
		if(GroupVectorCopy[i].size()!=0){
			int Group1=0;
			int Group2=0;
			for(int j=0;j<GroupVectorCopy[i].size();j++){
				if(find(GroupVector[0],GroupVectorCopy[i].at(j)))Group1++;
				if(find(GroupVector[1],GroupVectorCopy[i].at(j)))Group2++;
			}
			if(Group1>Group2)ElementsGroup1.push_back(i);
			if(Group2>Group1)ElementsGroup2.push_back(i);
		}
	}

	//if we have in one group exactly the same amount of elements as numbers we have a unique group and can exclude
	//the overlapping numbers from the other group

	if(ElementsGroup1.size()==GroupVector[0].size() && ElementsGroup2.size()!=GroupVector[1].size()){
		//one uniq group remove overlap:
		std::vector<int> ExcludedElements;
		std::cout<<"The numbers ";
		for(int i=0;i<GroupVector[0].size();i++){
			if(find(GroupVector[1],GroupVector[0].at(i))){
				std::cout<<GroupVector[0].at(i)<<",";
				ExcludedElements.push_back(GroupVector[0].at(i));
			}
		}
		std::cout<<"can be excluded ";

		std::cout<<"for Element: ";
		for(int i=0;i<ElementsGroup2.size();i++){
			std::cout<<ElementsGroup2.at(i)<<",";
			Output.push_back(std::make_pair(ElementsGroup2.at(i),ExcludedElements));
		}
		std::cout<<std::endl;
	}

	if(ElementsGroup1.size()!=GroupVector[0].size() && ElementsGroup2.size()==GroupVector[1].size()){
		//one uniq group remove overlap:
		std::vector<int> ExcludedElements;

		std::cout<<"The numbers ";
		for(int i=0;i<GroupVector[1].size();i++){
			if(find(GroupVector[0],GroupVector[1].at(i))){
				std::cout<<GroupVector[1].at(i)<<",";
				ExcludedElements.push_back(GroupVector[1].at(i));
			}
		}
		std::cout<<"can be excluded ";

		std::cout<<"for Element: ";
		for(int i=0;i<ElementsGroup1.size();i++){
			std::cout<<ElementsGroup1.at(i)<<",";
			Output.push_back(std::make_pair(ElementsGroup1.at(i),ExcludedElements));
		}
		std::cout<<std::endl;
	}

	return Output;

}
