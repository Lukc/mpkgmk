
all:
	cd src; ${MAKE}
	ln -sf src/main mpkgmk

clean:
	cd src; ${MAKE} clean
	rm -f mpkgmk

