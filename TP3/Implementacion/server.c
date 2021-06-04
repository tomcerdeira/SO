//https://www.binarytides.com/socket-programming-c-linux-tutorial/

#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>	   //write
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

// #include <windows.h>
//#include<conio.h> //clear// console

//#include<pthread.h> //for threading , link with lpthread

//void *connection_handler(void *);

#define PORT 8080
//#define ENTENDIDO "entendido\n"
#define ENTENDIDO_SIZE 10
#define CANT_DESAFIOS 12
#define CANT_CHARACTER_USED 123

int compare(char *str1, char *str2);
void desafio2();
void desafio3();
void desafio4();
void desafio5();
void desafio6();
void desafio7();
void desafio8();
void desafio9();
void desafio10();
void desafio11();
void desafio12();
void finDesafios();

void (*desafios[CANT_DESAFIOS])() = {desafio2, desafio3, desafio4, desafio5, desafio6, desafio7, desafio8, desafio9, desafio10, desafio11, desafio12, finDesafios};

char *respuestas[CANT_DESAFIOS] = {"entendido\n", "itba\n", "M4GFKZ289aku\n", "fk3wfLCm3QvS\n", "too_easy\n", ".RUN_ME\n", "K5n2UFfpFMUN\n", "BUmyYq5XxXGt\n", "u^v\\cdot \\left(v'\\cdot \\ln \\left(u\right)+v\\cdot \frac{u'}{u}\right)\\cdot y\n", "chin_chu_lan_cha\n", "gdb_rules\n", "normal\n"};

int main(int argc, char *argv[])
{
	int socket_desc, new_socket, c; // *new_sock
	int read_size;
	struct sockaddr_in server, client;
	//char *message;
	char client_message[100] = {0};
	int numero_desafio = 0;

	//Create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	//Bind
	if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("bind failed");
		perror("ERROR");
		return 1;
	}

	//Listen
	listen(socket_desc, 3);

	//Accept and incoming connection
	c = sizeof(struct sockaddr_in);

	while ((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)))
	{
			system("clear");
		puts("------------- DESAFIO -------------");

		//Reply to the client
		puts("Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\n\n\n\nDeberán estar atentos a los easter eggs.\n\n\n\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra 'entendido\\n'\n");
		puts("¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?");
		numero_desafio = 8;

		while ((read_size = read(new_socket, client_message, 2000) > 0))
		{
			//clrscr();
			system("clear");
			(*desafios[numero_desafio])();
			if (strcmp(client_message, respuestas[numero_desafio]) == 0)
			{	
				numero_desafio++;
			}
			// else if (strcmp(client_message, "\n") == 0) // Para reintentarlo en aquellos que lo requieren
			// {
			// 	(*desafios[numero_desafio])();
			// }
			else
			{
				char buffer[100] = {0};
				sprintf(buffer, "Respuesta incorrecta: %s", client_message);
				puts(buffer);
				char buffer2[100] = {0};
				sprintf(buffer2, "Respuesta esperada: %s", respuestas[numero_desafio]);
				puts(buffer2);
				int k1 = 0;
				while (buffer[k1] != 0)
				{
					buffer[k1++] = 0;
				}
			}
			int k = 0;
			while (client_message[k] != 0)
			{
				client_message[k++] = 0;
			}
		}

		if (new_socket < 0)
		{
			perror("accept failed");
			return 1;
		}
	}
	return 0;
}

// int compare(char* str1, char* str2)
// {
//     int i= 0;
//     for(; i< strlen(ENTENDIDO); i++){
//         if(str1[i] != str2[i]){
//             return 0;
//         }
//     }
//     return 1;
// }

void desafio2()
{
	puts("------------- DESAFIO -------------\n");
	puts("The Wire S1E5 5295 888 6288\n");
	puts("----- PREGUNTA PARA INVESTIGAR -----\n");
	puts("¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?\n");
	/// respuesta : itba
}

void desafio3()
{
	puts("------------- DESAFIO -------------\n");
	puts("https://ibb.co/tc0Hb6w\n");
	puts("----- PREGUNTA PARA INVESTIGAR -----\n");
	puts("¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?\n");
	// M4GFKZ289aku
}

void desafio4()
{
	puts("------------- DESAFIO -------------\n");
	puts("EBADF...\nwrite: Bad file descriptor\n");
	puts("----- PREGUNTA PARA INVESTIGAR -----\n");
	puts("¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?\n");
	//fk3wfLCm3QvS
}
void desafio5()
{
	puts("------------- DESAFIO -------------\n");
	puts("respuesta = strings:277\n");
	//too_easy
	puts("----- PREGUNTA PARA INVESTIGAR -----\n");
	puts("¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?\n");
}

void desafio6()
{
	puts("------------- DESAFIO -------------\n");
	puts(".data .bss .comment ? .shstrtab .symtab .strtab\n");
	//.RUN_ME
	puts("----- PREGUNTA PARA INVESTIGAR -----\n");
	puts("Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?\n");
}

void desafio7()
{
	puts("------------- DESAFIO -------------\n");
	puts("Filter error\n");
	int k = 0;
	int i = strlen("La respuesta es: K5n2UFfpFMUN");
	char *toPrint = "La respuesta es: K5n2UFfpFMUN";
	srand(time(NULL));
	int randNumber = 0;
	while (k < i)
	{
		randNumber = rand() % 7;
		if (randNumber == 0)
		{
			write(STDOUT_FILENO, toPrint+k++, 1);
		}
		else
		{
			char toP = (char )(rand() % CANT_CHARACTER_USED+ 32);
			write(STDERR_FILENO,&toP, 1);
			// + 33 es por que los primeros 32 ascii no son caracters https://elcodigoascii.com.ar/
		}
	}
	puts("----- PREGUNTA PARA INVESTIGAR -----\n");
	puts("¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?\n");
	//K5n2UFfpFMUN
}

void desafio8()
{
	puts("------------- DESAFIO -------------\n");
	puts("¿?\n");
	/// lo de seleccionar y que muestre la respuesta
	// https://www.programmersought.com/article/2256659653/
	printf("\033[0;30m"); //\033[0;30m
	printf("La respuesta es: BUmyYq5XxXGt \n");
	printf("\033[0m");
	// \033[background color; font color m represents a color font of a certain background color that you choose to output from here.
	// \033[0m represents the end of the custom color, restore the system default

	puts("----- PREGUNTA PARA INVESTIGAR -----\n");
	puts("¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?\n");
	//BUmyYq5XxXGt
}

void desafio9()
{
	puts("------------- DESAFIO -------------\n");
	puts("Latexme\nSi\n\\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\frac{u'}{u})\nentonces\n y=\n");
	puts("----- PREGUNTA PARA INVESTIGAR -----\n");
	puts("sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?\n");
	//u^v\cdot \left(v'\cdot \ln \left(u\right)+v\cdot \frac{u'}{u}\right)\cdot y
}

void desafio10()
{
	puts("------------- DESAFIO -------------\n");
	puts("quine\n\n");

	// Intento compilar el quine.c
	// int pid2=1;
	// if((pid2=fork()) == 0){
	// 		char *args[] = {"./gcc -Wall -o quine quine.c", NULL};
				
	// 		if (system(args[0], args) < 0)
	// 		{
	// 			perror("ERROR en Execv (desafio10)");
	// 			return;
	// 		}
	// 	}
	system("gcc -Wall -o quine quine.c");
	// Busco en el PWD si esta el archivo
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if ((dp = opendir(".")) == NULL)
	{
		printf("cannot open directory\n");
		return;
	}
	int found = 0;
	while ((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name, &statbuf);
		if (S_ISREG(statbuf.st_mode))
		{
			if (strcmp("quine.c", entry->d_name) == 0)
			{
				found = 1;
			}
		}
	}
	closedir(dp);

	// Si el archivo NO esta, imprimo y corto
	if (!found)
	{
		puts("\n");
		puts("ENTER para reintentar\n");
	}
	else
	{
		// Si el archivo esta, tengo que ver si hace lo que tiene que hacer
		puts("quine\n¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde.\n");

		int fd[2];
		if (pipe(fd) < 0)
		{
			perror("ERROR al crear pipe (desafio10)");
			return;
		}
		
		int pid = -1;
		if((pid=fork()) == 0){
			if(dup2(fd[1],STDOUT_FILENO)<0)//redirecciono la salida del STDOUT al pipe (eso intento)
			{
				perror("Error al supear la salida");
			} 
			char *quine[] = {"./quine", NULL};  //antes del exec hay que forkear si no te pisa la imagen del server
			int resExec = execvp(quine[0], quine);
			if (resExec < 0)
			{
				perror("ERROR en Execv (desafio10)");
				return;
			}
		}
	
		

		char buffer[1024]={0};
		read(fd[0],buffer,1024);
	
		
		// //Ahora deberia ver si lo que se escribio en el fd es igual al programa en si
		char chSalida;
		int bufferIndex = 0;
		FILE *fp;

		int different = 0;

		fp = fopen("quine.c", "r"); // read mode
	
		while ((chSalida= (char)fgetc(fp)) != EOF && (buffer[bufferIndex]) != EOF && bufferIndex<1024)
		{
			if (chSalida !=buffer[bufferIndex++])
			{
				printf("Leido del file: %c Leido del pipe: %c",chSalida,buffer[bufferIndex-1]);
				different = 1;
			}
		}
		fclose(fp);

		if(!different){
			puts("La respuesta es chin_chu_lan_cha\n");		
		}

		//Habria que hacer la logica ahora de si son distinto o no
	}

	//SI HACE LO QUE TIENE QUE HACER

	puts("----- PREGUNTA PARA INVESTIGAR -----\n");
	puts("¿Cuáles son las características del protocolo SCTP?\n");
	// // hacer programa quine.c
	// //chin_chu_lan_cha
}

void desafio11()
{
	puts("------------- DESAFIO -------------\n");
	puts("b gdbme y encontrá el valor mágico\n");
	// SI FALLA
	//puts("ENTER para reintentar\n");
	puts("----- PREGUNTA PARA INVESTIGAR -----\n");
	puts("\n");
	//gdb_rules
}

void desafio12()
{
	puts("------------- DESAFIO -------------\n");
	puts("Me conoces\n");
	// imprimir valors para una distribucion normal
	puts("----- PREGUNTA PARA INVESTIGAR -----\n");
	puts("¿Fue divertido?\n");
	//normal
}

void finDesafios()
{
	puts("Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto\n");
}
