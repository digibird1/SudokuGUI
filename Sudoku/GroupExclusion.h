/*
 * GroupExclusion.h
 *
 *  Created on: Aug 1, 2012
 *      Author: Daniel Pelikan
 */

#ifndef GROUPEXCLUSION_H_
#define GROUPEXCLUSION_H_

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

class GroupExclusion {
public:
	GroupExclusion();
	virtual ~GroupExclusion();

	bool find(const std::vector<int> &vec,const int &Num) const;
	std::vector<int> mergeVectors(const std::vector<int> &a,const std::vector<int> &b) const;
//	bool removeElemnetsWithSameContent(std::vector<std::vector<int> > &Vec);
	bool removeInclusivMergedElements(std::vector<std::vector<int> > &Vec, const std::vector<std::pair<int,int> > &MergedElements) const;
	std::vector<std::vector<int> > GroupAlgo(const std::vector<std::vector<int> > &GroupVector) const;
	void printGroupVector(const std::vector<std::vector<int> >&GroupVector) const;
	std::vector<std::pair<int,int> > mergeTheLargestGroups(const std::vector<std::vector<int> > &GroupCombMap, std::vector<std::vector<int> > &GroupVector) const;
	bool removeElementsInclusivElements(std::vector<std::vector<int> > &GroupVector) const;

	std::vector<std::pair<int,std::vector<int> > > CheckForExclusions(std::vector< std::vector<int> > GroupVector) const;

private:
	bool m_debug;

};

#endif /* GROUPEXCLUSION_H_ */
