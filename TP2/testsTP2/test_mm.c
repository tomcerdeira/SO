#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "includes.h"
#include "test_util.h"

#define MAX_BLOCKS 128
#define MAX_MEMORY 1024 //Should be around 80% of memory managed by the MM

typedef struct MM_rq
{
  void *address;
  uint32_t size;
} mm_rq;

void test_mm()
{
  mm_rq mm_rqs[MAX_BLOCKS];
  uint8_t rq;
  uint32_t total;

  //initialize(); /////////////////////////////////////////////////

  while (1)
  {
    rq = 0;
    total = 0;

    //printf("Total memory USED: %d - Total memory AVAILABLE: %d\n", getMemoryUsed(), getMemoryAvailable());
    //printf("------------------------------------------------\n");

    // Request as many blocks as we can
    printf("Pido memoria\n");
    while (rq < MAX_BLOCKS && total < MAX_MEMORY)
    {
      mm_rqs[rq].size = GetUniform(MAX_MEMORY - total - 1) + 1;
      //printf("%d\n", mm_rqs[rq].size);
      printf("Se piden %d\n",mm_rqs[rq].size);
      mm_rqs[rq].address = mallocNUESTRO(mm_rqs[rq].size); // TODO: Port this call as required
                                                           //TODO: check if NULL

      ///////////////////////////////

      if (mm_rqs[rq].address == NULL)
      {
        printf("No hay memoria suficiente para %d\n", mm_rqs[rq].size);
        //exit(1);
      }
      printf("Total memory USED: %d - Total memory AVAILABLE: %d\n", getMemoryUsed(), getMemoryAvailable());
      printf("------------------------------------------------\n");

      //////////////////////////////

      total += mm_rqs[rq].size;
      rq++;
    }

    // Set
    printf("\nSeteo toda la memoria\n");
    uint32_t i;

    void *auxi;

    for (i = 0; i < rq; i++)
    {
      if (mm_rqs[i].address != NULL)
      {
        auxi = memsetNUESTRO(mm_rqs[i].address, i, mm_rqs[i].size); // TODO: Port this call as required
        if (auxi == NULL)
        {
          printf("ERROR EN MEMSET \n");
          exit(1);
        }
      }
    }
    //Check
    for (i = 0; i < rq; i++)
    {
      if (mm_rqs[i].address != NULL)
      {
        ////////
        // uint8_t *p = (uint8_t *)mm_rqs[i].address;
        // int h = 0;

        // for (; h < mm_rqs[i].size; h++, p++)
        //   printf("EN MEMORIA: %d - DEBERIA SER: %d \n", *(p), i);
        // printf("------------------------------------------------\n");

        //////////
        if (!memcheck(mm_rqs[i].address, i, mm_rqs[i].size))
        {
          printf("ERROR!\n"); // TODO: Port this call as required
          exit(1);
        }
      }
    }
    // Free
    printf("\nLibero memoria\n");
    printf("Total memory USED: %d - Total memory AVAILABLE: %d\n", getMemoryUsed(), getMemoryAvailable());
    for (i = 0; i < rq; i++)
    {
      //printf("VALOR RQ: %d \n", rq);

      if (mm_rqs[i].address != NULL)
      {
        freeMemory(mm_rqs[i].address);
        //printf("VALOR i: %d \n", i);
        //exit(1);
      }
    }

    printf("Total memory USED: %d - Total memory AVAILABLE: %d\n", getMemoryUsed(), getMemoryAvailable());
    printf("------------------------------------------------\n\n");

    //free(mm_rqs[i].address); // TODO: Port this call as required
    ////////// USAR free DESPUES!!!
    sleep(1);
  }
}

int main()
{
  test_mm();
  return 0;
}
