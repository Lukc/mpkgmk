
%.o: %.c
	${CC} -fpic -c $^

%.so: %.o
	${CC} -shared -o $@ $^

all: archive.so test.so

archive.so: archive.o
	${CC} -shared -o $@ $^ -larchive

${LIBDIR}/mpkgmk:
	mkdir -p ${LIBDIR}/mpkgmk

install-archive.so: ${LIBDIR}/mpkgmk
	cp archive.so ${LIBDIR}/mpkgmk/archive.so

install: install-archive.so


clean:
	rm -rf *.o *.so

