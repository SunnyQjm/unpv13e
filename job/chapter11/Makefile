PROGS = ghbn ghba gsbn gsbp

OBJS = ghbn.o ghba.o gsbn.o gsbp.o

all: ${PROGS}

ghbn: ghbn.o
	cc -o $@ ghbn.o -lunp
ghba: ghba.o
	cc -o $@ ghba.o -lunp
gsbn: gsbn.o
	cc -o $@ gsbn.o -lunp
gsbp: gsbp.o
	cc -o $@ gsbp.o -lunp

clean:
	rm -f ${PROGS} ${OBJS} ${CLEANFILES}
