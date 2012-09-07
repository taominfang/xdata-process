/*
 * RegSearch.cpp
 *
 *  Created on: Aug 23, 2012
 *      Author: minfang
 */

#include "RegSearch.h"
#include "Parameters.h"
#include "RegResultUsing.h"
#include "RegResultPrintOut.h"

RegSearch::RegSearch() :
		mp_processor(NULL) {
	// TODO Auto-generated constructor stub

	if (Parameters::get("awk_out_formater") != NULL) {

		mp_processor = new RegResultUsing(Parameters::get("awk_out_formater"));
	}

	else {

		mp_processor = new RegResultPrintOut();
	}
}

RegSearch::~RegSearch() {
	// TODO Auto-generated destructor stub

	if (mp_processor != NULL) {
		delete mp_processor;
	}
}

bool RegSearch::file_regex_callback(
		const boost::match_results<TripleBufferIFileStream::const_iterator>& what,
		RegSearch & processor) {
	// what[0] contains the whole string
	// what[5] contains the class name.
	// what[6] contains the template specialisation if any.
	// add class name and position to map:
	//class_index[what[5].str() + what[6].str()] = what.position(5);
	return processor.process(what);
}

int RegSearch::awk_search_reg() {

	//boost::regex expression(Parameters::get("awk_search_reg"));
	boost::regex expression(Parameters::get("awk_search_reg"));

	if (Parameters::get("input_file") != NULL) {
		//source is file
		TripleBufferIFileStream inp(Parameters::get("input_file"), ios::in,
				102400);
		if (inp.is_open()) {

			TripleBufferIFileStream::const_iterator begin = inp.begin();
			TripleBufferIFileStream::const_iterator end = inp.end();

			boost::regex expression(Parameters::get("awk_search_reg"));
			boost::regex_iterator<TripleBufferIFileStream::const_iterator> m1(
					begin, end, expression);
			boost::regex_iterator<TripleBufferIFileStream::const_iterator> m2;

			RegSearch processor;
			for (; m1 != m2; m1++) {
				file_regex_callback(*m1, processor);
			}

			//std::for_each(m1, m2, &regex_callback);
			inp.close();
		}
	}

	else {
		//source is stdin, using string as the reg source

		if (Parameters::get("split_string") != NULL) {
			// the input will be split , by the string
		} else {
			//split by new line
		}
	}

	return 0;
}

bool RegSearch::process(
		const boost::match_results<TripleBufferIFileStream::const_iterator>& what) {

	if (mp_processor != NULL) {

		vector<string> pa;

		for (int i1 = 0, total = what.size(); i1 < total; i1++) {

			pa.push_back(what[i1].str());

		}

		mp_processor->process(pa);
	}
	return true;
}
