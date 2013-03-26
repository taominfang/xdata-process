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
#include "string"
#include "system_dep_def.h"

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

bool RegSearch::fire_regex_callback(
		const boost::match_results<TripleBufferIFileStream::const_iterator>& what,
		RegSearch & processor) {
	// what[0] contains the whole string
	// what[5] contains the class name.
	// what[6] contains the template specialisation if any.
	// add class name and position to map:
	//class_index[what[5].str() + what[6].str()] = what.position(5);
	return processor.process(what);
}
bool RegSearch::fire_regex_callback(
		const boost::match_results<string::iterator>& what,
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
	RegSearch processor;
	if (Parameters::get("input_file") != NULL) {
		//source is file
		TripleBufferIFileStream inp(Parameters::get("input_file"), ios::in,
				DEFAULT_TRIPLE_BUFFER_SIZE);
		if (inp.is_open()) {

			TripleBufferIFileStream::const_iterator begin = inp.begin();
			TripleBufferIFileStream::const_iterator end = inp.end();

			boost::regex_iterator<TripleBufferIFileStream::const_iterator> m1(
					begin, end, expression);
			boost::regex_iterator<TripleBufferIFileStream::const_iterator> m2;

			for (; m1 != m2; m1++) {
				fire_regex_callback(*m1, processor);
			}

			//std::for_each(m1, m2, &regex_callback);
			inp.close();
		}
	}

	else {
		//source is stdin, using string as the reg source
		const char * splitStr = Parameters::get("split_string");

		if (splitStr == NULL || strlen(splitStr) == 0) {
			// the input will be split , by the string
			splitStr = NEW_LINE;
		}
		int splitStrLen = strlen(splitStr);
		boost::scoped_array<char> _inputBuffer(new char[MAX_INPUT_BUFFER_SIZE]);

		char * inputBuffer = _inputBuffer.get();

		int iReadIndex = 0;
		int limit = MAX_INPUT_BUFFER_SIZE - 1;

		int compareIndex = 0;

		for (;;) {
			if (iReadIndex == limit) {

				inputBuffer[iReadIndex] = 0;
				//force using the input data TODO

				string data = inputBuffer;

				boost::regex_iterator<string::iterator> m1(data.begin(),
						data.end(), expression);
				boost::regex_iterator<string::iterator> m2;

				for (; m1 != m2; m1++) {
					fire_regex_callback(*m1, processor);
				}

				iReadIndex = 0;
				compareIndex = 0;

			}

			cin.read(&inputBuffer[iReadIndex], 1);

			if (!cin.good()) {
				break;
			}

			if (inputBuffer[iReadIndex] == splitStr[compareIndex]) {
				compareIndex++;
				if (compareIndex == splitStrLen) {

					inputBuffer[iReadIndex] = 0;
					string data = inputBuffer;

					boost::regex_iterator<string::iterator> m1(data.begin(),
							data.end(), expression);
					boost::regex_iterator<string::iterator> m2;

					for (; m1 != m2; m1++) {
						fire_regex_callback(*m1, processor);
					}
					iReadIndex = 0;
					compareIndex = 0;
					continue;
				}

			} else {
				compareIndex = 0;
			}

			compareIndex++;

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
bool RegSearch::process(const boost::match_results<string::iterator>& what) {

	if (mp_processor != NULL) {

		vector<string> pa;

		for (int i1 = 0, total = what.size(); i1 < total; i1++) {

			pa.push_back(what[i1].str());

		}

		mp_processor->process(pa);
	}
	return true;
}
