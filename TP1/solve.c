#include "includes.h"

#define CANT_PROCESSES 5
#define INITIAL_CANT_FILES 2

int fd_work[CANT_PROCESSES][2]; // PIPE maste --> slave
int fd_sols[CANT_PROCESSES][2]; // PIPE slave --> master
int flags_fd_work_open[CANT_PROCESSES];
int offset_args = 1;
int cantFilesToSend = 0;
int cantFilesResolved = 0;
int processes[CANT_PROCESSES];
int cant_sol_process[CANT_PROCESSES];
char *ptr_shared_memory;

int createSHM(size_t size);
void check_format(int cantFiles, char *files[], char *format);
void prepare_fd_set(int *max_fd1, fd_set *fd_slaves1);
void concatNFiles(int cantFiles, char **files, char concat[]);
void create_slaves();
void cleanBuffer(char * buffer);
void create_pipes();

int main(int argc, char *argv[])
{
    // Deshabilitamos buffering en stdout
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, 0, _IONBF, 0);

    check_format(cantFilesToSend, (argv + 1), ".cnf");
    create_pipes();
    create_slaves();

    sem_t *sem_w_shm = sem_open(SEMAPHORE_NAME, O_CREAT, 0644, 0);
 
    int cantFilesToSend = argc - 1;
    int i = 1;

    // Mandamos al vista la cantidad de archivos a procesar
    printf("%d \n",cantFilesToSend);

    int fd_shared_memory = createSHM(SIZEOF_RESPONSE * cantFilesToSend);     

    ptr_shared_memory = mmap(NULL, SIZEOF_RESPONSE * cantFilesToSend, PROT_WRITE, MAP_SHARED, fd_shared_memory, 0);
    if (ptr_shared_memory == MAP_FAILED)
    {
        perror("ERROR en Aplicacion - Map failed in write process");
        abort();
    }
    char num[10];
    sprintf(num,"%d",cantFilesToSend);
    strcpy(ptr_shared_memory,num);
    ptr_shared_memory += strlen(num) + 1;
   
    int resolved_fd;
    if((resolved_fd = open("./output_solve", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR)) < 0){
        perror("ERROR en Aplicacion - Open");
        abort();
    }


    char files_concat[256] = {'\0'};
    // Mandamos archivos a los hijos
    for (i = 0; i < CANT_PROCESSES; i++)
    {
        concatNFiles(INITIAL_CANT_FILES, (argv + offset_args), files_concat);
        offset_args += INITIAL_CANT_FILES;
        write(fd_work[i][1], files_concat, strlen(files_concat) + 1);
        cleanBuffer(files_concat);
        cantFilesToSend -= INITIAL_CANT_FILES;
    }

    // Logica del padre para leer y mandar tareas.
    fd_set fd_slaves;
    int max_fd = 0;
   

    while ((argc - 1) > cantFilesResolved)
    {
       
        char buf[265] = {'\0'};

        prepare_fd_set(&max_fd, &fd_slaves);
      
        int res_select = select(max_fd, &fd_slaves, NULL, NULL, NULL);
        if (res_select < 0)
        {
            perror("ERROR en Aplicacion - Select");
            abort();
        }
        else if (res_select)
        {
            for (i = 0; i < CANT_PROCESSES; i++)
            {
                if (FD_ISSET(fd_sols[i][0], &fd_slaves))
                {
                    cant_sol_process[i]++;
                    read(fd_sols[i][0], buf, sizeof(buf));

                    cantFilesResolved++;

                    // Mandarlo al archivo resueltos
                    if(write(resolved_fd, buf, sizeof(buf)) < 0){
                        perror("ERROR en Aplicacion - Write archivo");
                        abort();
                    }

                    // Escribimos en memoria compartida
                    memcpy(ptr_shared_memory, buf, sizeof(buf));

                    int ret_sem;
                    ret_sem = sem_post(sem_w_shm);
                    if (ret_sem < 0)
                    {
                        perror("ERROR en Aplicacion - SEM_POST");
                        abort();
                    }

                    ptr_shared_memory += SIZEOF_RESPONSE;
                   cleanBuffer(buf);

                    if (cant_sol_process[i] >= INITIAL_CANT_FILES && cantFilesToSend > 0)
                    {
                        char buffer_aux[BUFFER_SIZE] = {'\0'};

                        strcpy(buffer_aux, argv[offset_args++]);
                        strcat(buffer_aux, "\n");
                        
                        //Mandamos otra tarea
                        write(fd_work[i][1], buffer_aux, strlen(buffer_aux));
                        cantFilesToSend--;
                        cleanBuffer(buffer_aux);
                    }
                    else if (cantFilesToSend == 0)
                    {
                        close(fd_work[i][1]);
                        close(fd_sols[i][0]);
                        flags_fd_work_open[i] = 0;
                         waitpid(processes[i], NULL, 0);
                    }
                }
            }
          
        }
        else
        {
            printf("Select vale 0 \n");
        }
    }
    char buffer[BUFFER_SIZE];

    sprintf(buffer, "Archivos hechos %d \n", cantFilesResolved);
    memcpy(ptr_shared_memory, buffer, sizeof(buffer));

      if (sem_close(sem_w_shm) < 0 || sem_unlink(SEMAPHORE_NAME) < 0)
    {
        perror("ERROR en Aplicacion - Sem close/unlink error");
        abort();
    }
   
   
   
    if (munmap(ptr_shared_memory,(SIZEOF_RESPONSE * cantFilesToSend )) < 0)
    {
        perror("ERROR en Aplicacion - Munmap");
        //abort();
    }
 if (shm_unlink(SMOBJ_NAME) < 0)
    {
        perror("ERROR en Aplicacion - Unlink shm");
        abort();
    }

     
    close(fd_shared_memory);

    
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////FUNCIONES////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Idea de: https://github.com/WhileTrueThenDream/ExamplesCLinuxUserSpace
int createSHM(size_t size)
{
    int fdSharedMemory;
    fdSharedMemory = shm_open(SMOBJ_NAME, O_CREAT | O_RDWR, 00700); /* create s.m object*/
    if (fdSharedMemory == -1)
    {
        perror("ERROR en Aplicacion - File descriptor");
        abort();
    }
    if (-1 == ftruncate(fdSharedMemory, size))
    {
        perror("ERROR en Aplicacion - Shared memory cannot be resized");
        abort();
    }
    
   
    return fdSharedMemory;
}

// Resetea el set de fileDescriptors que usa el select
void prepare_fd_set(int *max_fd1, fd_set *fd_slaves1)
{
    fd_set fd_slaves;
    int max_fd = 0;

    FD_ZERO(&fd_slaves);

    int i = 0;
    for (; i < CANT_PROCESSES; i++)
    {
        if (flags_fd_work_open[i] != 0) // Si es 0 quiere decir que lo cerramos
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

// Validacion del tipo de archivo
void check_format(int cantFiles, char *files[], char *format)
{
    int i = 0;
    for (; i < cantFiles; i++)
    {
        if (strstr(files[i], format) == NULL)
        {
            printf("ERROR en Aplicacion - Enviar solamente archivos .cnf\n");
            abort();
        }
    }
}

void concatNFiles(int cantFiles, char **files, char concat[])
{

    strcpy(concat, files[0]);
    strcat(concat, "\n");
    int i = 1;
    for (; i < cantFiles; i++)
    {
        strcat(concat, files[i]);
        strcat(concat, "\n");
    }
}

// Logica creacion de los pipes
void create_pipes(){
     int i;
    for (i = 0; i < CANT_PROCESSES; i++)   { 
        if (pipe(fd_work[i]) != 0)
        {
            perror("ERROR en Aplicacion - PIPE Work");
            abort();
        }
        flags_fd_work_open[i] = 1;
        if (pipe(fd_sols[i]) != 0)
        {
            perror("ERROR en Aplicacion - PIPE Sols");
            abort();
        }
    }
}

// Logica creacion de los slaves
void create_slaves(){

    int i;
    for (i = 0; i < CANT_PROCESSES; i++)
    {
        cant_sol_process[i] = 0;

        // Logica de los hijos
        if ((processes[i] = fork()) == 0)
        {
            int j = 0;
            for (; j < CANT_PROCESSES; j++)
            {
                // Cerramos los pipes ajenos a este hijo.
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

            // Redireccionamos la entrada del hijo al nuevo pipe
            if (dup2(fd_work[i][0], STDIN_FILENO) < 0)
            { 
                perror("ERROR en Aplicacion - Dup 1");
                abort();
            }

            // Redireccionamos la salida del hijo al padre
            if (dup2(fd_sols[i][1], STDOUT_FILENO) < 0)
            { 
                perror("ERROR en Aplicacion - Dup 2");
                abort();
            }

            char *const params[] = {"slave", NULL};
            int res_execv = execv(params[0], params);
            if (res_execv < 0)
            {
                perror("ERROR en Aplicacion - Execv");
                abort();
            }
        }
        else if (processes[i] < 0)
        {
            perror("ERROR en Aplicacion - Fork");
        }
    }
}

void cleanBuffer(char * buffer){
    int j=0;
    while(buffer[j] != '\0'){
        buffer[j++] = '\0';
    }
}
