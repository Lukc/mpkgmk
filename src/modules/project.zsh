targets=(archive.so curl.so test.so lua.so)

install[archive.so]='$(LIBDIR)/mpkgmk'
sources[archive.so]=archive.c
ldflags[archive.so]=-larchive
type[archive.so]=dynamic-library

install[curl.so]='$(LIBDIR)/mpkgmk'
sources[curl.so]=curl.c
ldflags[curl.so]=-lcurl
type[curl.so]=dynamic-library

install[lua.so]='$(LIBDIR)/mpkgmk'
sources[lua.so]=lua.c
ldflags[lua.so]="-llua"
type[lua.so]=dynamic-library

install[test.so]='$(LIBDIR)/mpkgmk'
sources[test.so]=test.c
type[test.so]=dynamic-library

dist=(
	Makefile project.zsh
)

for i in ${targets[@]}; do
	cflags[${i}]='-DLIBDIR=\"$(LIBDIR)/mpkgmk\"'
done

