ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = -I${top_srcdir}/include

# If GCC and not GCOV, pass flag to optimize for size
@WITH_GCC_TRUE@@WITH_GCOV_FALSE@ AM_CFLAGS += -Os

# If GCC, support -gc-sections at link time
@WITH_GCC_TRUE@ AM_CFLAGS += -ffunction-sections -fdata-sections

# If GCOV, add required flags
@WITH_GCOV_TRUE@ AM_CFLAGS += -fprofile-arcs -ftest-coverage -O0

embtextfdir = ${libdir}
embtextf_LTLIBRARIES = libembtextf.la
libembtextf_la_SOURCES = \
	vuprintf.c \
	itoa.c ltoa.c lltoa.c

if EMBTEXTF_PROVIDE_LIBC
libembtextf_libc_la_SOURCES = libc.c
embtextf_libcdir = ${libdir}
embtextf_libc_LTLIBRARIES = libembtextf-libc.la
endif # EMBTEXTF_PROVIDE_LIBC

clean-local:
	-rm *.gcda *.gcno
