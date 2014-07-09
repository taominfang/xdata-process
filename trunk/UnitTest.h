/*
 * UnitTest.h
 *
 *  Created on: Aug 6, 2012
 *      Author: minfang
 */

#ifndef UNITTEST_H_
#define UNITTEST_H_

#include "SystemUtil.h"
#include "FileUtil.h"
#include "SimpleContentReplace.h"
#include "Parameters.h"
#include <iostream>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <exception>

#include "TripleBufferIFileStream.h"
#include "CharIterator.h"

using namespace std;
class UnitTest {
public:
	UnitTest();
	virtual ~UnitTest();

	void runAll() {
		//runNeedSettingTest();
		runGeneralTest();
	}

	void runNeedSettingTest() {
		//those functions need manually setting some values for testing
		test_isOwnerUid();
		test_isInGroup();
		test_isFile();
	}

	void runGeneralTest() {

		cout << "test SimpleContentReplace" << endl;
		if (test_SimpleContentReplace()) {
			cout << "test result successful" << endl;
		} else {
			cout << "test result failure" << endl;
		}

		test_createStringList();

		cout << "test TripleBufferIFileStream ......";

		if (test_TripleBufferIFileStream()) {
			cout << "successful" << endl;
		} else {
			cout << "fail" << endl;
		}

		cout << " test Char iterator....." << endl;

		if (test_CharIterator()) {
			cout << "successful" << endl;
		} else {
			cout << "fail" << endl;
		}
	}

	void test_isFile() {
		cout << "test isFile";

		// echo abcd > /tmp/test1.txt

		if (FileUtil::isFile("/tmp/test1.txt", true, true)
				&& !FileUtil::isFile("/asdf/asdfas/asdf")) {

			// echo abcd > /tmp/test2.txt
			// sudo  chown nagios:nagios /tmp/test2.txt
			cout << "..... successful" << endl;
			cout << "test isFile readable, writable";

			if (FileUtil::isFile("/tmp/test2.txt", true, false)
					&& !FileUtil::isFile("/tmp/test2.txt", true, true)) {
				cout << "..... successful" << endl;
			} else {
				cout << "..... failure" << endl;
			}
		} else {
			cout << "..... failure" << endl;
		}

	}

	void test_isOwnerUid() {
		cout << "test isOwnerUid";
		//grep minfang /etc/passwd
		//minfang:x:500:3:minfang:/home/minfang:/bin/bash

		if (SystemUtil::isOwnerUid(500) && !SystemUtil::isOwnerUid(501)) {
			cout << "..... successful" << endl;
		} else {
			cout << "..... failure" << endl;
		}

	}
	void test_isInGroup() {
		cout << "test isInGroup";
		//grep minfang /etc/group
//		lp:x:7:daemon,lp,root,minfang
//		minfang:x:500:

		if (SystemUtil::isInGroup(getgid()) && !SystemUtil::isOwnerUid(2)) {
			cout << "..... successful" << endl;
		} else {
			cout << "..... failure" << endl;
		}

	}

	bool test_SimpleContentReplace() {

		SimpleContentReplace sp;
		map<string, string> testing;

		testing["abcd"] = "12345";

		const char *finName = "/tmp/SimpleFileContentReplace_in";
		const char * foutName = "/tmp/SimpleFileContentReplace_out";
		const char * fresult = "/tmp/SimpleFileContentReplace_result";

		if (!FileUtil::isFile(finName)) {
			cout << " file " << finName << " is not existent,create one"
					<< endl;
			ofstream fo(finName);

			fo << "$abcd$ abcd aa$abcd$$abcd$dd" << endl;
			fo.close();
		}
		if (!FileUtil::isFile(fresult)) {
			cout << " file " << fresult << " is not existent,create one" << endl;
			ofstream fo(fresult);

			fo << "12345 abcd aa1234512345dd" << endl;
			fo.close();
		}

		ifstream fin(finName);

		ofstream fout(foutName);

		cout << "Start replace" << endl;

		if (sp.variableReplace(fin, testing, fout)) {

			cout << "Please run diff " << foutName << " " << fresult << endl;
		} else {
			return false;
		}

		if (fin.is_open()) {
			fin.close();
		}
		if (fout.is_open()) {
			fout.close();
		}

		return true;

	}

	void test_createStringList() {
		cout << "test createStringList:" << endl;

		if (createStringList(NULL) == NULL) {

			list<string> * r = createStringList("abc1", NULL);

			if (r->begin() != r->end() && (*(r->begin())) == string("abc1")) {

				list<string> * t1 = createStringList("abc2", "sdf", NULL);
				list<string> * t2 = createStringList("abc3", NULL);

				delete t1;
				delete t2;

				cout << "..... successful" << endl;
			} else {
				cout << "..... failure" << endl;
			}

			delete r;
		} else {
			cout << "..... failure" << endl;
		}

	}

	bool test_TripleBufferIFileStream() {

		const char * fn = "/tmp/a.avi";
		TripleBufferIFileStream f1(fn);
		ifstream f2(fn, ios::binary);
		bool re = true;
		if (f1.is_open() && f2.is_open()) {

			char buff2[1024];

			long l2;
			f2.seekg(0, ios::end);
			l2 = f2.tellg();
			f2.seekg(0, ios::beg);

			long sum2 = 0;
			for (; l2 > 0;) {

				long rs = l2 > 1024 ? 1024 : l2;
				f2.read(buff2, rs);

				l2 -= rs;

				for (int i3 = 0; i3 < rs; i3++) {
					sum2 += (unsigned char) buff2[i3];
				}

			}

			f2.close();

			cout << " sum for f2 is " << sum2 << endl;

			// for begin to end
			long sum1 = 0;
			for (TripleBufferIFileStream::const_iterator b1 = f1.begin(), e1 =
					f1.end(); b1 != e1; b1++) {
				sum1 += (unsigned char) *b1;
			}

			if (sum1 != sum2) {
				cout << " test 1 from begin to end error!" << endl;
				re = false;

			}

			// from end to begin

			//cout << "test2" << endl;
			sum1 = 0;
			for (TripleBufferIFileStream::const_iterator b1 = f1.begin(), e1 =
					f1.end();;) {
				e1--;

				if (b1 <= e1) {
					sum1 += (unsigned char) *e1;
				} else {
					break;
				}
			}

			if (sum1 != sum2) {
				cout << " test 2 from end to begin error!" << endl;
				re = false;

			}

			//25016150

			TripleBufferIFileStream::const_iterator bb1 = f1.begin();
			TripleBufferIFileStream::const_iterator ee1 = f1.end();
			TripleBufferIFileStream::const_iterator mm1 = bb1 + 15016150;
			sum1 = 0;

			for (; bb1 < mm1; bb1++) {
				sum1 += (unsigned char) *bb1;
			}

			for (; mm1 < ee1; mm1++) {
				sum1 += (unsigned char) *mm1;
			}

			if (sum1 != sum2) {
				cout << " test 3 from middle error!" << endl;
				re = false;

			}

			f1.close();

		} else {
			cout << "open file fail ";
			return false;
		}

		return re;

	}

	bool test_CharIterator() {

	}

};

#endif /* UNITTEST_H_ */
