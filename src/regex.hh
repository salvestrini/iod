//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#ifndef REGEX_HH
#define REGEX_HH

#include "config.h"

#if HAVE_REGEX_H
#include <sys/types.h>
#include <regex.h>
#endif

#include <list>
#include <string>

#define REGEX_MAX_MATCHES 5

class regex {
public:
        regex(const char *);
        regex(const std::string & expression);
        virtual ~regex();

        std::list<std::string> matches(const std::string & input);

private:
        void compile(const char * expression);

        regex_t    buffer_;
        regmatch_t matches_[REGEX_MAX_MATCHES];
};

#endif
