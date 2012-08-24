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

#define _STR(X) #X

#define BUG(MSG) \
	do { bug(__FILE__, __LINE__, MSG); } while (0)
#define BUG_IF(COND, MSG) \
	do { if (COND) bug(__FILE__, __LINE__, MSG); } while (0)

#define ASSERT(COND)                                                    \
	do {                                                            \
                if (!(COND))                                            \
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
