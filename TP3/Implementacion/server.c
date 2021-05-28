//https://www.binarytides.com/socket-programming-c-linux-tutorial/

#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write

//#include<pthread.h> //for threading , link with lpthread

//void *connection_handler(void *);

#define PORT 8080
#define ENTENDIDO "entendido\n"
#define ENTENDIDO_SIZE 10

int compare(char* str1, char* str2);
void desafio2();

int main(int argc , char *argv[])
{
	int socket_desc , new_socket , c;// *new_sock
	int read_size;
	struct sockaddr_in server , client;
    //char *message;
    char * client_message;
    	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( PORT );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	c = sizeof(struct sockaddr_in);
    
	while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
		puts("------------- DESAFIO -------------");
	
		//Reply to the client
		puts("Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\n\n\n\nDeberán estar atentos a los easter eggs.\n\n\n\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra 'entendido\\n'\n");
		//write(new_socket , message , strlen(message));

        puts("¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?");

        while( (read_size = recv(new_socket , client_message , 2000 , 0) > 0 ) ){
            if (compare(client_message, ENTENDIDO))
            {
                //Segundo desafio
                desafio2();
                //puts("------------- DESAFIO -------------");
            }
	    }
        puts("sale");
	}
	
	if (new_socket<0)
	{
		perror("accept failed");
		return 1;
	}
	
	return 0;
}

int compare(char* str1, char* str2)
{
    int i= 0;
    for(; i< strlen(ENTENDIDO); i++){
        if(str1[i] != str2[i]){
            return 0;
        }
    }
    return 1;
}

void desafio2()
{
    puts("------------- DESAFIO -------------\n");
    puts("The Wire S1E5 5295 888 6288\n");
    puts("----- PREGUNTA PARA INVESTIGAR -----\n");
    puts("¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?\n");
}