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
#include <sys/mman.h>
#include <semaphore.h>
#include <math.h>

#define SIZEOF_SMOBJ 200
#define FILE_OUTPUT "./output_solve"
#define SMOBJ_NAME "/myMemoryObj"
#define BUFFER_SIZE 256
#define SIZEOF_RESPONSE 150
#define FOOTER_OUTPUT " -------------------------- \n "
#define SEMAPHORE_NAME "semaphore1" // El valor del semaforo indica la cantidad de resltados que hay para leer

#endif