#include "includes.h"

int main(void) //idea de: https://github.com/WhileTrueThenDream/ExamplesCLinuxUserSpace
{
    sleep(2);
    int fdSM;
    char *ptr;
    struct stat shmobj_st;
    sem_t *sem_r_shm = sem_open(SEMAPHORE_NAME, O_CREAT);

    fdSM = shm_open(SMOBJ_NAME, O_RDONLY, 00400); /* open s.m object*/
    if (fdSM == -1)
    {
        perror("Vista: Error file descriptor");
        abort();
    }

    if (fstat(fdSM, &shmobj_st) == -1)
    {
        perror("Vista: Error fstat");
        abort();
    }
    ptr = mmap(NULL, shmobj_st.st_size, PROT_READ, MAP_SHARED, fdSM, 0);
    if (ptr == MAP_FAILED)
    {
        perror("Vista: Map failed in read process");
        abort();
    }

    int res = 0;
    //////////////////////////////
    while (1 && res != -1)
    {
        char buffer[SIZEOF_RESPONSE] = {'\0'};

        //printf("ANTES DEL WAIT \n");
        res = sem_wait(sem_r_shm);
        //printf("DESPUES DE SEMAFORO\n");
        //res = read(fdSM, buffer, SIZEOF_RESPONSE);
        int i;
        for (i = 0; i < SIZEOF_RESPONSE; i++)
        {
            buffer[i] = ptr[i];
        }
        ptr += SIZEOF_RESPONSE;
        sleep(1);
        write(STDOUT_FILENO, buffer, SIZEOF_RESPONSE);
        int r = 0;
        while (buffer[r] != '\0')
        {
            buffer[r++] = '\0';
        }
    }
    //wait();
    // printf("%s \n", ptr);
    close(fdSM);

    return 0;
}