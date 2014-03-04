targets=(archive.so curl.so test.so)

install[archive.so]='$(LIBDIR)/mpkgmk'
sources[archive.so]=archive.c
ldflags[archive.so]=-larchive
type[archive.so]=dynamic-library

install[curl.so]='$(LIBDIR)/mpkgmk'
sources[curl.so]=curl.c
ldflags[curl.so]=-lcurl
type[curl.so]=dynamic-library

install[test.so]='$(LIBDIR)/mpkgmk'
sources[test.so]=test.c
type[test.so]=dynamic-library

dist=(
	Makefile project.zsh
)

