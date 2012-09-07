/*
 * TripleBufferIFileStream.h
 *
 *  Created on: Aug 24, 2012
 *      Author: minfang
 */

#ifndef TRIPLEBUFFERIFILESTREAM_H_
#define TRIPLEBUFFERIFILESTREAM_H_

#define DEFAULT_BUFFER_SIZE 1024000
#define THE_NUMBER_OF_BUFFER 3

#include <iostream>
#include <fstream>
#include <exception>
#include <iterator>


using namespace std;

class TripleBufferIFileStream: public basic_ifstream<char> {

public:



	class FileUnReadyException: public exception {
		virtual const char* what() const throw () {
			return "The file is not opened !";
		}
	};
	class OutFileScope: public exception {
		virtual const char* what() const throw () {
			return "The position is out of file scope !";
		}
	};
	class SystemError: public exception {
		virtual const char* what() const throw () {
			return "The system is wrong, contact the programer !";
		}
	};

	class const_iterator: public iterator<bidirectional_iterator_tag, char> {
	public:

		const_iterator(TripleBufferIFileStream * ifs, long p) :
				position(p), istream(ifs) {

		}
		const_iterator() :
				position(0), istream(NULL) {

		}

		bool operator !=(const const_iterator & other) const {
			return position != other.position;
		}
		bool operator ==(const const_iterator & other) const {
			return position == other.position;
		}
		bool operator >=(const const_iterator & other) const {
			return position >= other.position;
		}
		bool operator <=(const const_iterator & other) const {
			return position <= other.position;
		}
		bool operator >(const const_iterator & other) const {
			return position > other.position;
		}
		bool operator <(const const_iterator & other) const {
			return position < other.position;
		}
		const_iterator & operator ++() {
			position++;
			return *this;
		}

		const_iterator & operator --() {
			position--;
			return *this;
		}
		const_iterator & operator ++(int) {
			position++;
			return *this;
		}

		const_iterator & operator --(int) {
			position--;
			return *this;
		}

		const_iterator & operator +=(long v) {
			position += v;
			return *this;
		}
		const_iterator & operator -=(long v) {
			position -= v;
			return *this;
		}
		const_iterator operator +(long v) {
			const_iterator n(istream, position + v);

			return n;
		}
		const_iterator operator -(long v) {
			const_iterator n(istream, position - v);

			return n;
		}

		inline char operator *() {
			return istream->getCharOnPosition(position);
		}

	private:
		long position;
		TripleBufferIFileStream * istream;
	};

public:
	TripleBufferIFileStream();
	TripleBufferIFileStream(const char* __s, ios_base::openmode __mode =
			ios_base::in, size_t bs = DEFAULT_BUFFER_SIZE);
	TripleBufferIFileStream(const std::string& __s, ios_base::openmode __mode =
			ios_base::in, size_t bs = DEFAULT_BUFFER_SIZE);

	virtual ~TripleBufferIFileStream();

	char getCharOnPosition(long p) {
		if (p < 0 || (unsigned long) p >= m_file_length) {
			OutFileScope ex;
			throw ex;
		}
//		seekg(p, ios::beg);
//
//		char c;
//		if (good()) {
//			read(&c, 1);
//		} else {
//			OutFileScope ex;
//			throw ex;
//		}
//
//		return c;

		if (p < m_buffer_border[m_current_buffer_index][0]
				|| p >= m_buffer_border[m_current_buffer_index][1]) {
			//hit the cache

			long startPoint = 0;

			if (m_buffer[m_current_buffer_index] == NULL) {
				// first visit this stream
				m_buffer[m_current_buffer_index] = new char[m_buffer_size];

				//

			}

			else {
				if (p < m_buffer_border[m_current_buffer_index][0]) {
					// go back

					if ((m_buffer_border[m_current_buffer_index][0] - p)
							> m_buffer_size) {
						//broken the cache rult, rebuild whole cache system
						m_current_buffer_index = 0;
					} else {
						//

						m_current_buffer_index--;
						if (m_current_buffer_index < 0) {
							m_current_buffer_index = THE_NUMBER_OF_BUFFER - 1;
						}

						if (p
								== (m_buffer_border[m_current_buffer_index][0]
										- 1)) {
							startPoint =
									m_buffer_border[m_current_buffer_index][0]
											- m_buffer_size;
						}

					}
				} else if (p >= m_buffer_border[m_current_buffer_index][1]) {
					// go head

					if ((p - m_buffer_border[m_current_buffer_index][1])
							> m_buffer_size) {
						//broken the cache rult, rebuild whole cache system
						m_current_buffer_index = 0;
					} else {
						//
						m_current_buffer_index++;
						if (m_current_buffer_index >= THE_NUMBER_OF_BUFFER) {
							m_current_buffer_index = 0;
						}

						if (p == m_buffer_border[m_current_buffer_index][1]) {
							startPoint =
									m_buffer_border[m_current_buffer_index][1];
						}

					}
				} else {

					SystemError ex;
					throw ex;

				}

				if (m_buffer[m_current_buffer_index] == NULL) {
					m_buffer[m_current_buffer_index] = new char[m_buffer_size];
				}

				else if (p >= m_buffer_border[m_current_buffer_index][0]
						&& p < m_buffer_border[m_current_buffer_index][1]) {
					return m_buffer[m_current_buffer_index][p
							- m_buffer_border[m_current_buffer_index][0]];

				}
			} // end else for  if (m_buffer[m_current_buffer_index] == NULL) {

			//calculate the border of the buffer;

			if (startPoint == 0) {

				startPoint = int(p / m_buffer_size) * m_buffer_size;

			}
			size_t length = m_file_length - startPoint;
			if (length > m_buffer_size) {
				length = m_buffer_size;
			}

			m_buffer_border[m_current_buffer_index][0] = startPoint;
			m_buffer_border[m_current_buffer_index][1] = startPoint + length;

			seekg(startPoint, ios::beg);
			read(m_buffer[m_current_buffer_index], length);

//			cout << "index:" << m_current_buffer_index << " "
//					<< m_buffer_border[m_current_buffer_index][0] << ":"
//					<< m_buffer_border[m_current_buffer_index][1] << " == "
//					<< length << endl;

		} //

		return m_buffer[m_current_buffer_index][p
				- m_buffer_border[m_current_buffer_index][0]];

	}

	const_iterator begin() {

		prepare();
		const_iterator b(this, 0);
		return b;

	}
	const_iterator end() {

		prepare();
		const_iterator b(this, m_file_length);
		return b;

	}

	long getFileLength() {
		return m_file_length;
	}

private:
	void localInit() {
		for (int i1 = 0; i1 < THE_NUMBER_OF_BUFFER; i1++) {
			m_buffer[i1] = NULL;
			m_buffer_border[i1][0] = -1;
			m_buffer_border[i1][1] = -1;
		}
		m_prepare = false;
		m_current_buffer_index = 0;
	}

	void prepare() {
		if (m_prepare) {
			return;
		}
		if (!this->is_open()) {
			FileUnReadyException ex;
			throw ex;
		}

		seekg(0, ios::end);
		m_file_length = tellg();
		seekg(0, ios::beg);

		m_prepare = true;
	}

private:

	size_t m_buffer_size;

	char * m_buffer[THE_NUMBER_OF_BUFFER];

	long m_buffer_border[THE_NUMBER_OF_BUFFER][2];

	int m_current_buffer_index;

	bool m_prepare;

	size_t m_file_length;

};

#endif /* TRIPLEBUFFERIFILESTREAM_H_ */
