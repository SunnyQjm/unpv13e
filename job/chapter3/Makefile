PROGS = byteorder 

OBJS = byteorder.o

all: ${PROGS}

byteorder: byteorder.o
	cc -o $@ byteorder.o -lunp

clean:
	rm -f ${PROGS} ${OBJS} ${CLEANFILES}
