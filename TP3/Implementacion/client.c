#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define PORT 8080

int main()
{
    int sockClient = 0, valread;
    struct sockaddr_in server;

    char buffer[1024] = {0};
    if ((sockClient = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    // if(inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr)<=0)
    // {
    //     printf("\nInvalid address/ Address not supported \n");
    //     return -1;
    // }

    if (connect(sockClient, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("\nFallo la conexion del cliente\n");
        return -1;
    }
    char bufferAUX[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &server.sin_addr, bufferAUX, sizeof(bufferAUX));
    printf("Se conecto al: %s:%d \n\n", bufferAUX, PORT);
    printf("Escriba EXIT para salir \n\n");

    char cleanBuffer[BUFFER_SIZE] = {0};
    char bufferSTDIN[BUFFER_SIZE] = {0};
    int exit = 0;

    while (!exit)
    {
        // http://stefan.buettcher.org/cs/conn_closed.html
        // struct pollfd pfd;
        // pfd.fd = fd;
        // pfd.events = POLLIN | POLLHUP | POLLRDNORM;
        // pfd.revents = 0;
        // char aux[32];
        // if (poll(&pfd, 1, 100) > 0 && recv(sockClient, aux, sizeof(aux), MSG_PEEK | MSG_DONTWAIT) == 0)
        // {
        //     // if recv returns zero, that means the connection has been closed:
        //     // kill the child process
        //     // kill(childProcess, SIGKILL);
        //     // waitpid(childProcess, &status, WNOHANG);
        //     // close(fd);
        //     // do something else, e.g. go on vacation
        //     printf("entro\n");
        //     exit = 1;
        //     continue;
        // }
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

    // valread = read(sockClient, buffer, 1024);
    // printf("%s\n", buffer);
    return 0;
}
