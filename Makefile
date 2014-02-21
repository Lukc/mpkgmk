
all:
	cd src; ${MAKE}
	cd src/modules; ${MAKE}
	ln -sf src/main mpkgmk

clean:
	cd src; ${MAKE} clean
	rm -f mpkgmk

