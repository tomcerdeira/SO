#ifndef INCLUDES
#define INCLUDES

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
//Includes y defines de la Shared Memory
#include <sys/mman.h>
#include <semaphore.h>

#define SIZEOF_SMOBJ 200
#define SMOBJ_NAME "/myMemoryObj"
#define BUFFER_SIZE 256
#define SIZEOF_RESPONSE 150
#define SEMAPHORE_NAME "semaphore1" // El valor del semaforo indica la cantidad de resltados que hay para leer



#endif