
%.o: %.c
	${CC} ${CFLAGS} -fpic -c $^

%.so: %.o
	${CC} ${CFLAGS} -shared -o $@ $^

all: archive.so curl.so test.so

archive.so: archive.o
	${CC} -shared -o $@ $^ -larchive

curl.so: curl.o
	${CC} -shared -o $@ $^ -lcurl

${LIBDIR}/mpkgmk:
	mkdir -p ${LIBDIR}/mpkgmk

install-archive.so: ${LIBDIR}/mpkgmk archive.so
	install -m 755 archive.so ${LIBDIR}/mpkgmk/archive.so

install-curl.so: ${LIBDIR}/mpkgmk curl.so
	install -m 755 curl.so ${LIBDIR}/mpkgmk/curl.so

install: install-archive.so install-curl.so

clean:
	rm -rf *.o *.so

