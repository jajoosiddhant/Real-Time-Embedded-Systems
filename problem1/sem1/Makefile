INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
CFILES= sem1.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	sem1

clean:
	-rm -f *.o *.d
	-rm -f sem1

sem1: sem1.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o -lm -lpthread

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
