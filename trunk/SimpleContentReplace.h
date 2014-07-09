/*
 * SimpleContentReplace.h
 *
 *  Created on: Aug 8, 2012
 *      Author: minfang
 */

#ifndef SimpleContentReplace_H_
#define SimpleContentReplace_H_
#include <map>
#include <string>

using namespace std;
class SimpleContentReplace {
public:
	SimpleContentReplace();
	virtual ~SimpleContentReplace();


	bool variableReplace(istream & in,map<string,string> & keyValues,ostream & out);
private:

};

#endif /* SimpleContentReplace_H_ */
