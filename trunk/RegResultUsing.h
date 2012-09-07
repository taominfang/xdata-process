/*
 * RegFormatOutputResult.h
 *
 *  Created on: Aug 24, 2012
 *      Author: minfang
 */

#ifndef REGFORMATOUTPUTRESULT_H_
#define REGFORMATOUTPUTRESULT_H_

#include "RegResultProcess.h"

using namespace std;


class RegResultUsing :public RegResultProcess
{
public:
	RegResultUsing(const char * r);
	virtual ~RegResultUsing();
	virtual void process(vector<string> & data);

private :
	string m_replace_formatter;
};

#endif /* REGFORMATOUTPUTRESULT_H_ */
