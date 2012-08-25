//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <set>
#include <string>

bool parse_configuration(const std::string &     filename,
                         std::set<std::string> & inputs,
                         std::set<std::string> & outputs,
                         std::set<std::string> & functions);

#endif
