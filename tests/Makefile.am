ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = -I${top_srcdir}/include
AM_CFLAGS = $(TARGET_CFLAGS)

# If GCC, force all available checks...
@WITH_GCC_TRUE@ AM_CFLAGS += -Wall -Werror -ansi -std=c99 -pedantic
# ...except these
@WITH_GCC_TRUE@ AM_CFLAGS += -Wno-error=format -Wno-error=format-extra-args

# If GCC, support -gc-sections at link time
@WITH_GCC_TRUE@ AM_LDFLAGS += -gc-sections

# If GCOV, add required flags
@WITH_GCOV_TRUE@ AM_CFLAGS += -fprofile-arcs -ftest-coverage
@WITH_GCOV_TRUE@ AM_LDFLAGS += -fprofile-arcs

# Note: To examine coverage, do:
# ./configure --enable-gcov
# make
# tests/test-basic
# (cd src ; gcov -a *.c )
# less src/vuprintf.c.gcov

if WITH_CUNIT
noinst_PROGRAMS = test-basic
test_basic_AM_CFLAGS = -Wno-error=format -Wno-error=format-extra-args
test_basic_SOURCES = test-basic.c
if EMBTEXTF_PROVIDE_LIBC
MAYBE_LIBC = ../src/libembtextf-libc.la
endif # EMBTEXTF_PROVIDE_LIBC
test_basic_LDADD = -lcunit $(MAYBE_LIBC) ../src/libembtextf.la
endif # WITH_CUINT

clean-local:
	-rm *.gcda *.gcno
