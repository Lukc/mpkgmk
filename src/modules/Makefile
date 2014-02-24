
Q=@

%.o: %.c
	@echo "  [CC]  $@"
	$Q${CC} ${CFLAGS} -fpic -c $^

%.so: %.o
	@echo "  [LD]  $@"
	$Q${CC} ${CFLAGS} -shared -o $@ $^

all: archive.so curl.so test.so

archive.so: archive.o
	@echo "  [LD]  $@"
	$Q${CC} -shared -o $@ $^ -larchive

curl.so: curl.o
	@echo "  [LD]  $@"
	$Q${CC} -shared -o $@ $^ -lcurl

${LIBDIR}/mpkgmk:
	mkdir -p ${LIBDIR}/mpkgmk

install-archive.so: ${LIBDIR}/mpkgmk archive.so
	install -m 755 archive.so ${LIBDIR}/mpkgmk/archive.so

install-curl.so: ${LIBDIR}/mpkgmk curl.so
	install -m 755 curl.so ${LIBDIR}/mpkgmk/curl.so

install-test.so: ${LIBDIR}/mpkgmk test.so
	install -m 755 test.so ${LIBDIR}/mpkgmk/test.so

install: install-archive.so install-curl.so install-test.so

clean:
	rm -rf *.o *.so

