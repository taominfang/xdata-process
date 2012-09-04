/*
 * TripleBufferIFileStream.cpp
 *
 *  Created on: Aug 24, 2012
 *      Author: minfang
 */

#include "TripleBufferIFileStream.h"

TripleBufferIFileStream::TripleBufferIFileStream() :
		basic_ifstream<char>(),m_buffer_size(DEFAULT_BUFFER_SIZE) {

	localInit();
}

TripleBufferIFileStream::TripleBufferIFileStream(const char* __s,
		ios_base::openmode __mode,size_t bs) :
		basic_ifstream<char>(__s, __mode),m_buffer_size(bs) {
	localInit();
}
TripleBufferIFileStream::TripleBufferIFileStream(const std::string& __s,
		ios_base::openmode __mode,size_t bs) :
		basic_ifstream<char>(__s.c_str(), __mode),m_buffer_size(bs)  {
	localInit();
}

TripleBufferIFileStream::~TripleBufferIFileStream() {

	for(int i1=0;i1<THE_NUMBER_OF_BUFFER;i1++){
		if(m_buffer[i1]!=NULL){
			delete [] m_buffer[i1];
		}
	}
}

