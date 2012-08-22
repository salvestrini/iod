//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#include "config.h"

#include <sstream>
#include <cstdlib>

#if HAVE_EXECINFO_H
#include <execinfo.h>
#include <stdlib.h>
#endif

#include "utils.hh"
#include "logs.hh"

#define MAX_BACKTRACE_FRAMES 200

//std::list<std::string> backtrace()
//{
//        std::list<std::string> tmp;
//
//        return tmp;
//}

void bug(const std::string & file,
         int                 line)
{
        LCRT("A bug has been detected in " << file << ":" << line);
#if HAVE_BACKTRACE && HAVE_BACKTRACE_SYMBOLS
        void *  array[MAX_BACKTRACE_FRAMES];
        size_t  size;
        char ** strings;
        size_t  i;

        size    = backtrace(array, MAX_BACKTRACE_FRAMES);
        strings = backtrace_symbols(array, size);

        if (strings) {
                LCRT("");
                LCRT("Backtrace (" << size << " stack frames):");
                for (i = 0; i < size; i++)
                        LCRT("  " << strings[i]);
                LCRT("");

                free(strings);
        } else
                LERR("Cannot retrieve backtrace ...");
#else
        LCRT("Backtrace unavailable (missing support)");
#endif

        LCRT("Please report this bug to <" << PACKAGE_BUGREPORT << ">");

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
