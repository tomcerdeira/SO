
#include <test_mm.h>


void test_mm()
{
  mm_rq mm_rqs[MAX_BLOCKS];
  uint8_t rq;
  uint32_t total;
  while (1)
  {
    rq = 0;
    total = 0;

    print("Total memory USED:",0xFFFFFF,0x000000);
    printBase(getMemoryUsed(),10);
    print("Total memory AVAILABLE:",0xffffff,0x000000);
    printBase( getMemoryAvailable(),10);
    print("\n",0xffffff,0x000000);
    print("------------------------------------------------\n",0xffffff,0x000000);

    // Request as many blocks as we can
    while (rq < MAX_BLOCKS && total < MAX_MEMORY)
    {
      mm_rqs[rq].size = GetUniform(MAX_MEMORY - total - 1) + 1;

      mm_rqs[rq].address = mallocNUESTRO(mm_rqs[rq].size);

      if (mm_rqs[rq].address == 0)
      {
        print("ERROR EN MALLOC \n",0xffffff,0x000000);
        exit(1);
      }
    print("Total memory USED:",0xFFFFFF,0x000000);
    printBase(getMemoryUsed(),10);
    print("Total memory AVAILABLE:",0xffffff,0x000000);
    printBase( getMemoryAvailable(),10);
    print("\n",0xffffff,0x000000);
    print("------------------------------------------------\n",0xffffff,0x000000);

      total += mm_rqs[rq].size;
      rq++;
    }

    // Set
    uint32_t i;

    void *auxi;

    for (i = 0; i < rq; i++)
    {
      if (mm_rqs[i].address != 0)
      {
        memsetNUESTRO(mm_rqs[i].address, i, mm_rqs[i].size); 
       
      }
    }
    //Check
    for (i = 0; i < rq; i++)
    {
      if (mm_rqs[i].address != 0)
      {
        if (!memcheck(mm_rqs[i].address, i, mm_rqs[i].size))
        {
         print("ERROR! \n",0xffffff,0x000000);
          exit(1);
        }
      }
    }
    // Free
    for (i = 0; i < rq; i++)
    {

      if (mm_rqs[i].address != 0)
      {
        freeMemory(mm_rqs[i].address);
      }
    }

     print("Total memory USED:",0xFFFFFF,0x000000);
    printBase(getMemoryUsed(),10);
    print("Total memory AVAILABLE:",0xffffff,0x000000);
    printBase( getMemoryAvailable(),10);
    print("\n",0xffffff,0x000000);
    print("------------------------------------------------\n",0xffffff,0x000000);
  }
}

