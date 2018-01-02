PROGS = daytimecli

OBJS = daytimecli.o

all: ${PROGS}

daytimecli: daytimecli.o
	cc -o $@ daytimecli.o -lunp

clean:
	rm -f ${PROGS} ${OBJS} ${CLEANFILES}
