#
# Makefile.am
#
# (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
#

bin_PROGRAMS = iod

EXTRA_DIST =					\
	iod.conf

iod_SOURCES =					\
	logs.cc          logs.hh		\
	utils.cc         utils.hh		\
	regex.cc         regex.hh		\
	configuration.cc configuration.hh	\
	iod.cc

iod_CPPFLAGS =					\
	-Wall -Werror -Wextra -Wundef		\
	-DSYSCONFDIR=\"${sysconfdir}\"

iod_CXXFLAGS =
