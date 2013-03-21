EMBTEXTF_ROOT ?= /opt/embtextf

CPPFLAGS = -I$(EMBTEXTF_ROOT)/include
OPTCFLAGS = -g
override LDFLAGS += -L$(EMBTEXTF_ROOT)/
LIBS = -lcunit -lembtextf
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
CFLAGS = -Wall -Werror -ansi -std=c99 -pedantic $(OPTCFLAGS)

# Explicitly exclude format errors as part of the test includes formats that appear incorrect when certain capabilities are not supported.
CFLAGS += -Wno-error=format -Wno-error=format-extra-args

ifdef DEFAULT
CPPFLAGS += -DEMBTEXTF_VUPRINTF_ENABLE_DEFAULT=$(DEFAULT)
endif

SRC = test-basic.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

TESTS = $(SRC:.c=)

test: $(TESTS)
	@for f in $(TESTS); do ./$$f ; done

test-basic: test-basic.o $(PSML_LIB)
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

clean:
	-rm -f $(OBJ)
	-rm -f *.gcov

realclean: clean
	-rm -f $(DEP) $(TESTS)
	-rm -f *.gcda *.gcno

coverage: realclean
	$(MAKE) OPTCFLAGS='-fprofile-arcs -ftest-coverage' LDFLAGS=-fprofile-arcs

%.d: %.c
	@set -e; rm -f $@; \
	 $(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	 sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	 rm -f $@.$$$$

include $(DEP)
