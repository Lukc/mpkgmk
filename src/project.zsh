
targets=( mpkgmk )

type[mpkgmk]="binary"
sources[mpkgmk]="assemble.c build.c configuration.c download.c extraction.c main.c modules.c recipe.c ui.c workdir.c"
cflags[mpkgmk]='-DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\"'
ldflags[mpkgmk]="-ldl -lyaml"
depends[mpkgmk]="error.h"

subdirs=(modules)

dist=(
	Makefile project.zsh
)

