/*
 * dp.cpp
 *
 *  Created on: Aug 5, 2012
 *      Author: minfang
 */

#include "dp.h"

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <map>
#include <exception>
#include <typeinfo>
#include "Parameters.h"
#include "UnitTest.h"
#include "RegSearch.h"
#include "Verbose.h"
#include "system_dep_def.h"
using namespace std;
using namespace boost;

dp::dp() {
	// TODO Auto-generated constructor stub

}

dp::~dp() {
	// TODO Auto-generated destructor stub
}

void usage(char * dp) {
	cout << dp << " options" << endl;
	;

	cout << "options:" << endl;

	Parameters::printUage(cout);
}

void init_parameter_group() {
	// setting the possible parameters

	// show help information

	Parameters::initAdd(
			ParameterElement("help", createStringList("--help", "-H", NULL),
					"show help information"));

	///Unit test
	Parameters::initAdd(
			ParameterElement("unit_test",
					createStringList("--unit_test", "-U", NULL),
					"Full unit test"));

	// do not do any action, just check the grammar
	Parameters::initAdd(
			ParameterElement("check_only",
					createStringList("--check_only", NULL),
					"check the grammar"));

	// print error message to console
	Parameters::initAdd(
			ParameterElement("report_error",
					createStringList("--report_error", NULL),
					"print error message to console"));

	// input file
	Parameters::initAdd(
			ParameterElement("input_file",
					createStringList("--input_file", "-i", NULL), "Input file",
					false, 1));

	// force to remove all variable
	Parameters::initAdd(
			ParameterElement("remove_unmatched_variable",
					createStringList("--remove_unmatched_variable", NULL),
					"Even there is value for replace, remove all '$..$'"));

	Parameters::initAdd(
			ParameterElement("awk_split_by_reg",
					createStringList("--awk_split_by_reg", NULL),
					"Like awk -F , split the string into several column", false,
					1));

	Parameters::initAdd(
			ParameterElement("awk_search_reg",
					createStringList("--awk_search_reg", NULL), "Desc", false,
					1));

	Parameters::initAdd(
			ParameterElement("awk_out_formater",
					createStringList("--awk_out_formater", NULL),
					"Define the formatter for out put", false, 1, NULL,
					createStringList("awk_search_reg", "awk_split_by_reg",
					NULL)));
	Parameters::initAdd(
			ParameterElement("verbose",
					createStringList("--verbose", "-v", NULL),
					"Print more information to STDERR"));

}

int dispatch(int argc, char ** argv) throw () {

	if (Parameters::get("verbose") != NULL) {
		Verbose::enable = true;
	}

	//Verbose::printf("new line chars len:%d\n",strlen(NEW_LINE));

	if (Parameters::get("help") != NULL) {
		usage(argv[0]);
	}

	else if (Parameters::get("unit_test") != NULL) {
		UnitTest ut;
		ut.runAll();
	}

	else if (Parameters::get("awk_search_reg") != NULL) {
		return RegSearch::awk_search_reg();
	}
	//depend the parameters, do action
	return 0;
}

int main(int argc, char ** argv) {

	init_parameter_group();

	int rp = Parameters::readParameter(argc, argv);

	if (Parameters::get("verbose") != NULL) {
		Parameters::printAll(cout);
	}
	if (rp == 2) {
		cerr << "Parameters error quit" << endl;
		return 2;
	}

	try {
		return dispatch(argc, argv);
	} catch (std::exception& e) {
		cerr << "exception caught: " << e.what() << endl;
	} catch (...) {
		cerr << " unknown exception" << endl;
	}
}
