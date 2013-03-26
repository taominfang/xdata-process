/*
 * RegResultPrintOut.cpp
 *
 *  Created on: Sep 3, 2012
 *      Author: minfang
 */

#include "RegResultPrintOut.h"
#include <iostream>
using namespace std;
RegResultPrintOut::RegResultPrintOut() {
	// TODO Auto-generated constructor stub

}

RegResultPrintOut::~RegResultPrintOut() {
	// TODO Auto-generated destructor stub
}

void RegResultPrintOut::process(vector<string> & data) {


	if (data.size() > 0) {
		cout << "<Whole string>[" << data[0] <<"]";

		for(size_t i1=1;i1<data.size();i1++){
			cout<<"<$"<<i1<<"$>["<<data[i1]<<"]";
		}
		cout<<endl;
	}

}
