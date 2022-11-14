CFLAGS ?= -Wall -Wextra

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
	${CC} -o $@ ${OBJS} 

${OBJS}: ${OBJDIR}/%.o : ${SRCDIR}/%.c
	${CC} -c $< -o $@ ${CFLAGS} ${INCFLAG}


.PHONY: clean

clean:
	rm -f ${OBJDIR}/*.o ./${PROGNAME}
