ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = -I${top_srcdir}/include
AM_CFLAGS = $(TARGET_CFLAGS)

if WITH_CCS

# Optimize for size
AM_CFLAGS += -mf=0

# CCS recognizes -o in its standard role specifying the output file only
# when linking, not when compiling, so have to override implicit rule to
# pass the flag required to rename the output.
%.o: %.c
	$(CC) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS) -c $< --output_file $@

endif # WITH_CCS

if WITH_GCC

# Force all available checks
AM_CFLAGS += -Wall -Werror -ansi -std=c99 -pedantic

# Support -gc-sections at link time
AM_CFLAGS += -ffunction-sections -fdata-sections

# Optimize for size unless using gcov
@WITH_GCOV_FALSE@ AM_CFLAGS += -Os
@WITH_GCOV_TRUE@ AM_CFLAGS += -fprofile-arcs -ftest-coverage -O0

endif # WITH_GCC

embtextfdir = ${libdir}
libembtextf_la_SOURCES = \
	vuprintf.c \
	itoa.c ltoa.c lltoa.c

if EMBTEXTF_PROVIDE_LIBC
libembtextf_libc_la_SOURCES = libc.c
embtextf_libcdir = ${libdir}
endif # EMBTEXTF_PROVIDE_LIBC

if WITH_LIBTOOL

embtextf_LTLIBRARIES = libembtextf.la

if EMBTEXTF_PROVIDE_LIBC
embtextf_libc_LTLIBRARIES = libembtextf-libc.la
endif # EMBTEXTF_PROVIDE_LIBC

else # WITH_LIBTOOL

libembtextf_la_OBJ = $(libembtextf_la_SOURCES:.c=.o)
libembtextf.a: $(libembtextf_la_OBJ)
	$(AR) rv $@ $^

embtextf_DATA = libembtextf.a

CLEANFILES = $(libembtextf_la_OBJ) $(embtextf_DATA)

if EMBTEXTF_PROVIDE_LIBC

libembtextf_libc_la_OBJ = $(libembtextf_libc_la_SOURCES:.c=.o)

libembtextf-libc.a: $(libembtextf_libc_la_OBJ)
	$(AR) rv $@ $^

embtextf_libc_DATA = libembtextf-libc.a

CLEANFILES += $(libembtextf_libc_la_OBJ) $(embtextf_libc_DATA)

endif # EMBTEXTF_PROVIDE_LIBC

endif # WITH_LIBTOOL

clean-local:
	-rm *.gcda *.gcno

