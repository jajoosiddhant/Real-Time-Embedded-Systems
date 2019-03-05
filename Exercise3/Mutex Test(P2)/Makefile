INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS= 
CFLAGS= -O3 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= -lpthread -lrt

PRODUCT=mutex_test

HFILES=
CFILES= mutex_test.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${PRODUCT} ${GARBAGE}

mutex_test:	mutex_test.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ mutex_test.o $(LIBS)

depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<

