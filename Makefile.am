ACLOCAL_AMFLAGS = -I m4
SUBDIRS = include/embtextf src tests doc

EXTRA_DIST = LICENSE README.rst

.PHONY: astyle
ASTYLE_ARGS=--options=none --style=1tbs --indent=spaces=2 --indent-switches --pad-header
astyle:
	astyle $(ASTYLE_ARGS) -r '*.c' '*.h' '*.inc'

pcdir = $(libdir)/pkgconfig
pc_DATA = embtextf.pc
