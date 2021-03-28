#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>

#define MAX_PROCESSES 5

int main(int argc, char *argv[])
{
    int cantFiles = argc - 1;
    int i = 1;
    // for (; i <= cantFiles; i++)
    // { //chequear
    //     if (!strcmp(argv[i], ".cnf"))
    //     {
    //         printf("Enviar solamente archivos .cnf \n "); // o perror?
    //         abort();
    //     }
    // }

    int fd_work[MAX_PROCESSES][2]; // par Master- slave --> Master escribe y slave lee
    int fd_sols[MAX_PROCESSES][2]; // Master lee lo que los hijos escriben

    // Logica creacion de los pipes
    for (i = 0; i < MAX_PROCESSES; i++) //VER SI SE PUEDE MEJORAR, Habria que cerrar los anteriores si falla?
    {                                   // Habria que cerrar los fd que el padre no usa? Sea el de escritura o el de lectura?
        if (pipe(fd_work[i]) != 0 && pipe(fd_sols[i]) != 0)
        {
            perror("Pipe error: ");
            abort();
        }
    }

    int processes[MAX_PROCESSES];
    // Logica de los hijos
    for (i = 0; i < MAX_PROCESSES; i++)
    {
        if ((processes[i] = fork()) == 0)
        {
            int j = 0;
            for (; j < MAX_PROCESSES; j++)
            { // Cerramos los pipes ajenos a este hijo.
                if (j != i)
                {
                    close(fd_work[j][0]);
                    close(fd_work[j][1]);
                    close(fd_sols[j][0]);
                    close(fd_sols[j][1]);
                }
            }

            close(fd_work[i][1]);              // --> El hijo no escribe aca
            close(fd_sols[i][0]);              // --> El hijo no lee aca
            dup2(fd_work[i][0], STDIN_FILENO); // Redireccionamos la entrada del hijo al nuevo pipe
                                               //       dup2(fd_sols[i][1], STDOUT_FILENO); // Redireccionamos la salida del hijo al padre

            char **params = {NULL};
            int res_execv = execv("slave ", params);

            //int res_execv = execv("./slave ", &argv[i + 1]); //// --> Completar con args
            if (res_execv < 0)
            {
                printf(argv[i + 1]);
                printf("\n");
                perror("Execv error con valor errno");
                abort();
            }
        }
    }

    // Logica del padre para leer y escribir tareas.
    // fd_set fd_slaves;
    // for (i = 0; i < MAX_PROCESSES; i++)
    // {
    //     FD_SET(fd_sols[i][0], &fd_slaves); // Llenamos el set de fd en los que el padre va a recibir las resps.
    // }

    // while (cantFiles > 0)
    // {
    //     int res_select = select(1, &fd_slaves, NULL, NULL, NULL); // timeval????
    //     if (res_select < 0)
    //     {
    //         perror("Select error: ");
    //         abort();
    //     }else if(res_select){
    //         for (i = 0; i < MAX_PROCESSES; i++)
    //         {
    //             if (FD_ISSET(fd_sols[i][0], &fd_slaves))
    //             {

    //                 /* code */
    //             }

    //         }

    //     }

    // }
    return 0;
}