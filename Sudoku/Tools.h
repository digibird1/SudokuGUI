/*
 * Tools.h
 *
 *  Created on: Jul 29, 2012
 *      Author: Daniel Pelikan
 */

#ifndef TOOLS_H_
#define TOOLS_H_
#include <cstring>
#include <sstream>

int CharToInt(const char &c){
	std::stringstream ss;
	ss<<c;
	int i;
	ss>>i;
	return i;
}


#endif /* TOOLS_H_ */
