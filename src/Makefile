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

all:  mpkgmk subdirs

mpkgmk: assemble.o build.o configuration.o download.o extraction.o main.o modules.o recipe.o workdir.o error.h path_max.h include/mpkgmk.h include/mpkgmk_private.h
	@echo '  [LD]    mpkgmk'
	$(Q)$(CC) -o mpkgmk $(CFLAGS) $(LDFLAGS) -ldl -lyaml -lmpkgmk -Llib assemble.o build.o configuration.o download.o extraction.o main.o modules.o recipe.o workdir.o

assemble.o: assemble.c assemble.h
	@echo '  [CC]    assemble.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -Iinclude -c assemble.c

assemble.o.clean:
	@echo '  [RM]    assemble.o'
	$(Q)rm -f assemble.o

build.o: build.c build.h
	@echo '  [CC]    build.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -Iinclude -c build.c

build.o.clean:
	@echo '  [RM]    build.o'
	$(Q)rm -f build.o

configuration.o: configuration.c configuration.h
	@echo '  [CC]    configuration.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -Iinclude -c configuration.c

configuration.o.clean:
	@echo '  [RM]    configuration.o'
	$(Q)rm -f configuration.o

download.o: download.c download.h
	@echo '  [CC]    download.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -Iinclude -c download.c

download.o.clean:
	@echo '  [RM]    download.o'
	$(Q)rm -f download.o

extraction.o: extraction.c extraction.h
	@echo '  [CC]    extraction.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -Iinclude -c extraction.c

extraction.o.clean:
	@echo '  [RM]    extraction.o'
	$(Q)rm -f extraction.o

main.o: main.c 
	@echo '  [CC]    main.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -Iinclude -c main.c

main.o.clean:
	@echo '  [RM]    main.o'
	$(Q)rm -f main.o

modules.o: modules.c modules.h
	@echo '  [CC]    modules.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -Iinclude -c modules.c

modules.o.clean:
	@echo '  [RM]    modules.o'
	$(Q)rm -f modules.o

recipe.o: recipe.c recipe.h
	@echo '  [CC]    recipe.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -Iinclude -c recipe.c

recipe.o.clean:
	@echo '  [RM]    recipe.o'
	$(Q)rm -f recipe.o

workdir.o: workdir.c workdir.h
	@echo '  [CC]    workdir.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -Iinclude -c workdir.c

workdir.o.clean:
	@echo '  [RM]    workdir.o'
	$(Q)rm -f workdir.o

mpkgmk.install: mpkgmk
	@echo '  [IN]    $(BINDIR)/mpkgmk'
	$(Q)install -m0755 mpkgmk $(DESTDIR)$(BINDIR)/mpkgmk

mpkgmk.clean:
	@echo '  [RM]    mpkgmk'
	$(Q)rm -f mpkgmk

mpkgmk.uninstall:
	@echo '  [RM]    $(BINDIR)/mpkgmk'
	$(Q)rm -f '$(DESTDIR)$(BINDIR)/mpkgmk'

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
subdirs:
	$(Q)for i in modules include; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" INCLUDEDIR="$(INCLUDEDIR)"); done

install: subdirs.install mpkgmk.install

subdirs.install:
	$(Q)for i in modules include; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" INCLUDEDIR="$(INCLUDEDIR)" install); done

uninstall: subdirs.uninstall mpkgmk.uninstall

subdirs.uninstall:
	$(Q)for i in modules include; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" INCLUDEDIR="$(INCLUDEDIR)" uninstall); done

clean: mpkgmk.clean assemble.o.clean build.o.clean configuration.o.clean download.o.clean extraction.o.clean main.o.clean modules.o.clean recipe.o.clean workdir.o.clean
	$(Q)for i in modules include; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" INCLUDEDIR="$(INCLUDEDIR)" clean); done

distclean: clean
	$(Q)for i in modules include; do (cd "$$i" && $(MAKE) Q=$(Q) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" DESTDIR="$(DESTDIR)" PREFIX="$(PREFIX)" BINDIR="$(BINDIR)" LIBDIR="$(LIBDIR)" SHAREDIR="$(SHAREDIR)" INCLUDEDIR="$(INCLUDEDIR)" distclean); done

.PHONY: all subdirs clean distclean dist install uninstall

