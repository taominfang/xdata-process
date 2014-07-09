/*
 * Verbose.h
 *
 *  Created on: Jul 9, 2014
 *      Author: mtao60
 */

#ifndef VERBOSE_H_
#define VERBOSE_H_
#include <iostream>
#include "string.h"
#include "list"
#include <stdarg.h>
using namespace std;
class Verbose {
public:
	static bool enable;
	Verbose();
	virtual ~Verbose();

	static inline void print(const char * message) {
		if (enable) {
			cerr << message;
		}
	}
	static inline void println(const char * message) {
		if (enable) {
			cerr << message << endl;
		}
	}
	static inline void printf(const char * message, ...) {
		if (enable) {
			va_list vlist;
			va_start(vlist, message);
			vdprintf(2,message,vlist);
			va_end(vlist);

		}
	}

	static inline void print(string message) {
		if (enable) {
			cerr << message;
		}
	}
	static inline void println(string message) {
		if (enable) {
			cerr << message << endl;
		}
	}
};

#endif /* VERBOSE_H_ */
