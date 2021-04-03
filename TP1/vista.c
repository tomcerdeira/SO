#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>    /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define SMOBJ_NAME "/myMemoryObj"

int main(void) //idea de: https://github.com/WhileTrueThenDream/ExamplesCLinuxUserSpace
{
    int fdSM;
    char *ptr;
    struct stat shmobj_st;

    fdSM = shm_open(SMOBJ_NAME, O_RDONLY, 00400); /* open s.m object*/
    if (fdSM == -1)
    {
        printf("Error file descriptor %s\n", strerror(errno));
        exit(1);
    }

    if (fstat(fdSM, &shmobj_st) == -1)
    {
        printf(" error fstat \n");
        exit(1);
    }
    ptr = mmap(NULL, shmobj_st.st_size, PROT_READ, MAP_SHARED, fdSM, 0);
    if (ptr == MAP_FAILED)
    {
        printf("Map failed in read process: %s\n", strerror(errno));
        exit(1);
    }

    printf("%s \n", ptr);
    close(fdSM);

    return 0;
}