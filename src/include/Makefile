PACKAGE = 'mpkgmk'
VERSION = '0.0.1'

PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
LIBDIR := $(PREFIX)/lib
SHAREDIR := $(PREFIX)/share
INCLUDEDIR := $(PREFIX)/include

CFLAGS := -O0 -g -Wall -Wextra -D_BSD_SOURCE -Wno-unused-parameter
LDFLAGS := 

Q := @

all:  mpkgmk.h mpkgmk_private.h

mpkgmk.h:
	@echo '  [  ]    mpkgmk.h'

mpkgmk.h.install: mpkgmk.h
	@echo '  [IN]    $(INCLUDEDIR)/mpkgmk.h'
	$(Q)install -m0755 mpkgmk.h $(DESTDIR)$(INCLUDEDIR)/mpkgmk.h

mpkgmk.h.clean:

mpkgmk.h.uninstall:
	@echo '  [RM]    $(INCLUDEDIR)/mpkgmk.h'
	$(Q)rm -f '$(DESTDIR)$(INCLUDEDIR)/mpkgmk.h'

mpkgmk_private.h:
	@echo '  [  ]    mpkgmk_private.h'

mpkgmk_private.h.install: mpkgmk_private.h
	@echo '  [IN]    $(INCLUDEDIR)/mpkgmk_private.h'
	$(Q)install -m0755 mpkgmk_private.h $(DESTDIR)$(INCLUDEDIR)/mpkgmk_private.h

mpkgmk_private.h.clean:

mpkgmk_private.h.uninstall:
	@echo '  [RM]    $(INCLUDEDIR)/mpkgmk_private.h'
	$(Q)rm -f '$(DESTDIR)$(INCLUDEDIR)/mpkgmk_private.h'

$(DESTDIR)$(PREFIX):
	@echo '  [DIR]   $(PREFIX)'
	$(Q)mkdir -p $(DESTDIR)$(PREFIX)
$(DESTDIR)$(BINDIR):
	@echo '  [DIR]   $(BINDIR)'
	$(Q)mkdir -p $(DESTDIR)$(BINDIR)
$(DESTDIR)$(LIBDIR):
	@echo '  [DIR]   $(LIBDIR)'
	$(Q)mkdir -p $(DESTDIR)$(LIBDIR)
$(DESTDIR)$(SHAREDIR):
	@echo '  [DIR]   $(SHAREDIR)'
	$(Q)mkdir -p $(DESTDIR)$(SHAREDIR)
$(DESTDIR)$(INCLUDEDIR):
	@echo '  [DIR]   $(INCLUDEDIR)'
	$(Q)mkdir -p $(DESTDIR)$(INCLUDEDIR)
install: subdirs.install mpkgmk.h.install mpkgmk_private.h.install

subdirs.install:
	$(Q)for i in ; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" INCLUDEDIR="$(INCLUDEDIR)" install); done

uninstall: subdirs.uninstall mpkgmk.h.uninstall mpkgmk_private.h.uninstall

subdirs.uninstall:
	$(Q)for i in ; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" INCLUDEDIR="$(INCLUDEDIR)" uninstall); done

clean: mpkgmk.h.clean mpkgmk_private.h.clean

distclean: clean

.PHONY: all subdirs clean distclean dist install uninstall

