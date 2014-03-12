
targets=( mpkgmk )

type[mpkgmk]="binary"
sources[mpkgmk]="assemble.c build.c configuration.c download.c extraction.c main.c modules.c recipe.c workdir.c"
cflags[mpkgmk]='-DLIBDIR=\"$(LIBDIR)/mpkgmk\" -DSHAREDIR=\"$(SHAREDIR)/mpkgmk\"'
ldflags[mpkgmk]="-ldl -lyaml -lmpkgmk"
depends[mpkgmk]="error.h path_max.h include/mpkgmk.h include/mpkgmk_private.h"

subdirs=(modules include)

dist=(
	Makefile project.zsh
)

for target in ${targets[@]}; do
	cflags[$target]+=" -Iinclude"
	ldflags[$target]+=" -Llib"
done

