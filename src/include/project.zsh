
targets=( mpkgmk.h mpkgmk_private.h )

for i in ${targets[@]}; do
	type[${i}]=header
done

