#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int rand1 = rand() % 10;
    sleep(rand1);
    printf("Hijo %d recibe archivo %s\n", getpid(), argv[1]);
    return 1;
}
