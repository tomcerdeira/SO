all: clean server

server: server.o
	gcc -o  server server.o -Wall -lm

server.o: 
	gcc -c server.c -lm

clean: 
	rm -f server *.o
	rm -f quine	
