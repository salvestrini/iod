//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#include "config.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <map>
#include <set>

#if HAVE_GETOPT_H
#include <getopt.h>
#endif

#include "logs.hh"
#include "utils.hh"

#define PROGRAM_NAME               "iod"
#define DEFAULT_CONFIGURATION_FILE SYSCONFDIR "/" PROGRAM_NAME ".conf"

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

        ss << "  -h, --help         " + sep
           << "print this help, then exit"
           << std::endl;
        ss << "  -v, --version      " + sep
           << "print version, then exit"
           << std::endl;
        ss << "  -q, --quiet        " + sep
           << "decrease logs verbosity"
           << std::endl;
        ss << "  -l, --lousy        " + sep
           << "increase logs verbosity"
           << std::endl;
        ss << "  -c, --configuration" + sep
           << "set configuration file"
           << std::endl
           << "                     " + sep
           << "(default " + quote(configuration_file) + ")"
           << std::endl;

        ss << std::endl;
        ss << "Report bugs to <" << PACKAGE_BUGREPORT << ">"
           << std::endl;

        return ss.str();
}

void terminate_handler()
{
        BUG("Called terminate_handler() ...");
}

bool parse_options(int argc, char * argv[])
{
        LVRB("Parsing command line options ...");

#if HAVE_GETOPT_H
        struct option long_options[] = {
                { "help",           no_argument,       0, 'h' },
                { "version",        no_argument,       0, 'v' },

                { "quiet",          no_argument,       0, 'q' },
                { "lousy",          no_argument,       0, 'l' },
                { "configuration",  required_argument, 0, 'c' },

                { 0,                0,                 0, 0   }
        };

        opterr = 0;
        int opt;
        while ((opt = getopt_long(argc, argv,
                                  "qlc:hv",
                                  long_options, 0)) != -1) {
                switch (opt) {
                        case 'c':
                                ASSERT(optarg == 0);
                                configuration_file = std::string(optarg);
                                break;
                        case 'q':
                                LOGS_LEVEL_SET(LOGS_LEVEL_GET() - 1);
                                break;
                        case 'l':
                                LOGS_LEVEL_SET(LOGS_LEVEL_GET() + 1);
                                break;
                        case 'h':
                                std::cout << help(argv[0]);
                                return true; // XXX FIXME: It doesn't halt
                        case 'v':
                                std::cout << version() << std::endl;
                                return true; // XXX FIXME: It doesn't halt
                        default:
                                ASSERT(argv[optind - 1] != 0);
                                std::string err =
                                        std::string("Unknown argument ") +
                                        quote(argv[optind - 1]);
                                std::cerr << hint(argv[0], err);
                                return false;
                }
        }

        if (optind < argc) {
                std::string tmp;
                for (int i = optind; i < argc; i++)
                        tmp = tmp + argv[i] + ((i != (argc - 1)) ? " " : "");
                LWRN("Discarding unhandled option(s) " + quote(tmp));
        }
#endif

        LDBG("Options parsing complete");
        return true;
}

bool parse_line(const std::string & l)
{
        std::string line(l);

        LDBG("Parsing line " + quote(line));

        line = line.erase(line.find_first_of("#"));

        LDBG("Line without comments is " + quote(line));

        line = trim(line, std::string(" \t"));

        LDBG("Line without whitespaces/tabs " + quote(line));

        if (line.empty())
                return true;

        return true;
}

bool parse_configuration(const std::string &                  filename,
                         std::map<std::string, std::string> & inputs,
                         std::map<std::string, std::string> & outputs,
                         std::set<std::string> &              functions)
{
        LVRB("Parsing configuration file " + quote(filename));

        std::ifstream ifs;
        ifs.open(filename.c_str());
        if (!ifs) {
                LERR("Cannot open file " + quote(filename) + " for reading");
                return false;
        }

        while (!ifs.eof()) {
                std::string line;

                std::getline(ifs, line);
                if (!parse_line(line))
                        return false;
        }

        LDBG("Inputs:");
        (void) inputs;

        LDBG("Outputs:");
        (void) outputs;

        LDBG("Functions:");
        (void) functions;

        LDBG("Configuration file parsing complete");

        return true;
}

bool core(int argc, char * argv[])
{
        LVRB(PROGRAM_NAME << " " << PACKAGE_VERSION << " starting ...");

        if (!parse_options(argc, argv))
                return false;

        std::map<std::string, std::string> inputs;
        std::map<std::string, std::string> outputs;
        std::set<std::string>              functions;

        if (!parse_configuration(configuration_file,
                                 inputs,
                                 outputs,
                                 functions))
                return false;

        if (inputs.size() == 0) {
                LERR("No inputs defined");
                return false;
        }

        if (outputs.size() == 0) {
                LERR("No outputs defined");
                return false;
        }

        if (functions.size() == 0) {
                LERR("No functions defined");
                return false;
        }

        LVRB(PROGRAM_NAME << " " << PACKAGE_VERSION << " started");

        LVRB("Stopped!");

        return true;
}

int main(int argc, char * argv[])
{
        LOGS_PREFIX_SET(PROGRAM_NAME);
        LOGS_LEVEL_SET(LOGS_LEVEL_DEFAULT);

        LDBG("Starting ...");

        std::set_terminate(terminate_handler);

        int retval;
        try {
                retval = core(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
        } catch (...) {
                retval = EXIT_FAILURE;
        }

        LDBG("Stopped");
        if (retval != EXIT_SUCCESS)
                LDBG("Exiting with error code " + tostring(EXIT_SUCCESS));

        return retval;
}
