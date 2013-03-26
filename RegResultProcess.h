/*
 * RegResultProcess.h
 *
 *  Created on: Aug 23, 2012
 *      Author: minfang
 */

#ifndef REGRESULTPROCESS_H_
#define REGRESULTPROCESS_H_
#include <vector>
#include <string>
//#include <boost/regex.hpp>
using namespace std;

//typedef istream_iterator<char> IteratorType;

typedef iterator<bidirectional_iterator_tag, char> bidirectional_iterator;
class RegResultProcess {
public:

	RegResultProcess();




	virtual void process(vector<string> & data)=0;
//	bool operator()(
//			const boost::match_results<IteratorType>& what) {
//
//		list<string> o;
//		for (size_t i1 = 0; i1 < what.size(); i1++) {
//			string s(what[i1].first, what[i1].second);
//			//cout<<"get:"<<s<<endl;
//			o.push_back(s);
//		}
//		m_processor->process(o);
//		//cout<<"Total line:"<<m_result.size()<<endl;
//		return true;
//	}
	virtual ~RegResultProcess();

private:

};

#endif /* REGRESULTPROCESS_H_ */
