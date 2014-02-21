
%.o: %.c
	${CC} -fpic -c $^

%.so: %.o
	${CC} -shared -o $@ $^

all: archive.so test.so

archive.so: archive.o
	${CC} -shared -o $@ $^ -larchive

clean:
	rm -rf *.o *.so

