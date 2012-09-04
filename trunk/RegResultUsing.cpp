/*
 * RegFormatOutputResult.cpp
 *
 *  Created on: Aug 24, 2012
 *      Author: minfang
 */

#include "RegResultUsing.h"
#include <iostream>
using namespace std;
RegResultUsing::RegResultUsing() {

}

RegResultUsing::~RegResultUsing() {
	// TODO Auto-generated destructor stub
}

void RegResultUsing::process(vector<string> & data) {

	cout << endl << "Total:" << data.size() << endl;

	if (data.size() > 0) {
		cout << "Whole string:" << data[0] << endl;

		for(size_t i1=1;i1<data.size();i1++){
			cout<<"Index "<<i1<<":"<<data[i1]<<endl;
		}
	}

}
