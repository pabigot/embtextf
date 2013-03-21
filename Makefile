EMBTEXTF_ROOT ?= /opt/embtextf
OPT_CFLAGS = -g -Os -ffunction-sections -fdata-sections
WARN_CFLAGS = -Wall -Werror -ansi -std=c99 -pedantic 
CPPFLAGS = -I$(EMBTEXTF_ROOT)/include
CPPFLAGS += -I$(EMBTEXTF_ROOT)/src
CPPFLAGS += $(AUX_CPPFLAGS)
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
GCOV = $(CROSS_COMPILE)gcov
CFLAGS = $(WARN_CFLAGS) $(OPT_CFLAGS) $(AUX_CFLAGS)

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
	$(CROSS_COMPILE)size $@
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
	&& $(MAKE) WITH_COVERAGE=1 EXPOSE_INTERNALS=1 all \
	&& $(MAKE) -C tests coverage
	for f in $(SRC:.c=) ; do ln -s $${f}.gcno; ln -s $${f}.gcda ; done
	$(GCOV) -a $(SRC)

%.d: %.c
	@set -e; rm -f $@; \
	 $(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	 sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	 rm -f $@.$$$$

ifneq ($(MAKECMDGOALS:realclean=clean),clean)
-include $(DEP)
endif # make [real]clean
