//https://www.binarytides.com/socket-programming-c-linux-tutorial/
#include "server.h"

void (*desafios[CANT_DESAFIOS])() = {desafio1, desafio2, desafio3, desafio4, desafio5, desafio6, desafio7, desafio8, desafio9, desafio10, desafio11, desafio12, finDesafios};

char *respuestas[CANT_DESAFIOS] = {"entendido\n", "itba\n", "M4GFKZ289aku\n", "fk3wfLCm3QvS\n", "too_easy\n", ".RUN_ME\n", "K5n2UFfpFMUN\n", "BUmyYq5XxXGt\n", "u^v\n", "chin_chu_lan_cha\n", "gdb_rules\n", "normal\n"};

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

	while ((newSocket = accept(scoketDesc, (struct sockaddr *)&client, (socklen_t *)&c)) && numeroDesafio < CANT_DESAFIOS)
	{
		system("clear");
		numeroDesafio = 5; ////////////////////////////////////////////////////////////////////////
		(*desafios[numeroDesafio])();
		while ((readSize = read(newSocket, clientMessage, 2000) > 0) && numeroDesafio < CANT_DESAFIOS)
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
	close(scoketDesc);
	return 0;
}
