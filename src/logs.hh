//
// (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
//

#ifndef LOGS_HH
#define LOGS_HH

#include <iostream>

extern const char * __logs_prefix;
extern unsigned int __logs_level;

#define LOG_SET_PREFIX(PFX) do { __logs_prefix = PFX; } while (0)
#define LOG_SET_LEVEL(LVL)  do { __logs_level  = LVL; } while (0)

#define __LOG(MSG, COND)                                                \
	do {                                                            \
	        if (COND)                                               \
	                std::cout << __logs_prefix << ": " << MSG       \
				  << std::endl;                         \
	} while (0)

#define LDBG(MSG) do { __LOG(MSG, (__logs_level > 2)); } while (0)
#define LVRB(MSG) do { __LOG(MSG, (__logs_level > 1)); } while (0)
#define LMSG(MSG) do { __LOG(MSG, true);               } while (0)
#define LWRN(MSG) do { __LOG(MSG, true);               } while (0)
#define LERR(MSG) do { __LOG(MSG, true);               } while (0)
#define LCRT(MSG) do { __LOG(MSG, true);               } while (0)

#endif
