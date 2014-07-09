/*
 * SimpleContentReplace.cpp
 *
 *  Created on: Aug 8, 2012
 *      Author: minfang
 */

#include "SimpleContentReplace.h"
#include <iostream>

#include <boost/scoped_array.hpp>
#include "Verbose.h"
#include "Parameters.h"

SimpleContentReplace::SimpleContentReplace() {


}

SimpleContentReplace::~SimpleContentReplace() {

}

#define BUFF_SIZE 10240
#define MAX_VARIABLE_SIZE 100
bool SimpleContentReplace::variableReplace(istream & in,
		map<string, string> & keyValues, ostream & out) {

	boost::scoped_array<char> _buff(new char[BUFF_SIZE]);

	boost::scoped_array<char> _variable(new char[MAX_VARIABLE_SIZE + 1]);
	char * buff = _buff.get();
	char * variable = _variable.get();
	bool escape = false;
	bool varaibleStart = false;
	size_t variable_index = 0;

	int iLineNumber=1;
	int iCharNumber=1;


	while (in.good()) {

		streamsize len = in.readsome(buff, BUFF_SIZE);

		if (len == 0) {
			break;
		}

		//cout << "get " << len << endl;

		for (streamsize i1 = 0; i1 < len; i1++) {
			char c = buff[i1];

			//cout << c;

			if (varaibleStart) {

				if (c == '$') {
					varaibleStart = false;
					//end variable
					variable[variable_index] = 0;
					map<string, string>::iterator f = keyValues.find(variable);
					//cout << "try to replace:" << variable << endl;
					if (f != keyValues.end()) {
					//	cout<<"find :"<<f->second<<endl;
						Verbose::printf("find v:[%s] replace it to [%s]\n",variable,f->second.c_str());
						out << f->second;
					}
					else{
						cerr<<"not find value for "<<variable<<endl;
					}
					variable_index=0;
				}

				else if (variable_index < MAX_VARIABLE_SIZE) {
					variable[variable_index++] = c;

				} else {
					//there is not a valid string for replace
					//error TODO
					out << '$';
					for (size_t i1 = 0; i1 < variable_index; i1++) {
						out << variable[i1];
					}
					varaibleStart = false;
				}
			} else if (escape) {
				escape = false;
				if (c == 'n') {
					out << "\n";
				} else if (c == 'r') {
					out << "\r";
				} else {
					//error
					//TODO
					out << c;
				}
			} else {
				if (c == '\\') {
					escape = true;
					//cout << "escape is true" << endl;
				}

				else if (c == '$') {

					varaibleStart = true;

				}

				else {
					out << c;

					if(c == '\n'){
						iLineNumber++;
						iCharNumber=1;
					}
				}
			}
		}
	}

	return true;

}
