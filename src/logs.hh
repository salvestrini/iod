//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#ifndef LOGS_HH
#define LOGS_HH

#include <iostream>

extern const char * __logs_prefix;
extern int          __logs_level;

#define LOGS_LEVEL_MIN                  0
#define LOGS_LEVEL_MAX                  2
#define LOGS_LEVEL_DEFAULT LOGS_LEVEL_MIN

#define LOGS_PREFIX_SET(PFX) do { __logs_prefix = PFX; } while (0)
#define LOGS_LEVEL_GET()     __logs_level
#define LOGS_LEVEL_SET(LVL)  do { __logs_level = LVL;  } while (0)

#define __LOG(MSG, COND)                                                \
	do {                                                            \
	        if (COND)                                               \
	                std::cout << __logs_prefix << ": " << MSG       \
				  << std::endl;                         \
	} while (0)

#define LDBG(MSG) do { __LOG(MSG, __logs_level > 1); } while (0)
#define LVRB(MSG) do { __LOG(MSG, __logs_level > 0); } while (0)
#define LMSG(MSG) do { __LOG(MSG, true);             } while (0)
#define LWRN(MSG) do { __LOG(MSG, true);             } while (0)
#define LERR(MSG) do { __LOG(MSG, true);             } while (0)
#define LCRT(MSG) do { __LOG(MSG, true);             } while (0)

#endif
