run :
	./im

link : im.o io.o common.o log.o thread.o queue.o socket.o reactor.o
	gcc -o im im.o io.o common.o log.o thread.o queue.o socket.o reactor.o

im : im.c log.o 
	gcc -c im.c log.o

log : log.h log.c common.o io.o
	gcc -c log.h log.c common.o io.o

io : io.h io.c
	gcc -c io.h io.c

common : common.h 
	gcc -c common.h 

thread : thread.h thread.c common.h
	gcc -c thread.h thread.c common.h

queue : queue.h queue.c common.h
	gcc -c queue.h queue.c common.h

socket : socket.h socket.c common.h
	gcc -c socket.h socket.c common.h

reactor : reactor.h reactor.c common.h socket.h
	gcc -c reactor.h reactor.c common.h socket.h

#timers : timers.h timers.c reactor.h common.h
#	gcc -c timers.h timers.c reactor.h common.h

clear :
	rm -f *.o *.gch im ./logfile/*.log
	clear

clearlog :
	rm -f ./logfile/debug_* ./logfile/dump_* ./logfile/error_*
