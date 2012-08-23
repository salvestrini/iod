//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#ifndef UTILS_HH
#define UTILS_HH

#include <string>

void        bug(const std::string & file,
                int                 line,
                const std::string & message);

std::string quote(const std::string & s);

#define BUG(MSG) bug(__FILE__, __LINE__, MSG)

#define _STR(X) #X

#define ASSERT(COND)                                                    \
	do {                                                            \
		if (COND)                                               \
			BUG("Assertion '" _STR(COND) "' failed");       \
	} while (0);

std::string tostring(int n);

std::string trim_left(const std::string & s,
                      const std::string & t);
std::string trim_right(const std::string & s,
                       const std::string & t);
std::string trim(const std::string & s,
                 const std::string & t);

#endif
