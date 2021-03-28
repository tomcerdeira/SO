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

#define MAX_PROCESSES 5

int main(int argc, char *argv[])
{
    // Disable buffering on stdout
    setvbuf(stdout, NULL, _IONBF, 0);
  //  setvbuf(stdin, 0, _IONBF, 0);
    int cantFiles = argc - 1; // ver como hacer cuando recibamos una carpeta como parametro
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
        cant_sol_process[i]=0;
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

            char *const params[] = {"slave", argv[i + 1], NULL};
            int res_execv = execv(params[0], params);

            //int res_execv = execv("./slave ", &argv[i + 1]); //// --> Completar con args
            if (res_execv < 0)
            {
                perror("Execv error");
                abort();
            }
        }else if(processes[i] < 0){
            perror("Fork");
        }
    }

    // Logica del padre para leer y escribir tareas.
    fd_set fd_slaves;
    int max_fd = 0;

    while (cantFiles > 0)
    {
        FD_ZERO(&fd_slaves);
        
        char buf[265] = {'\0'};
     
        for (i = 0; i < MAX_PROCESSES; i++)
        {
            FD_SET(fd_sols[i][0], &fd_slaves); // Llenamos el set de fd en los que el padre va a recibir las resps.
            if (fd_sols[i][0] > max_fd)
            {
                max_fd = fd_sols[i][0] + 1;
            }
        }
        int res_select = select(max_fd, &fd_slaves, NULL, NULL, NULL);
        if (res_select < 0)
        {
            perror("Select error: ");
            abort();
        }
        else if (res_select)
        {
            printf("Leo %d bytes \n",res_select);
            int j=0;

            for (i = 0; i < MAX_PROCESSES; i++)
            {
                if (FD_ISSET(fd_sols[i][0], &fd_slaves))
                {
                    cant_sol_process[i]++;
                    read(fd_sols[i][0],buf,sizeof(buf)); 
                    //printf("Hijo %d se libero \n", i);

                    if(cant_sol_process[i]>=2){
                        write(fd_work[i][1],argv[argc-1-cantFiles],sizeof(argv[argc-1-cantFiles])); // CAPAZ PONER MAS LINDO LA POS 
                        // Logica de mandar 1 tarea mas
                    }
                    // logica memcompartida
                    write(STDOUT_FILENO,buf,sizeof(buf));       
               
                }
            }
            printf("----------------------------------------------- \n");
        }
        else
        {
            printf("Select vale 0 \n");
        }
        cantFiles--;
    }

    for (i=0;i<MAX_PROCESSES ; i++){
        waitpid(processes[i],NULL,0); 
    }

    return 0;
}