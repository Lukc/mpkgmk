
package=mpkgmk
version=0.0.1

subdirs=(
	src
)
dist=(
	Makefile
	project.lua
	package.yaml
)

CFLAGS="-O0 -g -Wall -Wextra -ansi -pedantic -D_BSD_SOURCE -Wno-unused-parameter"

