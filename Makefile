EMBTEXTF_ROOT ?= /opt/embtextf
include $(EMBTEXTF_ROOT)/Makefile.common

ifdef DEFAULT
CPPFLAGS += -DEMBTEXTF_VUPRINTF_ENABLE_DEFAULT=$(DEFAULT)
endif

SRC = \
  src/vuprintf.c \
  src/itoa.c src/utoa.c \
  src/ltoa.c src/ultoa.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

TARGET = libembtextf.a

all: $(TARGET)

libembtextf.a: $(OBJ)
	$(AR) rv $@ $^
ifdef SIZE
	$(SIZE) $@
endif # SIZE
doc:
	doxygen

.PHONY: astyle
ASTYLE_ARGS=--options=none --style=1tbs --indent=spaces=2 --indent-switches --pad-header
astyle:
	astyle $(ASTYLE_ARGS) -r '*.c' '*.h' '*.inc'

clean:
	-rm -f $(OBJ)
	-rm -f *.gcov

realclean: clean
	-rm -f $(DEP) $(TARGET)
	-rm -f *.gcda *.gcno
	-rm -f src/*.gcda src/*.gcno
	-rm -f tests/*.gcda tests/*.gcno
	-rm -rf html

.PHONY: coverage
coverage:
	$(MAKE) realclean \
	&& $(MAKE) -C tests realclean \
	&& $(MAKE) AUX_CFLAGS='-fprofile-arcs -ftest-coverage' all \
	&& $(MAKE) -C tests coverage
	for f in $(SRC:.c=) ; do ln -s $${f}.gcno; ln -s $${f}.gcda ; done
	$(GCOV) -a $(SRC)

.PHONY: test
test: all
	$(MAKE) -C tests realclean test

ifneq ($(MAKECMDGOALS:realclean=clean),clean)
-include $(DEP)
endif # make [real]clean
