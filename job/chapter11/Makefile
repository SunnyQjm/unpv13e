PROGS = ghbn ghba

OBJS = ghbn.o ghba.o

all: ${PROGS}

ghbn: ghbn.o
	cc -o $@ ghbn.o -lunp
ghba: ghba.o
	cc -o $@ ghba.o -lunp

clean:
	rm -f ${PROGS} ${OBJS} ${CLEANFILES}
