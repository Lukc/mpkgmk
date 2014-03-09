
package=mpkgmk
version=0.0.1

subdirs=(
	src/lib
	src
)
dist=(
	Makefile
	project.zsh
	package.yaml
)

CFLAGS="-O0 -g -Wall -Wextra -D_BSD_SOURCE -Wno-unused-parameter"
#CFLAGS+="-ansi -pedantic"

