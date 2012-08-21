//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#include "config.h"

#include <cstdlib>
#include <sstream>
#include <cassert>

#if HAVE_GETOPT_H
#include <getopt.h>
#endif

#include "logs.hh"
#include "utils.hh"

#define PROGRAM_NAME               "iod"
#define DEFAULT_CONFIGURATION_FILE SYSCONFDIR "/" PROGRAM_NAME

std::string configuration_file = std::string(DEFAULT_CONFIGURATION_FILE);

std::string hint(const std::string & executable,
                 const std::string & message)
{
        std::stringstream ss;

        ss << PROGRAM_NAME << ": " << message << std::endl;
        ss << "Try `" << executable << " --help' for "
           << "more information." << std::endl;

        return ss.str();
}

std::string version()
{
        std::stringstream ss;

        ss << PROGRAM_NAME << " "
           << "(" << PACKAGE_NAME << " " << PACKAGE_VERSION << ")";

        return ss.str();
}

std::string help(const std::string & executable)
{
        std::stringstream ss;
        std::string       sep("    ");

        ss << "Usage: " << executable << " [OPTION] ..."
           << std::endl;
        ss << std::endl;

        ss << "  -h, --help         " + sep + "print this help, then exit"
           << std::endl;
        ss << "  -v, --version      " + sep + "print version, then exit"
           << std::endl;
        ss << "  -q, --quiet        " + sep + "decrease logs verbosity"
           << std::endl;
        ss << "  -l, --lousy        " + sep + "increase logs verbosity"
           << std::endl;
        ss << "  -c, --configuration" + sep + "set configuration file"
           << std::endl
           << "                     " + sep + "(default " + quote(configuration_file) + ")"
           << std::endl;

        ss << std::endl;
        ss << "Report bugs to <" << PACKAGE_BUGREPORT << ">"
           << std::endl;

        return ss.str();
}

void terminate_handler()
{
        BUG();
}

bool parse_options(int argc, char * argv[])
{
        LDBG("Parsing command line options ...");

#if HAVE_GETOPT_H
        struct option long_options[] = {
                { "quiet",          no_argument, 0, 'q' },
                { "lousy",          no_argument, 0, 'l' },
                { "help",           no_argument, 0, 'h' },
                { "version",        no_argument, 0, 'v' },

                { "configuration",  no_argument, 0, 'c' },

                { 0,                0,           0, 0   }
        };

        opterr = 0;
        int opt;
        while ((opt = getopt_long(argc, argv,
                                  "qlhv",
                                  long_options, 0)) != -1) {
                switch (opt) {
                        case 'c':
                                assert(optarg != 0);
                                configuration_file = std::string(optarg);
                                break;
                        case 'q':
                                LOGS_SET_LEVEL(LOGS_GET_LEVEL() - 1);
                                break;
                        case 'l':
                                LOGS_SET_LEVEL(LOGS_GET_LEVEL() + 1);
                                break;
                        case 'h':
                                std::cout << help(argv[0]);
                                return true;
                        case 'v':
                                std::cout << version() << std::endl;
                                return true;
                        default:
                                assert(argv[optind - 1] != 0);
                                std::string err =
                                        std::string("Unknown argument ") +
                                        quote(argv[optind - 1]);
                                std::cerr << hint(argv[0], err);
                                return false;
                }
        }

        if (optind < argc) {
                LWRN("Discarding unhandled option(s) ...");
        }
#endif

        LDBG("Options parsing complete");
        return true;
}

bool parse_configuration(const std::string & filename)
{
        LDBG("Parsing configuration file " + quote(filename));

        return false;
}

bool core(int argc, char * argv[])
{
        if (!parse_options(argc, argv))
                return false;

        if (!parse_configuration(configuration_file))
                return false;

        LVRB(PROGRAM_NAME << " " << PACKAGE_VERSION << " starting ...");
        LVRB("Stopped!");

        return true;
}

int main(int argc, char * argv[])
{
        LOGS_SET_PREFIX(PROGRAM_NAME);
        // LOGS_SET_LEVEL(100);

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
