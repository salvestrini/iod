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

#include <vector>
#include <string>

class regex {
public:
        regex(const char *);
        regex(const std::string & expression);
        virtual ~regex();

        std::vector<std::string> matches(const std::string & input,
                                         size_t              mcount);

private:
        void compile(const char * expression);

        regex_t    buffer_;
};

#endif
