/*
 * RegResultPrintOut.h
 *
 *  Created on: Sep 3, 2012
 *      Author: minfang
 */

#ifndef REGRESULTPRINTOUT_H_
#define REGRESULTPRINTOUT_H_

#include "RegResultProcess.h"

class RegResultPrintOut: public RegResultProcess {
public:
	RegResultPrintOut();
	virtual ~RegResultPrintOut();

	virtual void process(vector<string> & data);
};

#endif /* REGRESULTPRINTOUT_H_ */
