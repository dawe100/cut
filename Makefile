CLANGFLAGS = -Weverything -Wno-padded -Wno-vla -Wno-double-promotion -Wno-disabled-macro-expansion
GCCFLAGS = -Wall -Wextra

ifeq (${CC}, gcc)
	CFLAGS = ${GCCFLAGS}
else 
	ifeq (${CC}, clang)
		CFLAGS = ${CLANGFLAGS}
	else
		CFLAGS = 
	endif
endif

PROGNAME = cut

SRCDIR = src
INCDIR = inc
OBJDIR = obj
TESTDIR = test

SRCS := $(wildcard ${SRCDIR}/*.c)
INCS := $(wildcard ${INCDIR}/*.h)
OBJS := ${SRCS:${SRCDIR}/%.c=${OBJDIR}/%.o}

INCFLAG = -I./${INCDIR}


all: ${PROGNAME} ${SRCS}

${PROGNAME}: ${OBJS}
	${CC} -o $@ ${OBJS} -pthread

${OBJS}: ${OBJDIR}/%.o : ${SRCDIR}/%.c | mkdir
	${CC} -c $< -o $@ ${INCFLAG} ${CFLAGS}

mkdir:
	@mkdir -p obj

test: test_kolejki

test_kolejki: ${TESTDIR}/Kolejka_test.c
	${CC} -o test_kolejki ${TESTDIR}/Kolejka_test.c src/Kolejka.c ${INCFLAG} ${CFLAGS}	


.PHONY: clean

clean:
	rm -f ${OBJDIR}/*.o ./${PROGNAME}
