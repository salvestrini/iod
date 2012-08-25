//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#include "config.h"

#include <fstream>
#include <iostream>

#include "logs.hh"
#include "utils.hh"
#include "configuration.hh"
#include "regex.hh"

std::string clean_line(const std::string & line)
{
        std::string l(line);

        LDBG("Cleaning line " + quote(l));

        std::string::size_type comment_position(l.find_first_of("#"));
        if (comment_position != std::string::npos) {
                LDBG("Removing comment");
                l = l.erase(comment_position);
                LDBG("Line without comments is " + quote(l));
        }

        l = trim(l, std::string(" \t"));

        LDBG("Cleaned line is " + quote(l));

        return l;
}

bool parse_configuration(const std::string &     filename,
                         std::set<std::string> & inputs,
                         std::set<std::string> & outputs,
                         std::set<std::string> & functions)
{
        LVRB("Parsing configuration file " + quote(filename));

        std::ifstream ifs;
        ifs.open(filename.c_str());
        if (!ifs) {
                LERR("Cannot open file " + quote(filename) + " for reading");
                return false;
        }

        regex regex_input("^[ \t]*define[ \t]+([a-zA-Z_][a-zA-Z0-9_]*)[ \t]+as[ \t]+input[ \t]*$");
        regex regex_output("^[ \t]*define[ \t]+([a-zA-Z_][a-zA-Z0-9_]*)[ \t]+as[ \t]+output[ \t]*$");
        regex regex_function("^[ \t]*if[ \t]+\\((.*)\\)[ \t]+then[ \t]+set[ \t]+(.*)[ \t]+to[ \t]+(.*)[ \t]*$");

        bool error = false;
        while (!ifs.eof() && !error) {
                std::string line;

                std::getline(ifs, line);
                if (line.empty())
                        continue;

                line = clean_line(line);
                if (line.empty()) {
                        LDBG("Line is empty, bailing out");
                        continue;
                }

                std::vector<std::string> matches;

                matches = regex_input.matches(line);
                if (!matches.empty()) {
                        ASSERT(matches.size() == 2);

                        std::string input = matches.at(1);

                        if (inputs.find(input) != inputs.end()) {
                                LERR("Input "     <<
                                     quote(input) <<
                                     " already defined");
                                return false;
                        }

                        inputs.insert(input);
                        continue;
                }

                matches = regex_output.matches(line);
                if (!matches.empty()) {
                        ASSERT(matches.size() == 2);

                        std::string output = matches.at(1);

                        if (outputs.find(output) != outputs.end()) {
                                LERR("Output "     <<
                                     quote(output) <<
                                     " already defined");
                                return false;
                        }

                        outputs.insert(output);
                        continue;
                }

                matches = regex_function.matches(line);
                if (!matches.empty()) {
                        ASSERT(matches.size() == 4);

                        std::string function = matches.at(1);
#if 0
                        if (functions.find(function) != functions.end()) {
                                LERR("Function "     <<
                                     quote(function) <<
                                     " already defined");
                                return false;
                        }
#endif
                        functions.insert(function);
                        continue;
                }

                LERR("Unknown line " << quote(line));
                error = true;
        }

        if (error)
                return false;

        LDBG("Configuration file parsing complete");

        {
                LVRB("Configuration:");

                std::string sep1("  ");
                std::string sep2("    ");

                LVRB(sep1 << "Inputs:");
                for (std::set<std::string>::const_iterator iter =
                             inputs.begin();
                     iter != inputs.end();
                     iter++)
                        LVRB(sep2 << *iter);
                LVRB(sep1 << "Outputs:");
                for (std::set<std::string>::const_iterator iter =
                             outputs.begin();
                     iter != outputs.end();
                     iter++)
                        LVRB(sep2 << *iter);
                LVRB(sep1 << "Functions:");
                for (std::set<std::string>::const_iterator iter =
                             functions.begin();
                     iter != functions.end();
                     iter++)
                        LVRB(sep2 << *iter);
        }

        return true;
}
