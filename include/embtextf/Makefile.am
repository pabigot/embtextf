ACLOCAL_AMFLAGS = -I m4

# Public headers are put into a embtextf subdirectory so they only
# conflict with other project namespaces if somebody includes distinct
# headers that use the same multiple-include symbol.
embtextfincdir = ${includedir}/embtextf

# Optionally add libc-related headers
if EMBTEXTF_PROVIDE_LIBC
MAYBE_LIBC = stdio.h stdarg.h
endif # EMBTEXTF_PROVIDE_LIBC

embtextfinc_HEADERS = \
	version.h uprintf.h xtoa.h \
	config.h \
	$(MAYBE_LIBC)
