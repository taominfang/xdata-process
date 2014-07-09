/*
 * RegFormatOutputResult.cpp
 *
 *  Created on: Aug 24, 2012
 *      Author: minfang
 */

#include "RegResultUsing.h"
#include <iostream>
#include "SimpleContentReplace.h"
#include <map>
#include <stdio.h>
#include "Verbose.h"
#include <sstream>
using namespace std;
RegResultUsing::RegResultUsing(const char * r	):m_replace_formatter(r) {

	Verbose::printf("out pattern:[%s]\n",r);

}

RegResultUsing::~RegResultUsing() {
	// TODO Auto-generated destructor stub
}

void RegResultUsing::process(vector<string> & data) {

	if(data.size() ==0){
		return;
	}



	map<string,string> replaceMap;
	replaceMap["matched_whole_string"]=data[0];

	for(size_t i1=0;i1<data.size();i1++){
		char buff[20];
		sprintf(buff,"%d",i1);
		replaceMap[buff]=data[i1];
	}

	SimpleContentReplace sp;
	stringstream sin(m_replace_formatter,stringstream::in) ;

	sp.variableReplace(sin,replaceMap	,cout);




}
