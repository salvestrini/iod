//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#include <cstdlib>

#include "logs.hh"

#define PROGRAM_NAME "iod"

bool core(int argc, char * argv[])
{
        (void) argc;
        (void) argv;

        return true;
}

int main(int argc, char * argv[])
{
        LOG_SET_PREFIX(PROGRAM_NAME);
        LOG_SET_LEVEL(100);

        LDBG("Starting ...");

        int retval;

        try {
                retval = core(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
        } catch (...) {
                retval = EXIT_FAILURE;
        }

        LDBG("Stopped");

        return retval;
}
