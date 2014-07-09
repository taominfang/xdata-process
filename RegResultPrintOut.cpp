/*
 * RegResultPrintOut.cpp
 *
 *  Created on: Sep 3, 2012
 *      Author: minfang
 */

#include "RegResultPrintOut.h"
#include <iostream>
#include "Verbose.h"
using namespace std;
RegResultPrintOut::RegResultPrintOut() {
	// TODO Auto-generated constructor stub

}

RegResultPrintOut::~RegResultPrintOut() {
	// TODO Auto-generated destructor stub
}

void RegResultPrintOut::process(vector<string> & data) {


	if (data.size() > 0) {

		Verbose::printf("<Whole string>[%s]",data[0].c_str() );


		for(size_t i1=1;i1<data.size();i1++){
			Verbose::printf("$%d$[%s]",i1,data[i1].c_str() );

		}
		Verbose::println("");

	}

}
