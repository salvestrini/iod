#
# Makefile.am
#
# (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
#

ACLOCAL_AMFLAGS      = -I m4
DISTCLEANFILES       =
MAINTAINERCLEANFILES =
BUILT_SOURCES        =

SUBDIRS = src

EXTRA_DIST     =				\
	build-aux/git-version-gen		\
	build-aux/gitlog-to-changelog		\
	README

.PHONY: AUTHORS
AUTHORS:
	$(GIT) log --format="%aN <%aE>" | $(SORT) | $(UNIQ) > AUTHORS || { \
		rm -f AUTHORS ;						   \
		exit 1 ;						   \
	}
EXTRA_DIST           += AUTHORS
MAINTAINERCLEANFILES += AUTHORS
DISTCLEANFILES       += AUTHORS

.PHONY: ChangeLog
ChangeLog:
	$(srcdir)/build-aux/gitlog-to-changelog				\
		--amend=$(srcdir)/.changelog-amend > ChangeLog || {	\
		rm -f ChangeLog ;					\
		exit 1 ;						\
	}
EXTRA_DIST           +=	ChangeLog .changelog-amend
MAINTAINERCLEANFILES += ChangeLog
DISTCLEANFILES       += ChangeLog

.PHONY: NEWS
NEWS:
	$(GIT) tag -l -n1 |                                               \
	$(SORT) -V |                                                      \
	$(SED) -e 's,Version[ \\t]\+bump[ \\t]\+(\(.*\)),\1,' > NEWS || { \
	        rm -f NEWS ;                                              \
	        exit 1 ;                                                  \
	}
EXTRA_DIST           += NEWS
MAINTAINERCLEANFILES += NEWS
DISTCLEANFILES       += NEWS

$(top_srcdir)/.version:
	echo $(VERSION) > $@-t && mv $@-t $@
BUILT_SOURCES  += $(top_srcdir)/.version
EXTRA_DIST     += $(top_srcdir)/.version

dist-hook:
	echo $(VERSION) > $(distdir)/.tarball-version
