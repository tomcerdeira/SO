// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "includes.h"

int strToInt(char *buffer);
void cleanBuffer(char *buffer);

char *ptr_aux;

int main(void) //idea de: https://github.com/WhileTrueThenDream/ExamplesCLinuxUserSpace
{
    int fdSM;
    char *ptr;
    struct stat shmobj_st;

    sem_t *sem_r_shm = sem_open(SEMAPHORE_NAME, O_CREAT);
    if (sem_r_shm == SEM_FAILED)
    {
        perror("ERROR en Vista - sem_open");
        abort();
    }

    int res = sem_wait(sem_r_shm);
    if (res < 0)
    {
        perror("ERROR en Vista - sem_wait ");
        abort();
    }

    while ((fdSM = shm_open(SMOBJ_NAME, O_RDONLY, 00400)) == -1)
        ; /* open s.m object*/

    if (fstat(fdSM, &shmobj_st) == -1)
    {
        perror("ERROR en Vista - fstat");
        abort();
    }
    ptr = mmap(NULL, shmobj_st.st_size, PROT_READ, MAP_SHARED, fdSM, 0);
    ptr_aux = mmap(NULL, shmobj_st.st_size, PROT_READ, MAP_SHARED, fdSM, 0);
    if (ptr == MAP_FAILED || ptr_aux == MAP_FAILED)
    {
        perror("ERROR en Vista - Map failed in read process");
        abort();
    }

    int cantFiles = (int)atoi(ptr_aux);
    ptr_aux += sizeof(cantFiles);
    printf("\n");
    printf("Proceso VISTA: %d soluciones para imprimir \n", cantFiles);
    printf("\n --------------------------------------------------------------------------------------------------------------------- \n\n");
    res = 0;

    while (cantFiles > 0)
    {
        char buffer[SIZEOF_RESPONSE] = {'\0'};
        res = sem_wait(sem_r_shm);
        if (res < 0)
        {
            perror("ERROR en Vista - sem_wait ");
            abort();
        }

        cantFiles--;
        memcpy(buffer, ptr_aux, SIZEOF_RESPONSE);
        ptr_aux += SIZEOF_RESPONSE;

        //sleep(1);
        write(STDOUT_FILENO, buffer, SIZEOF_RESPONSE);
        cleanBuffer(buffer);
    }
    printf("\n --------------------------------------------------------------------------------------------------------------------- \n\n");
    printf("Proceso VISTA: todas las soluciones fueron impresas correctamente\n\n\n");

    if (sem_close(sem_r_shm) < 0)
    {
        perror("ERROR en Vista - Sem close");
        abort();
    }

    if (munmap(ptr, shmobj_st.st_size) < 0)
    {
        perror("ERROR en Vista - munmap shm");
        abort();
    }

    close(fdSM);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////FUNCIONES////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cleanBuffer(char *buffer)
{
    int j = 0;
    while (buffer[j] != '\0')
    {
        buffer[j++] = '\0';
    }
}