PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
LIBDIR := $(PREFIX)/lib
SHAREDIR := $(PREFIX)/share

CFLAGS := -O0 -g -Wall -Wextra -D_BSD_SOURCE -Wno-unused-parameter
LDFLAGS := 

Q := @

all:  mpkgmk subdirs

mpkgmk: assemble.o build.o configuration.o download.o extraction.o main.o modules.o recipe.o ui.o workdir.o error.h
	@echo '  [LD]    mpkgmk'
	$(Q)$(CC) -o mpkgmk $(CFLAGS) $(LDFLAGS) -ldl -lyaml assemble.o build.o configuration.o download.o extraction.o main.o modules.o recipe.o ui.o workdir.o

assemble.o: assemble.c assemble.h
	@echo '  [CC]    assemble.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c assemble.c

assemble.o.clean:
	@echo '  [RM]    assemble.o'
	$(Q)rm -f assemble.o

build.o: build.c build.h
	@echo '  [CC]    build.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c build.c

build.o.clean:
	@echo '  [RM]    build.o'
	$(Q)rm -f build.o

configuration.o: configuration.c configuration.h
	@echo '  [CC]    configuration.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c configuration.c

configuration.o.clean:
	@echo '  [RM]    configuration.o'
	$(Q)rm -f configuration.o

download.o: download.c download.h
	@echo '  [CC]    download.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c download.c

download.o.clean:
	@echo '  [RM]    download.o'
	$(Q)rm -f download.o

extraction.o: extraction.c extraction.h
	@echo '  [CC]    extraction.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c extraction.c

extraction.o.clean:
	@echo '  [RM]    extraction.o'
	$(Q)rm -f extraction.o

main.o: main.c 
	@echo '  [CC]    main.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c main.c

main.o.clean:
	@echo '  [RM]    main.o'
	$(Q)rm -f main.o

modules.o: modules.c modules.h
	@echo '  [CC]    modules.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c modules.c

modules.o.clean:
	@echo '  [RM]    modules.o'
	$(Q)rm -f modules.o

recipe.o: recipe.c recipe.h
	@echo '  [CC]    recipe.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c recipe.c

recipe.o.clean:
	@echo '  [RM]    recipe.o'
	$(Q)rm -f recipe.o

ui.o: ui.c ui.h
	@echo '  [CC]    ui.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c ui.c

ui.o.clean:
	@echo '  [RM]    ui.o'
	$(Q)rm -f ui.o

workdir.o: workdir.c workdir.h
	@echo '  [CC]    workdir.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -c workdir.c

workdir.o.clean:
	@echo '  [RM]    workdir.o'
	$(Q)rm -f workdir.o

mpkgmk.install: $(DESTDIR)$(BINDIR)
	@echo '  [IN]    $(BINDIR)/mpkgmk'
	$(Q)install -m755 mpkgmk $(DESTDIR)$(BINDIR)/mpkgmk

mpkgmk.clean:
	@echo '  [RM]    mpkgmk'
	$(Q)rm -f mpkgmk

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
subdirs:
	$(Q)for i in modules; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)"); done

install: subdirs.install mpkgmk.install

subdirs.install:
	$(Q)for i in modules; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" install); done

clean: mpkgmk.clean assemble.o.clean build.o.clean configuration.o.clean download.o.clean extraction.o.clean main.o.clean modules.o.clean recipe.o.clean ui.o.clean workdir.o.clean
	$(Q)for i in modules; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" clean); done

distclean: clean
	$(Q)for i in modules; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" distclean); done

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
		$(PACKAGE)-$(VERSION)/assemble.c \
		$(PACKAGE)-$(VERSION)/build.c \
		$(PACKAGE)-$(VERSION)/configuration.c \
		$(PACKAGE)-$(VERSION)/download.c \
		$(PACKAGE)-$(VERSION)/extraction.c \
		$(PACKAGE)-$(VERSION)/main.c \
		$(PACKAGE)-$(VERSION)/modules.c \
		$(PACKAGE)-$(VERSION)/recipe.c \
		$(PACKAGE)-$(VERSION)/ui.c \
		$(PACKAGE)-$(VERSION)/workdir.c \
		$(PACKAGE)-$(VERSION)/error.h \
		$(PACKAGE)-$(VERSION)/assemble.h \
		$(PACKAGE)-$(VERSION)/build.h \
		$(PACKAGE)-$(VERSION)/configuration.h \
		$(PACKAGE)-$(VERSION)/download.h \
		$(PACKAGE)-$(VERSION)/extraction.h \
		$(PACKAGE)-$(VERSION)/modules.h \
		$(PACKAGE)-$(VERSION)/recipe.h \
		$(PACKAGE)-$(VERSION)/ui.h \
		$(PACKAGE)-$(VERSION)/workdir.h \
		$(PACKAGE)-$(VERSION)/modules/makefile \
		$(PACKAGE)-$(VERSION)/modules/project.zsh \
		$(PACKAGE)-$(VERSION)/modules/curl.c \
		$(PACKAGE)-$(VERSION)/modules/archive.c \
		$(PACKAGE)-$(VERSION)/modules/test.c \
		$(PACKAGE)-$(VERSION)/modules/lua.c

dist-xz: $(PACKAGE)-$(VERSION).tar.xz
$(PACKAGE)-$(VERSION).tar.xz: distdir
	@echo '  [TAR]   $(PACKAGE)-$(VERSION).tar.xz'
	$(Q)tar cJf $(PACKAGE)-$(VERSION).tar.xz \
		$(PACKAGE)-$(VERSION)/Makefile \
		$(PACKAGE)-$(VERSION)/project.zsh \
		$(PACKAGE)-$(VERSION)/assemble.c \
		$(PACKAGE)-$(VERSION)/build.c \
		$(PACKAGE)-$(VERSION)/configuration.c \
		$(PACKAGE)-$(VERSION)/download.c \
		$(PACKAGE)-$(VERSION)/extraction.c \
		$(PACKAGE)-$(VERSION)/main.c \
		$(PACKAGE)-$(VERSION)/modules.c \
		$(PACKAGE)-$(VERSION)/recipe.c \
		$(PACKAGE)-$(VERSION)/ui.c \
		$(PACKAGE)-$(VERSION)/workdir.c \
		$(PACKAGE)-$(VERSION)/error.h \
		$(PACKAGE)-$(VERSION)/assemble.h \
		$(PACKAGE)-$(VERSION)/build.h \
		$(PACKAGE)-$(VERSION)/configuration.h \
		$(PACKAGE)-$(VERSION)/download.h \
		$(PACKAGE)-$(VERSION)/extraction.h \
		$(PACKAGE)-$(VERSION)/modules.h \
		$(PACKAGE)-$(VERSION)/recipe.h \
		$(PACKAGE)-$(VERSION)/ui.h \
		$(PACKAGE)-$(VERSION)/workdir.h \
		$(PACKAGE)-$(VERSION)/modules/makefile \
		$(PACKAGE)-$(VERSION)/modules/project.zsh \
		$(PACKAGE)-$(VERSION)/modules/curl.c \
		$(PACKAGE)-$(VERSION)/modules/archive.c \
		$(PACKAGE)-$(VERSION)/modules/test.c \
		$(PACKAGE)-$(VERSION)/modules/lua.c

dist-bz2: $(PACKAGE)-$(VERSION).tar.bz2
$(PACKAGE)-$(VERSION).tar.bz2: distdir
	@echo '  [TAR]   $(PACKAGE)-$(VERSION).tar.bz2'
	$(Q)tar cjf $(PACKAGE)-$(VERSION).tar.bz2 \
		$(PACKAGE)-$(VERSION)/Makefile \
		$(PACKAGE)-$(VERSION)/project.zsh \
		$(PACKAGE)-$(VERSION)/assemble.c \
		$(PACKAGE)-$(VERSION)/build.c \
		$(PACKAGE)-$(VERSION)/configuration.c \
		$(PACKAGE)-$(VERSION)/download.c \
		$(PACKAGE)-$(VERSION)/extraction.c \
		$(PACKAGE)-$(VERSION)/main.c \
		$(PACKAGE)-$(VERSION)/modules.c \
		$(PACKAGE)-$(VERSION)/recipe.c \
		$(PACKAGE)-$(VERSION)/ui.c \
		$(PACKAGE)-$(VERSION)/workdir.c \
		$(PACKAGE)-$(VERSION)/error.h \
		$(PACKAGE)-$(VERSION)/assemble.h \
		$(PACKAGE)-$(VERSION)/build.h \
		$(PACKAGE)-$(VERSION)/configuration.h \
		$(PACKAGE)-$(VERSION)/download.h \
		$(PACKAGE)-$(VERSION)/extraction.h \
		$(PACKAGE)-$(VERSION)/modules.h \
		$(PACKAGE)-$(VERSION)/recipe.h \
		$(PACKAGE)-$(VERSION)/ui.h \
		$(PACKAGE)-$(VERSION)/workdir.h \
		$(PACKAGE)-$(VERSION)/modules/makefile \
		$(PACKAGE)-$(VERSION)/modules/project.zsh \
		$(PACKAGE)-$(VERSION)/modules/curl.c \
		$(PACKAGE)-$(VERSION)/modules/archive.c \
		$(PACKAGE)-$(VERSION)/modules/test.c \
		$(PACKAGE)-$(VERSION)/modules/lua.c

.PHONY: all subdirs clean distclean dist install uninstall

