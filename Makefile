CLANGFLAGS = -Weverything -Wno-padded -Wno-vla -Wno-double-promotion
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

PROGNAME = a

SRCDIR = src
INCDIR = inc
OBJDIR = obj

SRCS := $(wildcard ${SRCDIR}/*.c)
INCS := $(wildcard ${INCDIR}/*.h)
OBJS := ${SRCS:${SRCDIR}/%.c=${OBJDIR}/%.o}

INCFLAG = -I./${INCDIR}


all: ${PROGNAME} ${SRCS}

${PROGNAME}: ${OBJS}
	${CC} -o $@ ${OBJS} -pthread

${OBJS}: ${OBJDIR}/%.o : ${SRCDIR}/%.c
	${CC} -c $< -o $@ ${INCFLAG} ${CFLAGS}


.PHONY: clean

clean:
	rm -f ${OBJDIR}/*.o ./${PROGNAME}
