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
#include <limits.h>
#include <string.h>

#define MAX_PROCESSES 1

int fd_work[MAX_PROCESSES][2]; // par Master- slave --> Master escribe y slave lee
int fd_sols[MAX_PROCESSES][2]; // Master lee lo que los hijos escriben

// void check_format(int cantFiles, char files[], char *format);
void prepare_fd_set(int *max_fd1, fd_set *fd_slaves1);

int main(int argc, char *argv[])
{
    // Disable buffering on stdout
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, 0, _IONBF, 0);

    int cantFiles = argc - 1;
    int i = 1;

    // check_format(cantFiles, argv + 1, ".cnf");

    // Logica creacion de los pipes
    for (i = 0; i < MAX_PROCESSES; i++) //VER SI SE PUEDE MEJORAR, Habria que cerrar los anteriores si falla?
    {                                   // Habria que cerrar los fd que el padre no usa? Sea el de escritura o el de lectura?
        if (pipe(fd_work[i]) != 0)
        {
            perror("Pipe error: ");
            abort();
        }
        if (pipe(fd_sols[i]) != 0)
        {
            perror("Pipe error: ");
            abort();
        }
    }

    int processes[MAX_PROCESSES];
    int cant_sol_process[MAX_PROCESSES];

    // Logica de los hijos
    for (i = 0; i < MAX_PROCESSES; i++)
    {
        cant_sol_process[i] = 0;
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

            close(fd_work[i][1]); // --> El hijo no escribe aca
            close(fd_sols[i][0]); // --> El hijo no lee aca

            if (dup2(fd_work[i][0], STDIN_FILENO) < 0)
            { // Redireccionamos la entrada del hijo al nuevo pipe
                perror("Dup 1");
                abort();
            }
            if (dup2(fd_sols[i][1], STDOUT_FILENO) < 0)
            { // Redireccionamos la salida del hijo al padre
                perror("Dup 2");
                printf("Hijo pid %d valor i %d  \n ", getpid(), i);
                abort();
            }

            //  printf("DESPUES DEL DUP\n");

            //char *const params[] = {"slave", argv[i + 1], NULL};
            char *const params[] = {"slave", NULL};
            int res_execv = execv(params[0], params);
            if (res_execv < 0)
            {
                perror("Execv error");
                abort();
            }
        }
        else if (processes[i] < 0)
        {
            perror("Fork");
        }
    }

    char files_concat[256] = {'\0'};
    // Mandamos archivos a los hijos
    for (i = 0; i < MAX_PROCESSES; i++)
    {
        strcpy(files_concat, argv[i + 1]);
        strcat(files_concat, "\n");
        strcat(files_concat, argv[i + 2]);
        strcat(files_concat, "\n");
        printf("Padre leyo: %s \n", files_concat);
        write(fd_work[i][1], files_concat, strlen(files_concat) + 1);
    }

    sleep(1);
    // Logica del padre para leer y escribir tareas.
    fd_set fd_slaves;
    int max_fd = 0;

    while (cantFiles > 0)
    {
        char buf[265] = {'\0'};

        prepare_fd_set(&max_fd, &fd_slaves);

        int res_select = select(max_fd, &fd_slaves, NULL, NULL, NULL);

        if (res_select < 0)
        {
            perror("Select error: ");
            abort();
        }
        else if (res_select)
        {
            // printf("Leo %d bytes \n", res_select);
            // printf(argv[argc - cantFiles]);
            // printf("\n");

            for (i = 0; i < MAX_PROCESSES; i++)
            {
                if (FD_ISSET(fd_sols[i][0], &fd_slaves))
                {
                    cant_sol_process[i]++;
                    read(fd_sols[i][0], buf, sizeof(buf));
                    printf(buf);
                    printf("\n");

                    // if (cant_sol_process[i] >= 1 && cantFiles > 0)
                    // {
                    // Mandamos otra tarea
                    write(fd_work[i][1], argv[argc - cantFiles], strlen(argv[argc - cantFiles]));
                    // }
                    cantFiles--;
                    // logica memcompartida
                }
            }
            printf("----------------------------------------------- \n");
        }
        else
        {
            printf("Select vale 0 \n");
        }
    }

    //Aca cerrar los pipes
    for (i = 0; i < MAX_PROCESSES; i++)
    {
        close(fd_work[i][0]);
        waitpid(processes[i], NULL, 0);
    }

    return 0;
}

void prepare_fd_set(int *max_fd1, fd_set *fd_slaves1)
{
    fd_set fd_slaves;
    int max_fd = 0;

    FD_ZERO(&fd_slaves);

    int i = 0;
    for (; i < MAX_PROCESSES; i++)
    {
        FD_SET(fd_sols[i][0], &fd_slaves); // Llenamos el set de fd en los que el padre va a recibir las resps.
        if (fd_sols[i][0] > max_fd)
        {
            max_fd = fd_sols[i][0] + 1;
        }
    }

    *max_fd1 = max_fd;
    *fd_slaves1 = fd_slaves;
}

// // Validacion del tipo de archivo
// void check_format(int cantFiles, char files[], char *format)
// {
//     int i = 0;
//     for (; i <= cantFiles; i++)
//     {
//         if (!strcmp(files[i], format))
//         {
//             printf("Enviar solamente archivos .cnf \n ");
//             abort();
//         }
//     }
// }

// {
//     printf("%s\n", argv[i + 1]);
//     printf("%s\n", argv[i + 2]);
//     char buf[20] = {'\0'};
//     strcpy(buf, argv[i + 1]);
//     strcat(buf, "\n");
//     write(fd_work[i][1], buf, strlen(buf));
//     // write(fd_work[i][1], "\n", strlen("\n" + 1));
//     //sleep(1);
//     write(fd_work[i][1], argv[i + 2], strlen(argv[i + 2]) + 1);
//     write(fd_work[i][1], "\n", strlen("\n" + 1));
//}