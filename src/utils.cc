//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#include "config.h"

#include <sstream>
#include <cstdlib>
#include <list>
#include <string>

#if HAVE_EXECINFO_H
#include <execinfo.h>
#include <stdlib.h>
#endif

#include "utils.hh"
#include "logs.hh"

#define MAX_BACKTRACE_FRAMES 200

std::list<std::string> backtrace()
{
        std::list<std::string> tmp;

#if HAVE_BACKTRACE && HAVE_BACKTRACE_SYMBOLS
        void *  array[MAX_BACKTRACE_FRAMES];
        size_t  size;
        char ** strings;
        size_t  i;

        size    = backtrace(array, MAX_BACKTRACE_FRAMES);
        strings = backtrace_symbols(array, size);

        if (strings) {
                for (i = 0; i < size; i++)
                        tmp.push_back(strings[i]);

                free(strings);
        }
#else
        LWRN("Backtrace support is not available ...");
#endif

        return tmp;
}

void bug(const std::string & file,
         int                 line,
         const std::string & message)
{
        LCRT("A bug has been detected in "
             << file << ":" << line << ": " << message);

        LCRT("");
        std::list<std::string> tmp(backtrace());
        if (tmp.size() != 0) {
                LCRT("Backtrace (" << tmp.size() << " stack frames):");
                for (std::list<std::string>::const_iterator iter = tmp.begin();
                     iter != tmp.end();
                     iter++)
                        LCRT("  " << *iter);
        }
        LCRT("");

        LCRT("Please report this bug to <" << PACKAGE_BUGREPORT << ">");

        LCRT("");
        LCRT("Process is going to terminate abruptly ...");
        abort();
}

std::string quote(const std::string & s)
{
        std::stringstream ss;

        ss << "`" << s << "'";

        return ss.str();
}

std::string tostring(int n)
{
        std::stringstream ss;

        ss << n;

        return ss.str();
}

std::string trim_left(const std::string & s,
                      const std::string & t)
{
        std::string tmp(s);

        return tmp.erase(0, tmp.find_first_not_of(t));
}

std::string trim_right(const std::string & s,
                       const std::string & t)
{
        std::string tmp(s);

        return tmp.erase(tmp.find_last_not_of(t) + 1);
}

std::string trim(const std::string & s,
                 const std::string & t)
{ return trim_left(trim_right(s, t), t); }
