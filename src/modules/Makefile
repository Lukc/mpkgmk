PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
LIBDIR := $(PREFIX)/lib

CFLAGS := -O0 -g -Wall -Wextra -D_BSD_SOURCE -Wno-unused-parameter
LDFLAGS := 

Q := @

all:  archive.so curl.so test.so

archive.so: archive.o 
	@echo '  [LD]    archive.so'
	$(Q)$(CC) -o archive.so -fPIC -shared $(CFLAGS) $(LDFLAGS) -larchive archive.o


archive.o: archive.c 
	@echo '  [CC]    archive.o'
	$(Q)$(CC) -fPIC $(CFLAGS)  -c archive.c

archive.o.clean:
	@echo '  [RM]    archive.o'
	$(Q)rm -f archive.o

archive.so.install: archive.so
	@echo "  [IN]    $(LIBDIR)/mpkgmk/archive.so"
	$(Q)install -m755 archive.so $(LIBDIR)/mpkgmk/archive.so
archive.so.clean:
	@echo '  [RM]    archive.so'
	$(Q)rm -f archive.so

curl.so: curl.o 
	@echo '  [LD]    curl.so'
	$(Q)$(CC) -o curl.so -fPIC -shared $(CFLAGS) $(LDFLAGS) -lcurl curl.o


curl.o: curl.c 
	@echo '  [CC]    curl.o'
	$(Q)$(CC) -fPIC $(CFLAGS)  -c curl.c

curl.o.clean:
	@echo '  [RM]    curl.o'
	$(Q)rm -f curl.o

curl.so.install: curl.so
	@echo "  [IN]    $(LIBDIR)/mpkgmk/curl.so"
	$(Q)install -m755 curl.so $(LIBDIR)/mpkgmk/curl.so
curl.so.clean:
	@echo '  [RM]    curl.so'
	$(Q)rm -f curl.so

test.so: test.o 
	@echo '  [LD]    test.so'
	$(Q)$(CC) -o test.so -fPIC -shared $(CFLAGS) $(LDFLAGS)  test.o


test.o: test.c 
	@echo '  [CC]    test.o'
	$(Q)$(CC) -fPIC $(CFLAGS)  -c test.c

test.o.clean:
	@echo '  [RM]    test.o'
	$(Q)rm -f test.o

test.so.install: test.so
	@echo "  [IN]    $(LIBDIR)/mpkgmk/test.so"
	$(Q)install -m755 test.so $(LIBDIR)/mpkgmk/test.so
test.so.clean:
	@echo '  [RM]    test.so'
	$(Q)rm -f test.so

install: subdirs.install archive.so.install curl.so.install test.so.install

subdirs.install:
	$(Q)for i in ; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" install); done

clean: archive.so.clean archive.o.clean curl.so.clean curl.o.clean test.so.clean test.o.clean

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
		$(PACKAGE)-$(VERSION)/test.c

dist-xz: $(PACKAGE)-$(VERSION).tar.xz
$(PACKAGE)-$(VERSION).tar.xz: distdir
	@echo '  [TAR]   $(PACKAGE)-$(VERSION).tar.xz'
	$(Q)tar cJf $(PACKAGE)-$(VERSION).tar.xz \
		$(PACKAGE)-$(VERSION)/Makefile \
		$(PACKAGE)-$(VERSION)/project.zsh \
		$(PACKAGE)-$(VERSION)/curl.c \
		$(PACKAGE)-$(VERSION)/archive.c \
		$(PACKAGE)-$(VERSION)/test.c

dist-bz2: $(PACKAGE)-$(VERSION).tar.bz2
$(PACKAGE)-$(VERSION).tar.bz2: distdir
	@echo '  [TAR]   $(PACKAGE)-$(VERSION).tar.bz2'
	$(Q)tar cjf $(PACKAGE)-$(VERSION).tar.bz2 \
		$(PACKAGE)-$(VERSION)/Makefile \
		$(PACKAGE)-$(VERSION)/project.zsh \
		$(PACKAGE)-$(VERSION)/curl.c \
		$(PACKAGE)-$(VERSION)/archive.c \
		$(PACKAGE)-$(VERSION)/test.c

.PHONY: all subdirs clean distclean dist install uninstall

