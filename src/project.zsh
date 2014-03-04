
targets=( mpkgmk )

type[mpkgmk]="binary"
sources[mpkgmk]="assemble.c build.c configuration.c download.c extraction.c main.c modules.c recipe.c ui.c workdir.c"
cflags[mpkgmk]='-DLIBDIR=\"$(LIBDIR)/mpkgmk\"'
ldflags[mpkgmk]="-ldl -lyaml"

subdirs=(modules)

#	mpkgmk=(
#		type="binary"
#		sources=(
#			"assemble.c" "build.c" "configuration.c" "download.c" "extraction.c"
#		)
#		ldflags="-ldl -lyaml"
#		depends=(error.h)
#		install='$(BINDIR)'
#	)
#)

dist=(
	Makefile project.zsh
)

