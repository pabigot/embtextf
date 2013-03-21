EMBTEXTF_ROOT ?= /opt/embtextf
include $(EMBTEXTF_ROOT)/Makefile.common

LDFLAGS += -L$(EMBTEXTF_ROOT)/
LIBS = -lcunit -lembtextf

ifneq ($(WITH_GCC),0)
# Explicitly exclude format errors as part of the test includes formats that appear incorrect when certain capabilities are not supported.
CFLAGS += -Wno-error=format -Wno-error=format-extra-args
endif # WITH_GCC 

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
	$(MAKE) AUX_CFLAGS='-fprofile-arcs -ftest-coverage' AUX_LDFLAGS=-fprofile-arcs

ifneq ($(MAKECMDGOALS:realclean=clean),clean)
-include $(DEP)
endif # make [real]clean
