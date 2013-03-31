EMBTEXTF_ROOT ?= /opt/embtextf
include $(EMBTEXTF_ROOT)/Makefile.common

ifdef DEFAULT
CPPFLAGS += -DENABLE_VUPRINTF_DEFAULT=$(DEFAULT)
endif

SRC = \
  src/vuprintf.c \
  src/libc.c \
  src/itoa.c \
  src/ltoa.c \
  src/lltoa.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

TARGET = lib/libembtextf.a

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(dir $@)
	$(AR) rv $@ $^
ifdef SIZE
	$(SIZE) -A $@ | grep '^.text'
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

ifeq ($(WITH_DEP),1)
ifneq ($(MAKECMDGOALS:realclean=clean),clean)
-include $(DEP)
endif # make [real]clean
endif # WITH_DEP
