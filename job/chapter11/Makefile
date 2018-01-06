PROGS = ghbn ghba gsbn

OBJS = ghbn.o ghba.o gsbn.o

all: ${PROGS}

ghbn: ghbn.o
	cc -o $@ ghbn.o -lunp
ghba: ghba.o
	cc -o $@ ghba.o -lunp
gsbn: gsbn.o
	cc -o $@ gsbn.o -lunp

clean:
	rm -f ${PROGS} ${OBJS} ${CLEANFILES}
