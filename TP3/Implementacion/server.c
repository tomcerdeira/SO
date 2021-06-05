//https://www.binarytides.com/socket-programming-c-linux-tutorial/
#include "server.h"

void (*desafios[CANT_DESAFIOS])() = {desafio1, desafio2, desafio3, desafio4, desafio5, desafio6, desafio7, desafio8, desafio9, desafio10, desafio11, desafio12, finDesafios};

char *respuestas[CANT_DESAFIOS] = {"entendido\n", "itba\n", "M4GFKZ289aku\n", "fk3wfLCm3QvS\n", "too_easy\n", ".RUN_ME\n", "K5n2UFfpFMUN\n", "BUmyYq5XxXGt\n", "u^v\\cdot \\left(v'\\cdot \\ln \\left(u\right)+v\\cdot \frac{u'}{u}\right)\\cdot y\n", "chin_chu_lan_cha\n", "gdb_rules\n", "normal\n"};

int main(int argc, char *argv[])
{
	int scoketDesc, newSocket, c; // *new_sock
	int readSize;
	struct sockaddr_in server, client;
	//char *message;
	char clientMessage[100] = {0};
	int numeroDesafio = 0;

	//Create socket
	scoketDesc = socket(AF_INET, SOCK_STREAM, 0);
	if (scoketDesc == -1)
	{
		printf("Could not create socket");
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	int enable = 1;
	if (setsockopt(scoketDesc, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		perror("setsockopt(SO_REUSEADDR) failed");
		return -1;
	}

	//Bind
	if (bind(scoketDesc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("bind failed");
		perror("ERROR");
		return -1;
	}

	//Listen
	listen(scoketDesc, 3);

	//Accept and incoming connection
	c = sizeof(struct sockaddr_in);

	while ((newSocket = accept(scoketDesc, (struct sockaddr *)&client, (socklen_t *)&c)))
	{
		system("clear");
		numeroDesafio = 9; ////////////////////////////////////////////////////////////////////////
		(*desafios[numeroDesafio])();
		while ((readSize = read(newSocket, clientMessage, 2000) > 0))
		{
			//clrscr();
			system("clear");
			(*desafios[numeroDesafio])();
			if (strcmp(clientMessage, respuestas[numeroDesafio]) == 0)
			{
				numeroDesafio++;
				system("clear");
				(*desafios[numeroDesafio])();
			}
			else
			{
				char buffer[100] = {0};
				sprintf(buffer, "Respuesta incorrecta: %s", clientMessage);
				puts(buffer);
				char buffer2[150] = {0};
				sprintf(buffer2, "Respuesta esperada: %s", respuestas[numeroDesafio]);
				puts(buffer2);
				int k1 = 0;
				while (buffer[k1] != 0)
				{
					buffer[k1++] = 0;
				}
			}

			int k = 0;
			while (clientMessage[k] != 0)
			{
				clientMessage[k++] = 0;
			}
		}

		if (newSocket < 0)
		{
			perror("accept failed");
			return -1;
		}
	}
	return 0;
}

void desafio1()
{
	puts(DESAFIO);

	//Reply to the client
	puts("Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\n\n\n\nDeberán estar atentos a los easter eggs.\n\n\n\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra 'entendido\\n'\n");
	puts(PREGUNTA);
	puts("¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?");
}

void desafio2()
{
	puts(DESAFIO);
	puts("The Wire S1E5 5295 888 6288\n");
	puts(PREGUNTA);
	puts("¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?\n");
	/// respuesta : itba
}

void desafio3()
{
	puts(DESAFIO);
	puts("https://ibb.co/tc0Hb6w\n");
	puts(PREGUNTA);
	puts("¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?\n");
	// M4GFKZ289aku
}

void desafio4()
{
	puts(DESAFIO);
	puts("EBADF...\nwrite: Bad file descriptor\n");
	write(WRITE_EBADF, ".................................................................La respuesta es: fk3wfLCm3QvS", strlen(".................................................................La respuesta es: fk3wfLCm3QvS"));
	puts(PREGUNTA);
	puts("¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?\n");
	//fk3wfLCm3QvS
}
void desafio5()
{
	puts(DESAFIO);
	puts("respuesta = strings:37\n");
	//too_easy
	puts(PREGUNTA);
	puts("¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?\n");
}

void desafio6()
{
	puts(DESAFIO);
	puts(".data .bss .comment ? .shstrtab .symtab .strtab\n");
	//.RUN_ME
	puts(PREGUNTA);
	puts("Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?\n");
}

void desafio7()
{
	puts(DESAFIO);
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
			write(STDOUT_FILENO, toPrint + k++, 1);
		}
		else
		{
			char toP = (char)(rand() % CANT_CHARACTER_USED + 32);
			write(STDERR_FILENO, &toP, 1);
			// + 33 es por que los primeros 32 ascii no son caracters https://elcodigoascii.com.ar/
		}
	}
	puts(PREGUNTA);
	puts("¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?\n");
	//K5n2UFfpFMUN
}

void desafio8()
{
	puts(DESAFIO);
	puts("¿?\n");
	/// lo de seleccionar y que muestre la respuesta
	// https://www.programmersought.com/article/2256659653/
	printf("\033[0;30m"); //\033[0;30m
	printf("La respuesta es: BUmyYq5XxXGt \n");
	printf("\033[0m");
	// \033[background color; font color m represents a color font of a certain background color that you choose to output from here.
	// \033[0m represents the end of the custom color, restore the system default

	puts(PREGUNTA);
	puts("¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?\n");
	//BUmyYq5XxXGt
}

void desafio9()
{
	puts(DESAFIO);
	puts("Latexme\nSi\n\\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\frac{u'}{u})\nentonces\n y=\n");
	puts(PREGUNTA);
	puts("sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?\n");
	//u^v\cdot \left(v'\cdot \ln \left(u\right)+v\cdot \frac{u'}{u}\right)\cdot y
}

void desafio10()
{
	puts(DESAFIO);
	puts("quine\n\n");

	//Compilar el quine.c
	system("gcc -Wall -o quine quine.c");
	// Busco en el PWD si esta el archivo
	DIR *dp;
	int pid = -1;
	int fd[2] = {-1, -1};
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
		puts("¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde.\n");

		if (pipe(fd) < 0)
		{
			perror("ERROR al crear pipe (desafio10)");
			return;
		}

		if ((pid = fork()) == 0)
		{
			close(fd[0]);						// el hijo solo escribe
			if (dup2(fd[1], STDOUT_FILENO) < 0) //redirecciono la salida del STDOUT al pipe (eso intento)
			{
				perror("Error al supear la salida");
			}
			char *quine[] = {"./quine", NULL}; //antes del exec hay que forkear si no te pisa la imagen del server
			int resExec = execvp(quine[0], quine);
			if (resExec < 0)
			{
				perror("ERROR en Execv (desafio10)");
				return;
			}
		}

		close(fd[1]); // el padre solo lee
		char buffer[1024] = {0};
		read(fd[0], buffer, 1024);

		//Ahora deberia ver si lo que se escribio en el fd es igual al programa en si
		char chSalida;
		int bufferIndex = 0;
		FILE *fp;

		int different = 0;

		fp = fopen("quine.c", "r"); // read mode

		while ((chSalida = (char)fgetc(fp)) != EOF && (buffer[bufferIndex]) != EOF && bufferIndex < 1024)
		{
			if (chSalida != buffer[bufferIndex++])
			{
				//printf("Leido del file: %c Leido del pipe: %c", chSalida, buffer[bufferIndex - 1]);
				different = 1;
			}
		}
		fclose(fp);

		if (!different)
		{
			puts("La respuesta es chin_chu_lan_cha\n");
		}
		else
		{
			puts("-- Codigo del programa --\n"); //Codigo de quine
			char chAux;
			FILE *fpAux;
			fpAux = fopen("quine.c", "r");
			while ((chAux = fgetc(fpAux)) != EOF)
			{
				printf("%c", chAux);
			}

			puts("-- Salida del programa --\n"); //Salida de quine
			bufferIndex = 0;
			while ((buffer[bufferIndex]) != EOF && bufferIndex < 1024)
			{
				printf("%c", buffer[bufferIndex++]);
			}
			printf("\n");
		}
		if (pid > 0)
		{
			waitpid(pid, NULL, 0);
		}

		//Habria que hacer la logica ahora de si son distinto o no
	}

	puts(PREGUNTA);
	puts("¿Cuáles son las características del protocolo SCTP?\n");
	if (fd[0] != -1)
	{
		close(fd[0]);
	}

	// // hacer programa quine.c
	// //chin_chu_lan_cha
}

int gdbme()
{
	return 0;
}

void desafio11()
{
	puts(DESAFIO);
	puts("b gdbme y encontrá el valor mágico\n");
	// SI FALLA
	if (gdbme() != 0x12345678)
	{
		puts("ENTER para reintentar\n");
	}
	else
	{
		puts("La respuesta es gdb_rules\n");
	}

	puts(PREGUNTA);
	puts("¿Qué es un RFC?\n");
	//gdb_rules
}

double drand() /* uniform distribution, (0..1] */
{
	return (rand() + 1.0) / (RAND_MAX + 1.0);
}

double randomNormal()
/* normal distribution, centered on 0, std dev 1 */
{
	return sqrt(-2 * log(drand())) * cos(2 * PI * drand());
}

void desafio12()
{
	puts(DESAFIO);
	puts("Me conoces\n");
	double rands[1000];
	int i = 0;
	for (i = 0; i < 1000; i++)
	{
		rands[i] = 1.0 + 0.5 * randomNormal();
		printf("%g ", rands[i]);
	}

	// imprimir valors para una distribucion normal
	puts("\n");
	puts(PREGUNTA);
	puts("¿Fue divertido?\n");
	//normal
}

void finDesafios()
{
	puts("Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto\n");
}
