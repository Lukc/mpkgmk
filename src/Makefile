PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
LIBDIR := $(PREFIX)/lib
SHAREDIR := $(PREFIX)/share

CFLAGS := -O0 -g -Wall -Wextra -D_BSD_SOURCE -Wno-unused-parameter
LDFLAGS := 

Q := @

all:  mpkgmk subdirs

mpkgmk: assemble.o build.o configuration.o download.o extraction.o main.o modules.o recipe.o ui.o workdir.o error.h mpkgmk.h mpkgmk_private.h
	@echo '  [LD]    mpkgmk'
	$(Q)$(CC) -o mpkgmk $(CFLAGS) $(LDFLAGS) -ldl -lyaml assemble.o build.o configuration.o download.o extraction.o main.o modules.o recipe.o ui.o workdir.o

assemble.o: assemble.c assemble.h
	@echo '  [CC]    assemble.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -I. -c assemble.c

assemble.o.clean:
	@echo '  [RM]    assemble.o'
	$(Q)rm -f assemble.o

build.o: build.c build.h
	@echo '  [CC]    build.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -I. -c build.c

build.o.clean:
	@echo '  [RM]    build.o'
	$(Q)rm -f build.o

configuration.o: configuration.c configuration.h
	@echo '  [CC]    configuration.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -I. -c configuration.c

configuration.o.clean:
	@echo '  [RM]    configuration.o'
	$(Q)rm -f configuration.o

download.o: download.c download.h
	@echo '  [CC]    download.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -I. -c download.c

download.o.clean:
	@echo '  [RM]    download.o'
	$(Q)rm -f download.o

extraction.o: extraction.c extraction.h
	@echo '  [CC]    extraction.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -I. -c extraction.c

extraction.o.clean:
	@echo '  [RM]    extraction.o'
	$(Q)rm -f extraction.o

main.o: main.c 
	@echo '  [CC]    main.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -I. -c main.c

main.o.clean:
	@echo '  [RM]    main.o'
	$(Q)rm -f main.o

modules.o: modules.c modules.h
	@echo '  [CC]    modules.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -I. -c modules.c

modules.o.clean:
	@echo '  [RM]    modules.o'
	$(Q)rm -f modules.o

recipe.o: recipe.c recipe.h
	@echo '  [CC]    recipe.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -I. -c recipe.c

recipe.o.clean:
	@echo '  [RM]    recipe.o'
	$(Q)rm -f recipe.o

ui.o: ui.c ui.h
	@echo '  [CC]    ui.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -I. -c ui.c

ui.o.clean:
	@echo '  [RM]    ui.o'
	$(Q)rm -f ui.o

workdir.o: workdir.c workdir.h
	@echo '  [CC]    workdir.o'
	$(Q)$(CC) $(CFLAGS) -DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\" -I. -c workdir.c

workdir.o.clean:
	@echo '  [RM]    workdir.o'
	$(Q)rm -f workdir.o

mpkgmk.install: mpkgmk
	@echo '  [IN]    $(BINDIR)/mpkgmk'
	$(Q)install -m0755 mpkgmk $(DESTDIR)$(BINDIR)/mpkgmk

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

.PHONY: all subdirs clean distclean dist install uninstall

