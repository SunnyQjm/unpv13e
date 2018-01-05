PROGS = tcpcli02 tcpserv02

OBJS = tcpcli02.o tcpserv02.o

all: ${PROGS}

tcpserv02: tcpserv02.o 
	cc -o $@ tcpserv02.o -lunp
tcpcli02: tcpcli02.o
	cc -o $@ tcpcli02.o -lunp

clean:
	rm -f ${PROGS} ${OBJS} ${CLEANFILES}
