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
#include <poll.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define INITIAL_CANT_FILES 2
#define BUFFER_SIZE 256

int fd_work[MAX_PROCESSES][2]; // par Master- slave --> Master escribe y slave lee
int fd_sols[MAX_PROCESSES][2]; // Master lee lo que los hijos escriben

int offset_args =1;
int cantFilesToSend = 0;
int cantFilesResolved = 0;

// void check_format(int cantFiles, char files[], char *format);
void prepare_fd_set(int *max_fd1, fd_set *fd_slaves1);
void concatNFiles(int cantFiles,char ** files, char concat[]);
bool is_pipe_closed(int fd);

    int main(int argc, char *argv[])
{
    // Disable buffering on stdout
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, 0, _IONBF, 0);

    int cantFilesToSend = argc - 1;
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

        // Funcion de mandar muchos archivos
        concatNFiles(INITIAL_CANT_FILES,(argv + offset_args), files_concat);
        offset_args += INITIAL_CANT_FILES;
        write(fd_work[i][1], files_concat, strlen(files_concat) + 1);
        int j =0;
        while(files_concat[j]!= '\0'){
            files_concat[j++]='\0';
        }
        cantFilesToSend -= INITIAL_CANT_FILES;
    }

   
    // Logica del padre para leer y escribir tareas.
    fd_set fd_slaves;
    int max_fd = 0;

    while ((argc - 1) > cantFilesResolved)
    {
        //printf("argc-1 = %d , cantFilesResolved = %d", (argc - 1), cantFilesResolved);
        char buf[265] = {'\0'};

        prepare_fd_set(&max_fd, &fd_slaves);
        //printf("Llego al select \n");
        int res_select = select(max_fd, &fd_slaves, NULL, NULL, NULL);
        //printf("Salgo del select \n");

        if (res_select < 0)
        {
            perror("Select error: ");
            abort();
        }
        else if (res_select)
        {
            for (i = 0; i < MAX_PROCESSES; i++)
            {
                if (FD_ISSET(fd_sols[i][0], &fd_slaves))
                {
                    cant_sol_process[i]++;
                    read(fd_sols[i][0], buf, sizeof(buf));
                    // Mandarla al vista
                    cantFilesResolved++;
                    printf(buf);
                    printf("\n");
                    // Limpiamos buffer
                    int y = 0;
                    while (buf[y] != '\0')
                    {
                        buf[y++] = '\0';
                    }
                

                    if (cant_sol_process[i] >= INITIAL_CANT_FILES && cantFilesToSend > 0)
                    {
                        char buffer_aux[BUFFER_SIZE] = {'\0'};
                       
                        strcpy(buffer_aux,argv[offset_args++]);
                        //Mandamos otra tarea   
                        strcat(buffer_aux, "\n");
                        //printf("%d offset y su buffer auz es  %s\n",offset_args,buffer_aux);
                        write(fd_work[i][1], buffer_aux, strlen(buffer_aux));
                        cantFilesToSend--;
                        int r = 0;
                        while(buffer_aux[r]!= '\0'){
                            buffer_aux[r++]='\0';
                        }
                     }else if(cantFilesToSend <= 0){
                         close(fd_work[i][1]);
                       //  close(fd_sols[i][0]);
                     }
                  
                  
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
    printf("RESOLVI: %d \n", cantFilesResolved);
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
        if (!is_pipe_closed(fd_work[i][1]))
        {
            FD_SET(fd_sols[i][0], &fd_slaves); // Llenamos el set de fd en los que el padre va a recibir las resps.
            if (fd_sols[i][0] > max_fd)
            {
                max_fd = fd_sols[i][0] + 1;
            }
        }
    }

    *max_fd1 = max_fd;
    *fd_slaves1 = fd_slaves;
}

//https://stackoverflow.com/questions/36663845/check-if-unix-pipe-closed-without-writing-anything
bool is_pipe_closed(int fd) {
    struct pollfd pfd = {
        .fd = fd,
        .events = POLLOUT,
    };

    if (poll(&pfd, 1, 1) < 0) {
        return false;
    }

    return pfd.revents & POLLERR;
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

void   concatNFiles(int cantFiles,char ** files, char concat[]){
    
    strcpy(concat, files[0]);
    strcat(concat, "\n");
    int i = 1;
    for(;i<cantFiles;i++){
        strcat(concat,files[i]);
        strcat(concat, "\n");
    }
    printf(concat);
    printf("\n");

}