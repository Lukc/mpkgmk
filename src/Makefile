
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

all: main modules

main: main.o ui.o recipe.o modules.o workdir.o download.o configuration.o extraction.o build.o assemble.o
	@$Necho "  [LD]  $@"
	$Q${CC} -o main -lyaml -ldl $^

modules:
	@cd modules; ${MAKE} LIBDIR="${LIBDIR}" SHAREDIR="${SHAREDIR}" BINDIR="${BINDIR}" PREFIX="${PREFIX}" CFLAGS="${CFLAGS}"

${BINDIR}:
	@mkdir -p ${BINDIR}

install: ${BINDIR}
	install -m 755 main ${BINDIR}/mpkgmk
	@cd modules; ${MAKE} install LIBDIR="${LIBDIR}" SHAREDIR="${SHAREDIR}" BINDIR="${BINDIR}" PREFIX="${PREFIX}" CFLAGS="${CFLAGS}"

clean:
	rm -f *.o main
	@cd modules; ${MAKE} clean

