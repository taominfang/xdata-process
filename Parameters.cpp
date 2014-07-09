/*
 * Parameters.cpp
 *
 *  Created on: Aug 11, 2012
 *      Author: minfang
 */

#include "Parameters.h"
#include "string.h"
#include "list"
#include <stdarg.h>



Parameters::Parameters() {

}

Parameters::~Parameters() {

}

map<string, string> Parameters::m_regular_parameters;

map<string, ParameterElement> Parameters::m_parameters_list;

/**
 * return 0, no error
 *
 * return 1, has errors but all errors are under control
 *
 * return 2, serious errors happen, discontinue running.
 */

int Parameters::readParameter(int argc, char ** argv) {

	map<string, ParameterElement *> allParamters =
			managermentPossibleParameters();


	list<string> unkonwParameterList;
	list<string> errorMessage;

	for (int i1 = 1; i1 < argc; i1++) {

		if (argv[i1][0] == '-') {
			string pa = argv[i1];
			map<string, ParameterElement *>::iterator p = allParamters.find(pa);
			if (p != allParamters.end()) {

				for (list<string>::iterator i2 =
						p->second->m_and_depends.begin();
						i2 != p->second->m_and_depends.end(); i2++) {
				}
				for (list<string>::iterator i2 =
						p->second->m_or_depends.begin();
						i2 != p->second->m_or_depends.end(); i2++) {
				}

				//cout<<p->second->m_name<<" "<<p->second->m_require_extra_one<<" "<<argv[i1+1]<<endl;
				if (p->second->m_require_extra_one) {
					i1++;
					if (i1 < argc) {
						add(p->second->m_name, argv[i1]);
						;
					} else {
						string error = pa;
						error += " should follow a extra parameter";
						errorMessage.push_back(error);
					}
				} else {

					add(p->second->m_name, "1");
				}

			}

			else {
				unkonwParameterList.push_back(argv[i1]);
			}
		}

		else {
			unkonwParameterList.push_back(argv[i1]);
		}
	}

	//do the parameter check

	for (map<string, string>::iterator i1 = m_regular_parameters.begin();
			i1 != m_regular_parameters.end(); i1++) {
		string p = i1->first;
		map<string, ParameterElement>::iterator pe = m_parameters_list.find(p);

		if (pe == m_parameters_list.end()) {
			string error = p;
			error += " is not find in  m_parameters_list , system error 1 ";
			errorMessage.push_back(error);
		}

		else {
			for (list<string>::iterator i2 = pe->second.m_and_depends.begin();
					i2 != pe->second.m_and_depends.end(); i2++) {

				if (m_regular_parameters.find(*i2)
						== m_regular_parameters.end()) {

					string error = "";

					map<string, ParameterElement>::iterator need =
							m_parameters_list.find(*i2);
					if (pe == m_parameters_list.end()) {
						error += *i2;
						error +=
								" is not find in  m_parameters_list , system error 2";
						errorMessage.push_back(error);
					} else {
						int start = 0;
						for (list<string>::iterator i3 =
								need->second.m_aliases.begin();
								i3 != need->second.m_aliases.end();
								i3++, start++) {
							if (start != 0) {
								error += "] or [";
							} else {
								error += "[";
							}
							error += *i3;
						}
						error += "]";
						error += " is required by " + p;
						errorMessage.push_back(error);
					}
				}
			}

			bool er = true;

			if (pe->second.m_or_depends.size() == 0) {
				er = false;
			}

			for (list<string>::iterator i2 = pe->second.m_or_depends.begin();
					i2 != pe->second.m_or_depends.end(); i2++) {
				if (m_regular_parameters.find(*i2)
						!= m_regular_parameters.end()) {
					er = false;
				}
			}

			if (er) {
				string error = p;
				error += " required at least one of ";
				for (list<string>::iterator i2 =
						pe->second.m_or_depends.begin();
						i2 != pe->second.m_or_depends.end(); i2++) {

					map<string, ParameterElement>::iterator need =
							m_parameters_list.find(*i2);
					if (pe == m_parameters_list.end()) {
						error += *i2;
						error +=
								" is not find in  m_parameters_list , system error 2";
						errorMessage.push_back(error);
						break;
					} else {
						int start = 0;
						error+="[ ";
						for (list<string>::iterator i3 =
								need->second.m_aliases.begin();
								i3 != need->second.m_aliases.end();
								i3++, start++) {
							if (start != 0) {
								error += " or ";
							}
							error += *i3;
						}
						error += "] ";


					}


				}
				errorMessage.push_back(error);
			}
		}

	}

	for (map<string, ParameterElement *>::iterator i1 = allParamters.begin();
			i1 != allParamters.end(); i1++) {
		if (i1->second->m_required
				&& m_regular_parameters.find(i1->first)
						== m_regular_parameters.end()) {
			string error = i1->first;
			error += " is required";
			errorMessage.push_back(error);
		}
	}

	if (unkonwParameterList.size() > 0 || errorMessage.size() > 0) {

		for (list<string>::iterator i1 = errorMessage.begin();
				i1 != errorMessage.end(); i1++) {
			cerr << *i1 << endl;
		}
		if (get("report_error") != NULL) {

			for (list<string>::iterator i1 = unkonwParameterList.begin();
					i1 != unkonwParameterList.end(); i1++) {
				cerr << "Unknow parameter:" << *i1 << endl;
			}

		}

		if (errorMessage.size() > 0) {
			//should stop the program
			return 2;
		} else {

			//has error ,but still can continue to run
			return 1;
		}
	} else {
		return 0;
	}

}

list<string> * createStringList(const char * first, ...) {

	if (first == NULL) {
		return NULL;
	}
	list<string> *re = new list<string>;
	va_list vlist;

	va_start(vlist, first);
	const char * p = first;

	do {
		string pp(p);
		re->push_back(p);
		p = va_arg(vlist,char *);
	} while (p != NULL);
	va_end(vlist);
	return re;
}
