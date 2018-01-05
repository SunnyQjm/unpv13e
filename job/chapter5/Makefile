PROGS = tcpserv01 tcpcli01

OBJS = tcpserv01.o tcpcli01.o

all: ${PROGS}

tcpserv01: tcpserv01.o
	cc -o $@ tcpserv01.o -lunp
tcpcli01: tcpcli01.o
	cc -o $@ tcpcli01.o -lunp

clean:
	rm -f ${PROGS} ${OBJS} ${CLEANFILES}
