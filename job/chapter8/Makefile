PROGS = udpserv01 udpcli01

OBJS = udpserv01.o udpcli01.o

all: ${PROGS}

udpcli01: udpcli01.o 
	cc -o $@ udpcli01.o -lunp
udpserv01: udpserv01.o
	cc -o $@ udpserv01.o -lunp

clean:
	rm -f ${PROGS} ${OBJS} ${CLEANFILES}
