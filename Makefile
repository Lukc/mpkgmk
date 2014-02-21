
all:
	@cd src; ${MAKE} all
	ln -sf src/main mpkgmk

install:
	@cd src; ${MAKE} install

clean:
	@cd src; ${MAKE} clean
	rm -f mpkgmk

