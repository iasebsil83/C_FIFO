#executable
run: fifo.o prog.o
	gcc -Wall -o run prog.o fifo.o -O2
	rm -f *.o



#example program
prog.o: src/prog.c lib/fifo.h
	gcc -Wall -c src/prog.c -O2



#fifo library
fifo.o: lib/fifo.c lib/fifo.h
	gcc -Wall -c lib/fifo.c -O2
