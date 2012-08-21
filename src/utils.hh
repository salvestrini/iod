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

#endif
