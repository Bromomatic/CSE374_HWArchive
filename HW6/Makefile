# Memory Management Makefile
# Author(s): 	Tianshu Bao, Shawn Stern
# Date:			2/17/2013
# Project: 		CSE 374, HW6 Memory Manager


bench: bench.o getmem.o freemem.o get_mem_stats.o print_heap.o
	gcc -Wall -g -o bench bench.o getmem.o freemem.o get_mem_stats.o print_heap.o

bench.o: bench.c mem.h
	gcc -Wall -g -c bench.c

getmem.o: getmem.c mem_impl.h mem.h
	gcc -Wall -g -c getmem.c

freemem.o: freemem.c mem_impl.h mem.h
	gcc -Wall -g -c freemem.c

get_mem_stats.o: get_mem_stats.c mem_impl.h mem.h
	gcc -Wall -g -c get_mem_stats.c

print_heap.o: print_heap.c mem_impl.h mem.h
	gcc -Wall -g -c print_heap.c

test:
	./bench

dist:
	tar -cvf hw6.tar bench.c freemem.c getmem.c get_mem_stats.c print_heap.c mem.h mem_impl.h svn.log README.txt Makefile

clean:
	rm -rf *.o bench