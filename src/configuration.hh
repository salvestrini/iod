//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <map>
#include <set>
#include <string>

bool parse_configuration(const std::string &                  filename,
                         std::map<std::string, std::string> & inputs,
                         std::map<std::string, std::string> & outputs,
                         std::set<std::string> &              functions);

#endif
