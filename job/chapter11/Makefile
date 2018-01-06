PROGS = ghbn 

OBJS = ghbn.o

all: ${PROGS}

ghbn: ghbn.o
	cc -o $@ ghbn.o -lunp

clean:
	rm -f ${PROGS} ${OBJS} ${CLEANFILES}
