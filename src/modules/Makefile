PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
LIBDIR := $(PREFIX)/lib
SHAREDIR := $(PREFIX)/share

CFLAGS := -O0 -g -Wall -Wextra -D_BSD_SOURCE -Wno-unused-parameter
LDFLAGS := 

Q := @

all:  archive.so curl.so test.so lua.so on_load.lua

archive.so: archive.o 
	@echo '  [LD]    archive.so'
	$(Q)$(CC) -o archive.so -fPIC -shared $(CFLAGS) $(LDFLAGS) -larchive archive.o


archive.o: archive.c 
	@echo '  [CC]    archive.o'
	$(Q)$(CC) -fPIC $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c archive.c

archive.o.clean:
	@echo '  [RM]    archive.o'
	$(Q)rm -f archive.o

archive.so.install: $(DESTDIR)$(LIBDIR)/mpkgmk
	@echo '  [IN]    $(LIBDIR)/mpkgmk/archive.so'
	$(Q)install -m755 archive.so $(DESTDIR)$(LIBDIR)/mpkgmk/archive.so

archive.so.clean:
	@echo '  [RM]    archive.so'
	$(Q)rm -f archive.so

curl.so: curl.o 
	@echo '  [LD]    curl.so'
	$(Q)$(CC) -o curl.so -fPIC -shared $(CFLAGS) $(LDFLAGS) -lcurl curl.o


curl.o: curl.c 
	@echo '  [CC]    curl.o'
	$(Q)$(CC) -fPIC $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c curl.c

curl.o.clean:
	@echo '  [RM]    curl.o'
	$(Q)rm -f curl.o

curl.so.install: $(DESTDIR)$(LIBDIR)/mpkgmk
	@echo '  [IN]    $(LIBDIR)/mpkgmk/curl.so'
	$(Q)install -m755 curl.so $(DESTDIR)$(LIBDIR)/mpkgmk/curl.so

curl.so.clean:
	@echo '  [RM]    curl.so'
	$(Q)rm -f curl.so

test.so: test.o 
	@echo '  [LD]    test.so'
	$(Q)$(CC) -o test.so -fPIC -shared $(CFLAGS) $(LDFLAGS)  test.o


test.o: test.c 
	@echo '  [CC]    test.o'
	$(Q)$(CC) -fPIC $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c test.c

test.o.clean:
	@echo '  [RM]    test.o'
	$(Q)rm -f test.o

test.so.install: $(DESTDIR)$(LIBDIR)/mpkgmk
	@echo '  [IN]    $(LIBDIR)/mpkgmk/test.so'
	$(Q)install -m755 test.so $(DESTDIR)$(LIBDIR)/mpkgmk/test.so

test.so.clean:
	@echo '  [RM]    test.so'
	$(Q)rm -f test.so

lua.so: lua.o 
	@echo '  [LD]    lua.so'
	$(Q)$(CC) -o lua.so -fPIC -shared $(CFLAGS) $(LDFLAGS) -llua lua.o


lua.o: lua.c 
	@echo '  [CC]    lua.o'
	$(Q)$(CC) -fPIC $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c lua.c

lua.o.clean:
	@echo '  [RM]    lua.o'
	$(Q)rm -f lua.o

lua.so.install: $(DESTDIR)$(LIBDIR)/mpkgmk
	@echo '  [IN]    $(LIBDIR)/mpkgmk/lua.so'
	$(Q)install -m755 lua.so $(DESTDIR)$(LIBDIR)/mpkgmk/lua.so

lua.so.clean:
	@echo '  [RM]    lua.so'
	$(Q)rm -f lua.so

on_load.lua:
	@echo '  [  ]    on_load.lua'

on_load.lua.install: $(DESTDIR)$(SHAREDIR)/mpkgmk
	@echo '  [IN]    $(SHAREDIR)/mpkgmk/on_load.lua'
	$(Q)install -m755 on_load.lua $(DESTDIR)$(SHAREDIR)/mpkgmk/on_load.lua

on_load.lua.clean:
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
install: subdirs.install archive.so.install curl.so.install test.so.install lua.so.install on_load.lua.install

subdirs.install:
	$(Q)for i in ; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" install); done

clean: archive.so.clean archive.o.clean curl.so.clean curl.o.clean test.so.clean test.o.clean lua.so.clean lua.o.clean on_load.lua.clean

distclean: clean

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
		$(PACKAGE)-$(VERSION)/curl.c \
		$(PACKAGE)-$(VERSION)/archive.c \
		$(PACKAGE)-$(VERSION)/test.c \
		$(PACKAGE)-$(VERSION)/lua.c

dist-xz: $(PACKAGE)-$(VERSION).tar.xz
$(PACKAGE)-$(VERSION).tar.xz: distdir
	@echo '  [TAR]   $(PACKAGE)-$(VERSION).tar.xz'
	$(Q)tar cJf $(PACKAGE)-$(VERSION).tar.xz \
		$(PACKAGE)-$(VERSION)/Makefile \
		$(PACKAGE)-$(VERSION)/project.zsh \
		$(PACKAGE)-$(VERSION)/curl.c \
		$(PACKAGE)-$(VERSION)/archive.c \
		$(PACKAGE)-$(VERSION)/test.c \
		$(PACKAGE)-$(VERSION)/lua.c

dist-bz2: $(PACKAGE)-$(VERSION).tar.bz2
$(PACKAGE)-$(VERSION).tar.bz2: distdir
	@echo '  [TAR]   $(PACKAGE)-$(VERSION).tar.bz2'
	$(Q)tar cjf $(PACKAGE)-$(VERSION).tar.bz2 \
		$(PACKAGE)-$(VERSION)/Makefile \
		$(PACKAGE)-$(VERSION)/project.zsh \
		$(PACKAGE)-$(VERSION)/curl.c \
		$(PACKAGE)-$(VERSION)/archive.c \
		$(PACKAGE)-$(VERSION)/test.c \
		$(PACKAGE)-$(VERSION)/lua.c

.PHONY: all subdirs clean distclean dist install uninstall

