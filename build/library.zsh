
# FIXME: Build static libraries as well.
# FIXME: Add symlinks at installation.

function library.build {
	write "${target}: ${target}.so"
	write

	target="${target}.so" dynamic-library.build
}

function library.install {
	write "${target}.install: ${target}.so.install"
	write

	target="${target}.so" dynamic-library.install
}

