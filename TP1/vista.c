#include "includes.h"

int strToInt(char * buffer);
void cleanBuffer(char *buffer);

int main(void) //idea de: https://github.com/WhileTrueThenDream/ExamplesCLinuxUserSpace
{
    int fdSM;
    char *ptr;
    struct stat shmobj_st;
    

    
   while( (fdSM = shm_open(SMOBJ_NAME, O_RDONLY, 00400)) == -1); /* open s.m object*/

    sem_t *sem_r_shm = sem_open(SEMAPHORE_NAME, O_CREAT);

    if (fstat(fdSM, &shmobj_st) == -1)
    {
        perror("ERROR en Vista - fstat");
        abort();
    }
    ptr = mmap(NULL, shmobj_st.st_size, PROT_READ, MAP_SHARED, fdSM, 0);
    if (ptr == MAP_FAILED)
    {
        perror("ERROR en Vista - Map failed in read process");
        abort();
    }
   
    
    int cantFiles = (int )  atoi(ptr);
    ptr += 1;
    printf("Proceso VISTA: %d archivos para imprimir \n",cantFiles);
    int res = 0;

    while (cantFiles > 0)
    {
        char buffer[SIZEOF_RESPONSE] = {'\0'};
        res = sem_wait(sem_r_shm);
        if(res < 0){
            perror("ERROR en Vista - sem_wait ");
            abort();
        }
       
        cantFiles --;
        memcpy(buffer,ptr,SIZEOF_RESPONSE);
        ptr += SIZEOF_RESPONSE;
        
        //sleep(1);
        write(STDOUT_FILENO, buffer, SIZEOF_RESPONSE);
        cleanBuffer(buffer);
    }
printf("\n --------------------------------------------------------------------------------------------------------------------- \n");
      printf("Proceso VISTA: todas las soluciones fueron impresas correctamente\n\n\n");
    
    close(fdSM);
     if (munmap(ptr,shmobj_st.st_size) < 0)
    {
        perror("ERROR en Vista - munmap shm");
       // abort();
    }

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