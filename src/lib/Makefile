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

all:  libmpkgmk

libmpkgmk: libmpkgmk.so

libmpkgmk.so: shell.o ui.o 
	@echo '  [LD]    libmpkgmk.so'
	$(Q)$(CC) -o libmpkgmk.so -fPIC -shared $(CFLAGS) $(LDFLAGS)  shell.o ui.o


shell.o: shell.c 
	@echo '  [CC]    shell.o'
	$(Q)$(CC) -fPIC $(CFLAGS)  -c shell.c

shell.o.clean:
	@echo '  [RM]    shell.o'
	$(Q)rm -f shell.o

ui.o: ui.c 
	@echo '  [CC]    ui.o'
	$(Q)$(CC) -fPIC $(CFLAGS)  -c ui.c

ui.o.clean:
	@echo '  [RM]    ui.o'
	$(Q)rm -f ui.o

libmpkgmk.install:  libmpkgmk.so.0.0.install libmpkgmk.so.0.install libmpkgmk.so.install

libmpkgmk.so.0.0.1.install: libmpkgmk.so $(DESTDIR)$(LIBDIR)
	@echo '  [IN]    $(LIBDIR)/libmpkgmk.so.0.0.1'
	$(Q)install -m755 libmpkgmk.so $(DESTDIR)$(LIBDIR)/libmpkgmk.so.0.0.1

libmpkgmk.so.0.0.install: libmpkgmk.so.0.0.1.install
	@echo '  [LN]    $(LIBDIR)/libmpkgmk.so.0.0'
	$(Q)ln -sf '$(LIBDIR)/libmpkgmk.so.0.0.1' '$(DESTDIR)/$(LIBDIR)/libmpkgmk.so.0.0'

libmpkgmk.so.0.install: libmpkgmk.so.0.0.1.install
	@echo '  [LN]    $(LIBDIR)/libmpkgmk.so.0'
	$(Q)ln -sf '$(LIBDIR)/libmpkgmk.so.0.0.1' '$(DESTDIR)/$(LIBDIR)/libmpkgmk.so.0'

libmpkgmk.so.install: libmpkgmk.so.0.0.1.install
	@echo '  [LN]    $(LIBDIR)/libmpkgmk.so'
	$(Q)ln -sf '$(LIBDIR)/libmpkgmk.so.0.0.1' '$(DESTDIR)/$(LIBDIR)/libmpkgmk.so'

libmpkgmk.clean:
	@echo '  [RM]    libmpkgmk'
	$(Q)rm -f libmpkgmk

libmpkgmk.uninstall:  libmpkgmk.so.uninstall libmpkgmk.so.0.uninstall libmpkgmk.so.0.0.uninstall libmpkgmk.so.0.0.1.uninstall

libmpkgmk.so.uninstall:
	@echo '  [RM]    $(LIBDIR)/libmpkgmk.so'
	$(Q)rm -f '$(DESTDIR)$(LIBDIR)/libmpkgmk.so'

libmpkgmk.so.0.uninstall:
	@echo '  [RM]    $(LIBDIR)/libmpkgmk.so.0'
	$(Q)rm -f '$(DESTDIR)$(LIBDIR)/libmpkgmk.so.0'

libmpkgmk.so.0.0.uninstall:
	@echo '  [RM]    $(LIBDIR)/libmpkgmk.so.0.0'
	$(Q)rm -f '$(DESTDIR)$(LIBDIR)/libmpkgmk.so.0.0'

libmpkgmk.so.0.0.1.uninstall:
	@echo '  [RM]    $(LIBDIR)/libmpkgmk.so.0.0.1'
	$(Q)rm -f '$(DESTDIR)$(LIBDIR)/libmpkgmk.so.0.0.1'

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
install: subdirs.install libmpkgmk.install

subdirs.install:
	$(Q)for i in ; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" INCLUDEDIR="$(INCLUDEDIR)" install); done

uninstall: subdirs.uninstall libmpkgmk.uninstall

subdirs.uninstall:
	$(Q)for i in ; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" INCLUDEDIR="$(INCLUDEDIR)" uninstall); done

clean: libmpkgmk.clean shell.o.clean ui.o.clean

distclean: clean

.PHONY: all subdirs clean distclean dist install uninstall

