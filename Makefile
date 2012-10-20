EMBTEXTF_ROOT ?= /opt/embtextf
OPTCFLAGS = -g -O
CPPFLAGS = -I$(EMBTEXTF_ROOT)/include
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
CFLAGS = -Wall -Werror -ansi -std=c99 -pedantic $(OPTCFLAGS) $(CPPFLAGS)

ifeq ($(ENABLE),1)
CPPFLAGS += -DEMBTEXTF_VUPRINTF_ENABLE_LONG=1 -DEMBTEXTF_VUPRINTF_ENABLE_INTPTR=1 -DEMBTEXTF_VUPRINTF_ENABLE_LONGLONG=1
endif

SRC = src/vuprintf.c src/uprintf.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

TARGET = libembtextf.a

all: $(TARGET)

msp430:
	make CROSS_COMPILE=msp430- clean all

libembtextf.a: $(OBJ)
	$(AR) rv $@ $^

doc:
	doxygen

.PHONY: astyle
ASTYLE_ARGS=--options=none --style=1tbs --indent=spaces=2 --indent-switches --pad-header
astyle:
	astyle $(ASTYLE_ARGS) -r '*.c' '*.h'

clean:
	-rm -f $(OBJ)
	-rm -f *.gcov

realclean: clean
	-rm -f $(DEP) $(TARGET)
	-rm -f *.gcda *.gcno
	-rm -rf html

coverage: realclean
	$(MAKE) OPTCFLAGS='-fprofile-arcs -ftest-coverage' 

%.d: %.c
	@set -e; rm -f $@; \
	 $(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	 sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	 rm -f $@.$$$$

include $(DEP)
