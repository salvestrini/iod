//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#include "config.h"

#include <cstdlib>
#include <sstream>

#include <getopt.h>

#include "logs.hh"
#include "utils.hh"

#define PROGRAM_NAME "iod"

std::string hint(const std::string & message)
{
        std::stringstream ss;

        ss << PROGRAM_NAME << ": " << message << std::endl;
        ss << "Try `" << PROGRAM_NAME << " --help' for "
           << "more information." << std::endl;

        return ss.str();
}

std::string version()
{
        std::stringstream ss;

        ss << PACKAGE_NAME << " " << PACKAGE_VERSION;

        return ss.str();
}

std::string help()
{
        std::stringstream ss;

        ss << "Usage: " << PROGRAM_NAME << " [OPTION] ..."
           << std::endl;
        ss << std::endl;

        ss << std::endl;
        ss << "Report bugs to <" << PACKAGE_BUGREPORT << ">"
           << std::endl;

        return ss.str();
}

void terminate_handler()
{
        LCRT("A call to terminate() has been performed ...");
        BUG();
}

bool parse_options(int argc, char * argv[])
{
        (void) argc;
        (void) argv;

        return true;
}

bool core(int argc, char * argv[])
{
        return parse_options(argc, argv);
}

int main(int argc, char * argv[])
{
        LOG_SET_PREFIX(PROGRAM_NAME);
        LOG_SET_LEVEL(100);

        LDBG("Starting ...");

        std::set_terminate(terminate_handler);

        int retval;
        try {
                retval = core(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
        } catch (...) {
                retval = EXIT_FAILURE;
        }

        LDBG("Stopped");

        return retval;
}
