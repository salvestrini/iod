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
