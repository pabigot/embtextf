EMBTEXTF_ROOT ?= /opt/libembtextf

CPPFLAGS = -I$(EMBTEXTF_ROOT)/include
OPTCFLAGS = -g
LDFLAGS = -L$(EMBTEXTF_ROOT)/
LIBS = -lcunit -lembtextf
CFLAGS = -Wall -Werror -ansi -std=c99 -pedantic $(CPPFLAGS) $(OPTCFLAGS)

ifeq ($(ENABLE),1)
CPPFLAGS += -DEMBTEXTF_VUPRINTF_ENABLE_LONG=1 -DEMBTEXTF_VUPRINTF_ENABLE_INTPTR=1 -DEMBTEXTF_VUPRINTF_ENABLE_LONGLONG=1
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
