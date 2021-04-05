all:
	gcc -Wall -o includes includes.h 
	gcc -Wall -o slave slave.c
	gcc -Wall -o solve solve.c -lrt -pthread
	gcc -Wall -o vista vista.c -lrt -pthread
clean:
	rm solve slave vista includes
	rm ./output_solve
	rm /dev/shm//myMemoryObj
.PHONY: all clean

