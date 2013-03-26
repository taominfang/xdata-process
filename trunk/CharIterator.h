/*
 * chariterator.h
 *
 *  Created on: Oct 3, 2012
 *      Author: minfang
 */

#ifndef CHAR_ITERATOR_H_
#define CHAR_ITERATOR_H_

#include <iostream>
#include <fstream>
#include <exception>
#include <iterator>
using namespace std;
class CharIterator: public iterator<bidirectional_iterator_tag, char> {
public:
	CharIterator(char * d, long p) :
			position(p), data(d) {

	}
	CharIterator() :
			position(0), data(NULL) {

	}

	bool operator !=(const CharIterator & other) const {
		return (data != other.data) || (position != other.position);
	}
	bool operator ==(const CharIterator & other) const {
		return (position == other.position) && (data == other.data);
	}
	bool operator >=(const CharIterator & other) const {
		return position >= other.position;
	}
	bool operator <=(const CharIterator & other) const {
		return position <= other.position;
	}
	bool operator >(const CharIterator & other) const {
		return position > other.position;
	}
	bool operator <(const CharIterator & other) const {
		return position < other.position;
	}
	CharIterator & operator ++() {
		position++;
		return *this;
	}

	CharIterator & operator --() {
		position--;
		return *this;
	}
	CharIterator & operator ++(int) {
		position++;
		return *this;
	}

	CharIterator & operator --(int) {
		position--;
		return *this;
	}

	CharIterator & operator +=(long v) {
		position += v;
		return *this;
	}
	CharIterator & operator -=(long v) {
		position -= v;
		return *this;
	}
	CharIterator operator +(long v) {
		CharIterator n(data, position + v);

		return n;
	}
	CharIterator operator -(long v) {
		CharIterator n(data, position - v);

		return n;
	}

	inline char operator *() {
		return data[position];
	}

private:
	long position;
	char * data;
};
#endif /* CHARITERATOR_H_ */
