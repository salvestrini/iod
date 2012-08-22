//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#ifndef UTILS_HH
#define UTILS_HH

#include <string>

void bug(const std::string & file,
         int                 line);

#define BUG() bug(__FILE__, __LINE__)

std::string quote(const std::string & s);
std::string tostring(int n);

std::string trim_left(const std::string & s,
                      const std::string & t);
std::string trim_right(const std::string & s,
                       const std::string & t);
std::string trim(const std::string & s,
                 const std::string & t);

#endif
