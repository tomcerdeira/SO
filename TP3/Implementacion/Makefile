all: clean server client

server: server.o desafios.o
	gcc -o  server server.o desafios.o -Wall -lm

client: client.o
	gcc -o  client client.o -Wall

client.o: 
	gcc -c client.c -lm

desafios.o: 
	gcc -c desafios.c -lm

server.o: 
	gcc -c server.c -lm

clean: 
	rm -f server
	rm -f client
	rm -f *.o
	rm -f quine	
