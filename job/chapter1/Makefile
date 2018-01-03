PROGS = daytimecli daytimeserv

OBJS = daytimecli.o daytimeserv.o

all: ${PROGS}

daytimecli: daytimecli.o
	cc -o $@ daytimecli.o -lunp
daytimeserv: daytimeserv.o
	cc -o $@ daytimeserv.o -lunp

clean:
	rm -f ${PROGS} ${OBJS} ${CLEANFILES}
