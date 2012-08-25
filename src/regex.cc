//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#include "logs.hh"
#include "utils.hh"
#include "regex.hh"

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

regex::regex(const std::string & expression)
{ compile(expression.c_str()); }

regex::regex(const char * expression)
{ compile(expression); }

regex::~regex()
{ regfree(&buffer_); }

void regex::compile(const char * expression)
{
        ASSERT(expression != 0);

        LDBG("Compiling regex " << quote(expression));

        int rc = regcomp(&buffer_,
                         expression,
                         REG_ICASE | REG_EXTENDED | REG_NEWLINE);

        BUG_IF(rc != 0, tostring(&buffer_, rc));
        ASSERT(rc == 0);
}

std::vector<std::string> regex::matches(const std::string & input)
{
        LDBG("Matching " << quote(input) << " against regex buffer");

        std::vector<std::string> tmp;

        if (regexec(&buffer_,
                    input.c_str(),
                    REGEX_MAX_MATCHES,
                    matches_,
                    0) == 0) {
                LDBG("Got matches:");
                for (size_t i = 0; i < REGEX_MAX_MATCHES; i++) {
                        std::string s(input.c_str() + matches_[i].rm_so,
                                      (matches_[i].rm_eo - matches_[i].rm_so));
                        if (matches_[i].rm_so != -1) {
                                LDBG("  "   << tostring(i) << "  "
                                     "so="  << tostring(matches_[i].rm_so) <<
                                     ", "   <<
                                     "eo="  << tostring(matches_[i].rm_eo) <<
                                     ", "   <<
                                     "str=" << quote(s));
                                tmp.push_back(s);
                        }
                }
        } else {
                LDBG("No match!");
        }

        return tmp;
}
