/*
 * RegSearch.h
 *
 *  Created on: Aug 23, 2012
 *      Author: minfang
 */

#ifndef REGSEARCH_H_
#define REGSEARCH_H_
#include <list>
#include <boost/regex.hpp>
#include "TripleBufferIFileStream.h"
#include "RegResultProcess.h"
#include <boost/scoped_ptr.hpp>

#define DEFAULT_TRIPLE_BUFFER_SIZE 102400

#define MAX_INPUT_BUFFER_SIZE 102400


class RegSearch {
public:
	RegSearch();
	virtual ~RegSearch();

	static bool fire_regex_callback(
			const boost::match_results<TripleBufferIFileStream::const_iterator>& what,RegSearch & processor);

	static bool fire_regex_callback(
			const boost::match_results<string::iterator>& what,RegSearch & processor);

	static int awk_search_reg();

	bool process(const boost::match_results<TripleBufferIFileStream::const_iterator>& what);
	bool process(const boost::match_results<string::iterator>& what);


private:

	RegResultProcess * mp_processor;


};

#endif /* REGSEARCH_H_ */
