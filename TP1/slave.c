#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int randInt(int a, int b);

int main(int argc, char *argv[])
{
    //  setvbuf(stdout, NULL, _IONBF, 0);
    // setvbuf(stdin, 0, _IONBF, 0);
   // srand(time(NULL));
    int rand1 = randInt(1, 10);
  
    sleep((getpid() % 3)+2);
    if (1)
    {
        // printf("Hijo %d espera %d\n", getpid(), rand1);
        printf("Hijo %d recibe archivo %s\n", getpid(), argv[1]);
    }
    
    return 1;
}

int randInt(int a, int b)
{
    int randValue;
    randValue = (rand() % (b - a + 1)) + a;
    return randValue;
}
