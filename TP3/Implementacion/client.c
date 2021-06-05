#include "client.h"

// Idea sacada de https://www.geeksforgeeks.org/socket-programming-cc/
int main()
{
    struct sockaddr_in server;

    char buffer[1024] = {0};

    int sockClient = connectToServer(&server);
    if (sockClient < 0)
    {
        return sockClient;
    }

    char bufferAUX[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &server.sin_addr, bufferAUX, sizeof(bufferAUX));
    printf("------------------------------------------------------------------------\n");
    printf("\nSe conecto al: %s:%d \n\n", bufferAUX, PORT);
    printf("Escriba EXIT para salir \n\n");
    printf("------------------------------- CLIENTE --------------------------------\n\n");

    char cleanBuffer[BUFFER_SIZE] = {0};
    char bufferSTDIN[BUFFER_SIZE] = {0};
    int exit = 0;

    while (!exit)
    {

        // Cerrar el cliente si el servidor fue cerrado
        // http://stefan.buettcher.org/cs/conn_closed.html
        struct pollfd pfd;
        pfd.fd = sockClient;
        pfd.events = POLLIN | POLLHUP | POLLRDNORM;
        pfd.revents = 0;

        if (poll(&pfd, 1, 100) > 0)
        {
            printf("\n------------------------------------------------------------------------\n\n");
            printf("Fallo la conexion al servidor ya que fue cerrado\n\n");
            printf("------------------------------------------------------------------------\n");
            exit = 1;
            continue;
        }
        ////////////////////////////////////////////////////

        scanf("%s", bufferSTDIN);
        if (strcmp(bufferSTDIN, "EXIT") == 0)
        {
            exit = 1;
        }
        strcat(bufferSTDIN, "\n");
        send(sockClient, bufferSTDIN, strlen(bufferSTDIN), 0);
        memcpy(bufferSTDIN, cleanBuffer, BUFFER_SIZE);
    }
    close(sockClient);
    return 0;
}

int connectToServer(struct sockaddr_in *server)
{
    int sockClient = 0;
    if ((sockClient = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\nSocket creation error");
        return -1;
    }

    //Prepare the sockaddr_in structure
    server->sin_family = AF_INET;
    server->sin_addr.s_addr = INADDR_ANY;
    server->sin_port = htons(PORT);

    if (connect(sockClient, (struct sockaddr *)server, sizeof(*server)) < 0)
    {
        perror("\nFallo la conexion del cliente\n");
        return -1;
    }
    return sockClient;
}
