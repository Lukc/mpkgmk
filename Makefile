PACKAGE = 'mpkgmk'
VERSION = '0.0.1'

PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
LIBDIR := $(PREFIX)/lib

CFLAGS := -O0 -g -Wall -Wextra -D_BSD_SOURCE -Wno-unused-parameter
LDFLAGS := 

Q := @

all:  subdirs

subdirs:
	$(Q)for i in src; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)"); done

install: subdirs.install

subdirs.install:
	$(Q)for i in src; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" install); done

clean:
	$(Q)for i in src; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" clean); done

distclean: clean
	$(Q)for i in src; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" distclean); done

dist: dist-gz dist-xz dist-bz2
	$(Q)rm -- $(PACKAGE)-$(VERSION)

distdir:
	$(Q)rm -rf -- $(PACKAGE)-$(VERSION)
	$(Q)ln -s -- . $(PACKAGE)-$(VERSION)

dist-gz: $(PACKAGE)-$(VERSION).tar.gz
$(PACKAGE)-$(VERSION).tar.gz: distdir
	@echo '  [TAR]   $(PACKAGE)-$(VERSION).tar.gz'
	$(Q)tar czf $(PACKAGE)-$(VERSION).tar.gz \
		$(PACKAGE)-$(VERSION)/Makefile \
		$(PACKAGE)-$(VERSION)/project.zsh \
		$(PACKAGE)-$(VERSION)/package.yaml \
		$(PACKAGE)-$(VERSION)/src/Makefile \
		$(PACKAGE)-$(VERSION)/src/project.zsh \
		$(PACKAGE)-$(VERSION)/src/assemble.c \
		$(PACKAGE)-$(VERSION)/src/build.c \
		$(PACKAGE)-$(VERSION)/src/configuration.c \
		$(PACKAGE)-$(VERSION)/src/download.c \
		$(PACKAGE)-$(VERSION)/src/extraction.c \
		$(PACKAGE)-$(VERSION)/src/main.c \
		$(PACKAGE)-$(VERSION)/src/modules.c \
		$(PACKAGE)-$(VERSION)/src/recipe.c \
		$(PACKAGE)-$(VERSION)/src/ui.c \
		$(PACKAGE)-$(VERSION)/src/workdir.c \
		$(PACKAGE)-$(VERSION)/src/error.h \
		$(PACKAGE)-$(VERSION)/src/assemble.h \
		$(PACKAGE)-$(VERSION)/src/build.h \
		$(PACKAGE)-$(VERSION)/src/configuration.h \
		$(PACKAGE)-$(VERSION)/src/download.h \
		$(PACKAGE)-$(VERSION)/src/extraction.h \
		$(PACKAGE)-$(VERSION)/src/modules.h \
		$(PACKAGE)-$(VERSION)/src/recipe.h \
		$(PACKAGE)-$(VERSION)/src/ui.h \
		$(PACKAGE)-$(VERSION)/src/workdir.h \
		$(PACKAGE)-$(VERSION)/src/modules/makefile \
		$(PACKAGE)-$(VERSION)/src/modules/project.zsh \
		$(PACKAGE)-$(VERSION)/src/modules/curl.c \
		$(PACKAGE)-$(VERSION)/src/modules/archive.c \
		$(PACKAGE)-$(VERSION)/src/modules/test.c

dist-xz: $(PACKAGE)-$(VERSION).tar.xz
$(PACKAGE)-$(VERSION).tar.xz: distdir
	@echo '  [TAR]   $(PACKAGE)-$(VERSION).tar.xz'
	$(Q)tar cJf $(PACKAGE)-$(VERSION).tar.xz \
		$(PACKAGE)-$(VERSION)/Makefile \
		$(PACKAGE)-$(VERSION)/project.zsh \
		$(PACKAGE)-$(VERSION)/package.yaml \
		$(PACKAGE)-$(VERSION)/src/Makefile \
		$(PACKAGE)-$(VERSION)/src/project.zsh \
		$(PACKAGE)-$(VERSION)/src/assemble.c \
		$(PACKAGE)-$(VERSION)/src/build.c \
		$(PACKAGE)-$(VERSION)/src/configuration.c \
		$(PACKAGE)-$(VERSION)/src/download.c \
		$(PACKAGE)-$(VERSION)/src/extraction.c \
		$(PACKAGE)-$(VERSION)/src/main.c \
		$(PACKAGE)-$(VERSION)/src/modules.c \
		$(PACKAGE)-$(VERSION)/src/recipe.c \
		$(PACKAGE)-$(VERSION)/src/ui.c \
		$(PACKAGE)-$(VERSION)/src/workdir.c \
		$(PACKAGE)-$(VERSION)/src/error.h \
		$(PACKAGE)-$(VERSION)/src/assemble.h \
		$(PACKAGE)-$(VERSION)/src/build.h \
		$(PACKAGE)-$(VERSION)/src/configuration.h \
		$(PACKAGE)-$(VERSION)/src/download.h \
		$(PACKAGE)-$(VERSION)/src/extraction.h \
		$(PACKAGE)-$(VERSION)/src/modules.h \
		$(PACKAGE)-$(VERSION)/src/recipe.h \
		$(PACKAGE)-$(VERSION)/src/ui.h \
		$(PACKAGE)-$(VERSION)/src/workdir.h \
		$(PACKAGE)-$(VERSION)/src/modules/makefile \
		$(PACKAGE)-$(VERSION)/src/modules/project.zsh \
		$(PACKAGE)-$(VERSION)/src/modules/curl.c \
		$(PACKAGE)-$(VERSION)/src/modules/archive.c \
		$(PACKAGE)-$(VERSION)/src/modules/test.c

dist-bz2: $(PACKAGE)-$(VERSION).tar.bz2
$(PACKAGE)-$(VERSION).tar.bz2: distdir
	@echo '  [TAR]   $(PACKAGE)-$(VERSION).tar.bz2'
	$(Q)tar cjf $(PACKAGE)-$(VERSION).tar.bz2 \
		$(PACKAGE)-$(VERSION)/Makefile \
		$(PACKAGE)-$(VERSION)/project.zsh \
		$(PACKAGE)-$(VERSION)/package.yaml \
		$(PACKAGE)-$(VERSION)/src/Makefile \
		$(PACKAGE)-$(VERSION)/src/project.zsh \
		$(PACKAGE)-$(VERSION)/src/assemble.c \
		$(PACKAGE)-$(VERSION)/src/build.c \
		$(PACKAGE)-$(VERSION)/src/configuration.c \
		$(PACKAGE)-$(VERSION)/src/download.c \
		$(PACKAGE)-$(VERSION)/src/extraction.c \
		$(PACKAGE)-$(VERSION)/src/main.c \
		$(PACKAGE)-$(VERSION)/src/modules.c \
		$(PACKAGE)-$(VERSION)/src/recipe.c \
		$(PACKAGE)-$(VERSION)/src/ui.c \
		$(PACKAGE)-$(VERSION)/src/workdir.c \
		$(PACKAGE)-$(VERSION)/src/error.h \
		$(PACKAGE)-$(VERSION)/src/assemble.h \
		$(PACKAGE)-$(VERSION)/src/build.h \
		$(PACKAGE)-$(VERSION)/src/configuration.h \
		$(PACKAGE)-$(VERSION)/src/download.h \
		$(PACKAGE)-$(VERSION)/src/extraction.h \
		$(PACKAGE)-$(VERSION)/src/modules.h \
		$(PACKAGE)-$(VERSION)/src/recipe.h \
		$(PACKAGE)-$(VERSION)/src/ui.h \
		$(PACKAGE)-$(VERSION)/src/workdir.h \
		$(PACKAGE)-$(VERSION)/src/modules/makefile \
		$(PACKAGE)-$(VERSION)/src/modules/project.zsh \
		$(PACKAGE)-$(VERSION)/src/modules/curl.c \
		$(PACKAGE)-$(VERSION)/src/modules/archive.c \
		$(PACKAGE)-$(VERSION)/src/modules/test.c

.PHONY: all subdirs clean distclean dist install uninstall

