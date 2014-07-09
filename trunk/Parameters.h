/*
 * Parameters.h
 *
 *  Created on: Aug 11, 2012
 *      Author: minfang
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <map>
#include <list>
#include <iostream>

using namespace std;

list<string> * createStringList(const char * first, ...);

class ParameterElement {
public:
	string m_name;
	string m_usage_description;
	bool m_required;
	bool m_require_extra_one;

	list<string> m_and_depends, m_or_depends;
	list<string> m_aliases;

	ParameterElement(const char * name, list<string> *aliases,
			const char * desc, bool required = false, int extra = 0,
			list<string> *andDepends = NULL, list<string> *orDepends = NULL) :
			m_name(name), m_usage_description(desc), m_required(required), m_and_depends(), m_or_depends(), m_aliases() {

		//cout<<m_and_depends.size()<<endl;
		if (aliases != NULL) {
			m_aliases = *aliases;
		}

		if (extra == 0) {
			m_require_extra_one = false;
		}
		else{
			m_require_extra_one=true;
		}

		if (andDepends != NULL) {
			cout << name << " set up and depends" << endl;
			m_and_depends = *andDepends;
			delete andDepends;
		}

		if (orDepends != NULL) {
			m_or_depends = *orDepends;
			delete orDepends;
		}

	}

	ParameterElement() {

	}

	~ParameterElement() {

	}

};

class Parameters {
public:
	Parameters();
	virtual ~Parameters();


	static void printAll(ostream &out) {

		//out << "Print all parameters" << endl;

		for (map<string, string>::iterator i1 = m_regular_parameters.begin();
				i1 != m_regular_parameters.end(); i1++) {
			cerr << "[" << i1->first << "]=" << i1->second << endl;
		}
	}

	static void printUage(ostream &out) {
		out<<endl;
		for (map<string, ParameterElement>::iterator i1 =
				m_parameters_list.begin(); i1 != m_parameters_list.end();i1++) {

			for (list<string>::iterator i2 = i1->second.m_aliases.begin();
					i2 != i1->second.m_aliases.end(); i2++) {
				cout<<*i2<<
						"   ";
			}

			out<<endl<<"\t"<<i1->second.m_usage_description<<endl;

			out<<endl;


		}
	}

	static int readParameter(int argc, char ** argv);

	static const char * get(const char * key) {
		if (m_regular_parameters.find(key) == m_regular_parameters.end()) {
			return NULL;
		}

		else {
			return m_regular_parameters[key].c_str();
		}
	}

	static map<string, ParameterElement *> managermentPossibleParameters() {

		map<string, ParameterElement *> re;
		for (map<string, ParameterElement>::iterator i1 =
				m_parameters_list.begin(); i1 != m_parameters_list.end();) {

			if (i1->second.m_aliases.size() == 0) {
				map<string, ParameterElement>::iterator de = i1;
				i1++;
				m_parameters_list.erase(de);
			}

			else {
				for (list<string>::iterator i2 = i1->second.m_aliases.begin();
						i2 != i1->second.m_aliases.end(); i2++) {
					re[*i2] = &(i1->second);
				}

				i1++;
			}

		}

		return re;
	}

	static void initAdd(ParameterElement a) {
		if (m_parameters_list.find(a.m_name) == m_parameters_list.end()) {
			m_parameters_list[a.m_name] = a;
		}
	}

private:
	static map<string, string> m_regular_parameters;
	static map<string, ParameterElement> m_parameters_list;
	static void add(string  key, const char * value) {
		m_regular_parameters[key] = value;
	}

};

#endif /* PARAMETERS_H_ */
