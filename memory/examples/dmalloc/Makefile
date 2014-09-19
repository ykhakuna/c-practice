# Makefile for dmalloc_test
#
# THIS SOFTWARE IS NOT COPYRIGHTED
#
# MontaVista Software, Inc. offers the following for use in the public
# domain.  MontaVista makes no warranty with regard to the software or
# its performance and the user accepts the software "AS IS" with all faults.
#
# MontaVista disclaims any warranties, express or implied, with regard to
# to this software including but not limited to the warranties
# of merchantability and fitness for a particular purpose.
#

# C compiler

CC     := gcc
CFLAGS  =  -g -ggdb -Wall -Werror -DDMALLOC

dmalloc_test.o : ../tests/my_test.c
	${CC} ${CFLAGS} -c $< -o $@
# linker

LINKER    := gcc
LDFLAGS    = 
LOADLIBES := -ldmalloc


# dmalloc_test

dmalloc_test : ./dmalloc_test.o
	${LINKER} ${LDFLAGS} dmalloc_test.o -o $@ ${LOADLIBES}

# target for making everything

.PHONY : all
all: dmalloc_test


# target for removing all object files

.PHONY : tidy
tidy::
	@${RM} core ./dmalloc_test.o

# target for removing all object files

.PHONY : clean
clean:: tidy
	@${RM} dmalloc_test


