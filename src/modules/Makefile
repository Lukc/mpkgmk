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

all:  archive.so curl.so lua.so on_load.lua

archive.so: archive.o  ../include/mpkgmk.h ../include/mpkgmk_private.h
	@echo '  [LD]    archive.so'
	$(Q)$(CC) -o archive.so -fPIC -shared $(CFLAGS) $(LDFLAGS) -larchive -L../lib archive.o


archive.o: archive.c 
	@echo '  [CC]    archive.o'
	$(Q)$(CC) -fPIC $(CFLAGS)  -I../include -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c archive.c

archive.o.clean:
	@echo '  [RM]    archive.o'
	$(Q)rm -f archive.o

archive.so.install: archive.so $(DESTDIR)$(LIBDIR)/mpkgmk
	@echo '  [IN]    $(LIBDIR)/mpkgmk/archive.so'
	$(Q)install -m755 archive.so $(DESTDIR)$(LIBDIR)/mpkgmk/archive.so

archive.so.clean:
	@echo '  [RM]    archive.so'
	$(Q)rm -f archive.so

archive.so.uninstall:
	@echo '  [RM]    $(LIBDIR)/mpkgmk/archive.so'
	$(Q)rm -f '$(DESTDIR)$(LIBDIR)/mpkgmk/archive.so'

curl.so: curl.o  ../include/mpkgmk.h ../include/mpkgmk_private.h
	@echo '  [LD]    curl.so'
	$(Q)$(CC) -o curl.so -fPIC -shared $(CFLAGS) $(LDFLAGS) -lcurl -L../lib curl.o


curl.o: curl.c 
	@echo '  [CC]    curl.o'
	$(Q)$(CC) -fPIC $(CFLAGS)  -I../include -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c curl.c

curl.o.clean:
	@echo '  [RM]    curl.o'
	$(Q)rm -f curl.o

curl.so.install: curl.so $(DESTDIR)$(LIBDIR)/mpkgmk
	@echo '  [IN]    $(LIBDIR)/mpkgmk/curl.so'
	$(Q)install -m755 curl.so $(DESTDIR)$(LIBDIR)/mpkgmk/curl.so

curl.so.clean:
	@echo '  [RM]    curl.so'
	$(Q)rm -f curl.so

curl.so.uninstall:
	@echo '  [RM]    $(LIBDIR)/mpkgmk/curl.so'
	$(Q)rm -f '$(DESTDIR)$(LIBDIR)/mpkgmk/curl.so'

lua.so: lua.o  ../include/mpkgmk.h ../include/mpkgmk_private.h
	@echo '  [LD]    lua.so'
	$(Q)$(CC) -o lua.so -fPIC -shared $(CFLAGS) $(LDFLAGS) -llua -L../lib lua.o


lua.o: lua.c 
	@echo '  [CC]    lua.o'
	$(Q)$(CC) -fPIC $(CFLAGS)  -I../include -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c lua.c

lua.o.clean:
	@echo '  [RM]    lua.o'
	$(Q)rm -f lua.o

lua.so.install: lua.so $(DESTDIR)$(LIBDIR)/mpkgmk
	@echo '  [IN]    $(LIBDIR)/mpkgmk/lua.so'
	$(Q)install -m755 lua.so $(DESTDIR)$(LIBDIR)/mpkgmk/lua.so

lua.so.clean:
	@echo '  [RM]    lua.so'
	$(Q)rm -f lua.so

lua.so.uninstall:
	@echo '  [RM]    $(LIBDIR)/mpkgmk/lua.so'
	$(Q)rm -f '$(DESTDIR)$(LIBDIR)/mpkgmk/lua.so'

on_load.lua:
	@echo '  [  ]    on_load.lua'

on_load.lua.install: $(DESTDIR)$(SHAREDIR)/mpkgmk
	@echo '  [IN]    $(SHAREDIR)/mpkgmk/on_load.lua'
	$(Q)install -m755 on_load.lua $(DESTDIR)$(SHAREDIR)/mpkgmk/on_load.lua

on_load.lua.clean:

on_load.lua.uninstall:
	@echo '  [RM]    $(SHAREDIR)/mpkgmk/on_load.lua'
	$(Q)rm -f '$(DESTDIR)$(SHAREDIR)/mpkgmk/on_load.lua'

$(DESTDIR)$(LIBDIR)/mpkgmk:
	@echo '  [DIR]   $(LIBDIR)/mpkgmk'
	$(Q)mkdir -p $(DESTDIR)$(LIBDIR)/mpkgmk
$(DESTDIR)$(SHAREDIR)/mpkgmk:
	@echo '  [DIR]   $(SHAREDIR)/mpkgmk'
	$(Q)mkdir -p $(DESTDIR)$(SHAREDIR)/mpkgmk
$(DESTDIR)$(SHAREDIR)/mpkgmk/lua:
	@echo '  [DIR]   $(SHAREDIR)/mpkgmk/lua'
	$(Q)mkdir -p $(DESTDIR)$(SHAREDIR)/mpkgmk/lua
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
install: subdirs.install archive.so.install curl.so.install lua.so.install on_load.lua.install

subdirs.install:
	$(Q)for i in ; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" INCLUDEDIR="$(INCLUDEDIR)" install); done

uninstall: subdirs.uninstall archive.so.uninstall curl.so.uninstall lua.so.uninstall on_load.lua.uninstall

subdirs.uninstall:
	$(Q)for i in ; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" INCLUDEDIR="$(INCLUDEDIR)" uninstall); done

clean: archive.so.clean archive.o.clean curl.so.clean curl.o.clean lua.so.clean lua.o.clean on_load.lua.clean

distclean: clean

.PHONY: all subdirs clean distclean dist install uninstall

