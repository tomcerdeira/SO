all:
	gcc -Wall -o includes includes.h -pthread
	gcc -Wall -o slave slave.c
	gcc -Wall -o solve solve.c -lrt -pthread
	gcc -Wall -o vista vista.c -lrt -pthread
clean:
	rm solve slave
	rm ../../dev/shm//myMemoryObj
.PHONY: all clean

