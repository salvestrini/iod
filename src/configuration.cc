//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#include "config.h"

#if HAVE_REGEX_H
#include <sys/types.h>
#include <regex.h>
#endif

#include <fstream>
#include <iostream>

#include "logs.hh"
#include "utils.hh"
#include "configuration.hh"

#if HAVE_REGEX_H
#define ERROR_BUFFER_SIZE 512

std::string tostring(regex_t * regex, int errcode)
{
        ASSERT(regex != 0);
        ASSERT(errcode != 0);

        char buffer[ERROR_BUFFER_SIZE];

        size_t s = regerror(errcode, regex, buffer, ERROR_BUFFER_SIZE);
        ASSERT(s <= ERROR_BUFFER_SIZE);

        return std::string(buffer);
}
#endif

bool parse_line(const std::string &                  line,
                std::map<std::string, std::string> & inputs,
                std::map<std::string, std::string> & outputs,
                std::set<std::string> &              functions)
{
        std::string l(line);

        LDBG("Parsing line " + quote(l));

        {
                std::string::size_type comment_position(l.find_first_of("#"));
                if (comment_position != std::string::npos) {
                        LDBG("Removing comment");
                        l = l.erase(comment_position);
                        LDBG("Line without comments is " + quote(l));
                }
        }

        l = trim(l, std::string(" \t"));

        LDBG("Line without whitespaces/tabs " + quote(l));

        if (l.empty()) {
                LDBG("Line is empty, bailing out");
                return true;
        }

#if HAVE_REGEX_H
        {
                LDBG("Regexing ...");

                regex_t regex_input;
                regex_t regex_output;
                regex_t regex_function;

                int         rc;
                std::string regex;

                regex = "define[ \t]+([a-zA-Z][a-zA-Z0-9]*)[ \t]+as[ \t]+input";
                LDBG("Compiling regex " + quote(regex));
                rc = regcomp(&regex_input, regex.c_str(), REG_ICASE);
                BUG_IF(rc != 0, tostring(&regex_input, rc));
                ASSERT(rc == 0);

                regex = "define[ \t]+([a-zA-Z][a-zA-Z0-9]*)[ \t]+as[ \t]+output";
                LDBG("Compiling regex " + quote(regex));
                rc = regcomp(&regex_output, regex.c_str(), REG_ICASE);
                BUG_IF(rc != 0, tostring(&regex_output, rc));
                ASSERT(rc == 0);

                regex = "if[ \t]+\\(.*\\)[ \t]+then[ \t]+set[ \t]+(.*)[ \t]+to[ \t]+(.*)";
                LDBG("Compiling regex " + quote(regex));
                rc = regcomp(&regex_function, regex.c_str(), REG_ICASE);
                BUG_IF(rc != 0, tostring(&regex_output, rc));
                ASSERT(rc == 0);

#define REGEX_MAX_MATCHES 5

                regmatch_t matches[REGEX_MAX_MATCHES];

                if (regexec(&regex_input,
                            line.c_str(),
                            REGEX_MAX_MATCHES,
                            matches,
                            0) == 0) {
                        LDBG("Got match on input");
                }

                if (regexec(&regex_output,
                            line.c_str(),
                            REGEX_MAX_MATCHES,
                            matches,
                            0) == 0) {
                        LDBG("Got match on output");
                }

                if (regexec(&regex_function,
                            line.c_str(),
                            REGEX_MAX_MATCHES,
                            matches,
                            0) == 0) {
                        LDBG("Got match on function");
                }

                regfree(&regex_input);
                regfree(&regex_output);
                regfree(&regex_function);
        }
#endif

        (void) inputs;
        (void) outputs;
        (void) functions;

        LDBG("Line parsed successfully");
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
                if (!parse_line(line, inputs, outputs, functions))
                        return false;
        }

        LDBG("Configuration file parsing complete");

        {
                LVRB("Configuration:");

                std::string sep1("  ");
                std::string sep2("    ");

                LVRB(sep1 << "Inputs:");
                for (std::map<std::string, std::string>::const_iterator iter =
                             inputs.begin();
                     iter != inputs.end();
                     iter++)
                        LVRB(sep2 << (*iter).first);
                LVRB(sep1 << "Outputs:");
                for (std::map<std::string, std::string>::const_iterator iter =
                             outputs.begin();
                     iter != outputs.end();
                     iter++)
                        LVRB(sep2 << (*iter).first);
                LVRB(sep1 << "Functions:");
                for (std::set<std::string>::const_iterator iter =
                             functions.begin();
                     iter != functions.end();
                     iter++)
                        LVRB(sep2 << *iter);
        }

        return true;
}
