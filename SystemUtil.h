/*
 * SystemUtil.h
 *
 *  Created on: Aug 6, 2012
 *      Author: minfang
 */

#ifndef SYSTEMUTIL_H_
#define SYSTEMUTIL_H_
#include <unistd.h>
#include <sys/types.h>
#include <boost/scoped_array.hpp>
using namespace boost;
class SystemUtil {
public:
	SystemUtil();
	virtual ~SystemUtil();

	static inline bool isOwnerUid(uid_t uid) {
		return uid == getuid();
	}

	static bool isInGroup(gid_t gid) {
		int ngroups = getgroups(0, NULL);
		scoped_array<gid_t> groups (new gid_t[ngroups]);


		int val = getgroups(ngroups, groups.get());
		bool re = false;
		if (val >= 0) {

			for (int i1 = 0; i1 < ngroups; i1++) {
				if (gid == groups[i1]) {
					re = true;
					break;
				}
			}
		}


		return re;
	}
};

#endif /* SYSTEMUTIL_H_ */
