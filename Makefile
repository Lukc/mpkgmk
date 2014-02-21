
all:
	@cd src; ${MAKE}
	@cd src/modules; ${MAKE}
	ln -sf src/main mpkgmk

install:
	@cd src; ${MAKE} install

clean:
	@cd src; ${MAKE} clean
	rm -f mpkgmk

