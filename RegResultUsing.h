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
	RegResultUsing();
	virtual ~RegResultUsing();
	virtual void process(vector<string> & data);
};

#endif /* REGFORMATOUTPUTRESULT_H_ */
