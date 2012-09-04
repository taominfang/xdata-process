/*
 * FileUtil.h
 *
 *  Created on: Aug 6, 2012
 *      Author: minfang
 */

#ifndef FILEUTIL_H_
#define FILEUTIL_H_
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "SystemUtil.h"
class FileUtil {
public:
	FileUtil();
	virtual ~FileUtil();

	static bool isFile(const char * sFilePath, bool readableTesting=false,
			bool writableTesting=false) {

		struct stat fstat;

		if (stat(sFilePath, &fstat) == -1) {
			return false;
		}

		if (!S_ISREG(fstat.st_mode) && !S_ISFIFO(fstat.st_mode)
				&& !S_ISLNK(fstat.st_mode)) {
			return false;
		}

		if (getuid() == 0) {
			//super use can read write any file

			return true;
		}

		if (readableTesting || writableTesting) {

			bool isOwner = SystemUtil::isOwnerUid(fstat.st_uid);
			bool isGroupMember = SystemUtil::isInGroup(fstat.st_gid);

			if (readableTesting) {
				bool test = false;
				if (isOwner) {
					if ((fstat.st_mode & S_IRUSR) != 0) {
						test = true;
					} else {
						// is owner and owner can not read !
						return false;
					}
				}

				if (!test && isGroupMember) {
					if ((fstat.st_mode & S_IRGRP) != 0) {
						test = true;
					} else {
						// is group member and  can not read !
						return false;
					}
				}

				if (!test) {
					if ((fstat.st_mode & S_IROTH) != 0) {
						test = true;
					} else {
						// is owner and owner can not read !
						return false;
					}
				}

				if (!test) {
					return false;
				}

			}

			if (writableTesting) {
				bool test = false;
				if (isOwner) {
					if ((fstat.st_mode & S_IWUSR) != 0) {
						test = true;
					} else {
						// is owner and owner can not read !
						return false;
					}
				}

				if (!test && isGroupMember) {
					if ((fstat.st_mode & S_IWGRP) != 0) {
						test = true;
					} else {
						// is group member and  can not read !
						return false;
					}
				}

				if (!test) {
					if ((fstat.st_mode & S_IWOTH) != 0) {
						test = true;
					} else {
						// is owner and owner can not read !
						return false;
					}
				}

				if (!test) {
					return false;
				}
			}
		}
		return true;

	}
};

#endif /* FILEUTIL_H_ */
