
PREFIX   := /usr/local
BINDIR   := ${PREFIX}/bin
LIBDIR   := ${PREFIX}/lib
SHAREDIR := ${PREFIX}/share

CFLAGS += -Wall -Wextra -ansi -pedantic -D_BSD_SOURCE -g
# Modules and stuff might ignore some data. We don’t want no warning from them.
CFLAGS += -Wno-unused-parameter
CFLAGS += -fPIC

CFLAGS += '-DBINDIR="${BINDIR}"'
CFLAGS += '-DLIBDIR="${LIBDIR}/mpkgmk"'
CFLAGS += '-DSHAREDIR="${SHAREDIR}/mpkgmk"'

Q := @
N := 

%.o: %.c
	@$Necho "  [CC]  $@"
	$Q${CC} ${CFLAGS} -c $<

%.o: %.c %.h
	@$Necho "  [CC]  $@"
	$Q${CC} ${CFLAGS} -c $<

main: main.o ui.o recipe.o modules.o workdir.o download.o configuration.o extraction.o build.o assemble.o
	@$Necho "  [LD]  $@"
	$Q${CC} -o main -lyaml -ldl $^

${BINDIR}:
	@mkdir -p ${BINDIR}

install: ${BINDIR}
	cp main ${BINDIR}/mpkgmk
	@cd modules; ${MAKE} install

clean:
	rm -f *.o main
	@cd modules; ${MAKE} clean

