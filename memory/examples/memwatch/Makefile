# Makefile for mtrace_test
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
CFLAGS  =  -g -ggdb -Werror -DMEMWATCH -DMEMWATCH_STDIO

memwatch_test.o : /home/antoine/work/c-practice/memory/leak.c
	${CC} ${CFLAGS} -c $< -o $@

memwatch.o : ./memwatch.c
	${CC} ${CFLAGS} -c $< -o $@


# linker

LINKER    := gcc
LDFLAGS    = 
LOADLIBES := 


# memwatch_test

memwatch_test : ./memwatch_test.o ./memwatch.o
	${LINKER} ${LDFLAGS} -o $@ $< ./memwatch.o ${LOADLIBES}

# target for making everything

.PHONY : all
all: memwatch_test


# target for removing all object files

.PHONY : tidy
tidy::
	@${RM} core ./memwatch_test.o ./memwatch.o *.log

# target for removing all object files

.PHONY : clean
clean:: tidy
	@${RM} memwatch_test


