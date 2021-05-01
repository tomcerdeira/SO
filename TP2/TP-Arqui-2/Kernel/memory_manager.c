#include <memory_manager.h>

int indexMemoryAsigned = 0;
memoryBlock bitMapMemory[CANTBLOCKS];
int id = 0;

int cantOfMemoryUsed = 0;

static char *const start = (void *) 0x600000;

char * next = &start; //next siempre apunta a la última posición de memoria que se puede usar
                // ??????????? Es por el &
// Inicializamos el bitMap
void initialize()
{
    int i = 0;
    for (; i < CANTBLOCKS; i++)
    {
        memoryBlock newMemoryblock;
        newMemoryblock.cantOfBlocks = 1;
        newMemoryblock.isFree = 1;
        newMemoryblock.start = (start + i * BLOCK);
        newMemoryblock.id_request = id;
        bitMapMemory[i] = newMemoryblock;
    }

    // printf("%d cantt \n", CANTBLOCKS);
    // printf("Ya inicialice \n\n");
}

void *dummy_malloc_with_blocks(int requestedCantOfBlocks)
{
    int i = 0;

    int index = searchFreeBlocks(requestedCantOfBlocks);

   // printf("ANTES: Requested cant of blocks: %d - Index: %d - cantBlocksUsed: %d\n", requestedCantOfBlocks, index, cantOfMemoryUsed);

    if (index >= 0)
    {
        i = index;
        id += 1;
        for (; i < index + requestedCantOfBlocks; i++)
        {
            bitMapMemory[i].isFree = 0;
            bitMapMemory[i].id_request = id;
            cantOfMemoryUsed++;
        }
        return bitMapMemory[index].start;
    }

   // printf("No hay memoria \n");
    // Si llega aca es por que no hay memoria contigua libre para dar
    return NULL;
}

int searchFreeBlocks(int requestedBlocks)
{
    int i = 0;
    int flag = 1;
    for (; i < CANTBLOCKS; i++)
    {
        //printf("ENTRO 1\n");
        if (bitMapMemory[i].isFree == 1)
        {
            //printf("ENTRO 2\n");
            int j = i + 1;
            for (; j < CANTBLOCKS && flag && j < i + requestedBlocks; j++)
            {
                //printf("ENTRO 3\n");
                if (!bitMapMemory[j].isFree)
                {
                    flag = 0;
                }
            }
            if (flag)
            {
                return i;
            }
            else
            {
                flag = 1;
                i = j;
            }
        }
    }
    return -1;
}

int searchIndexBitMap(char *ptr)
{
    int i = 0;

    for (; i < CANTBLOCKS; i++)
    {
        if (ptr >= bitMapMemory[i].start && ptr < (bitMapMemory[i].start + BLOCK))
        {
            return i;
        }
    }
    return -1;
}

void freeMemory(char *ptr)
{
    int index_block = searchIndexBitMap(ptr);
    if (index_block < 0)
    {
      // printf("No hay memoria para liberar");
        return;
    }
    int id_find = bitMapMemory[index_block].id_request;

    int t = index_block;

    while (bitMapMemory[t].id_request == id_find && t >= 0)
    {
        bitMapMemory[t].isFree = 1;
        t--;
        cantOfMemoryUsed--;
    }

    t = index_block + 1;
    while (bitMapMemory[t].id_request == id_find && t <= CANTBLOCKS)
    {
        bitMapMemory[t].isFree = 1;
        t++;
        cantOfMemoryUsed--;
    }
}

void *mallocNUESTRO(int size)
{
    int cantBlocks = size / BLOCK + 1;
    return dummy_malloc_with_blocks(cantBlocks);
}

void *memsetNUESTRO(char *ptr, int toWrite, int size)
{

    int index = searchIndexBitMap(ptr);
    int id_found = bitMapMemory[index].id_request;
    int i = index;
    int j = 0;

    while (bitMapMemory[i].id_request == id_found && size != 0)
    {
        for (; j < BLOCK && size != 0; j++)
        {
            // printf("ENTROOOOOO. id_request: %d - size: %d\n", id_found, size);
            bitMapMemory[i].start[j] = toWrite;
            size--;
        }
        // printf("UN BLOQUE COMPLETO. id_request (i): %d - id_request (i+1): %d\n", bitMapMemory[i].id_request, bitMapMemory[i + 1].id_request);
        i++;
        j = 0;
    }

    if (size == 0)
    {
        return bitMapMemory[index].start;
    }

    return NULL;
}

int getTotalMemorySize()
{
    return MEMORY_SIZE;
}

int getMemoryAvailable()
{
    return MEMORY_SIZE - (cantOfMemoryUsed * BLOCK);
}

int getMemoryUsed()
{
    return (cantOfMemoryUsed * BLOCK);
}

/////////////////////////////// HASTA ACA

// int main(int argc, char *argv[])
// {
//     initialize();
//     char *ptr;
//     int i;
//     // int j = 0;
//     ptr = dummy_malloc_with_blocks(15);
//     if (ptr == NULL)
//     {
//         printf("No pude asignar memoria primer caso!\n");
//     }

//     char *ptr2;
//     ptr2 = dummy_malloc_with_blocks(5);
//     if (ptr2 == NULL)
//     {
//         printf("No pude asignar memoria segundo caso!\n");
//     }
//     char *ptr3;
//     ptr3 = dummy_malloc_with_blocks(5);
//     if (ptr3 == NULL)
//     {
//         printf("No pude asignar memoria tercer caso!\n");
//     }
//     char *ptr4;
//     ptr4 = dummy_malloc_with_blocks(5);
//     if (ptr4 == NULL)
//     {
//         printf("No pude asignar memoria cuarta caso!\n");
//     }
//     char *ptr5;
//     ptr5 = dummy_malloc_with_blocks(5);
//     if (ptr5 == NULL)
//     {
//         printf("No pude asignar memoria quinto caso!\n");
//     }
//     char *ptr6;
//     ptr6 = dummy_malloc_with_blocks(5);
//     if (ptr6 == NULL)
//     {
//         printf("No pude asignar memoria sexto caso!\n");
//     }

//     printf("Ya DI toda la memoria \n");
//     printf("Voy a liberar la memoria \n");
//     printf("%d valor del ptr sin mover \n", ptr);

//     freeMemory(ptr);
//     printf("Libero 1 \n ");

//     freeMemory(ptr2);
//     printf("Libero 2 \n");
//     freeMemory(ptr3);
//     printf("Libero 3 \n");
//     freeMemory(ptr3);
//     ptr3 = dummy_malloc_with_blocks(10); // NO SE LIBERAN
//     printf("Libero 3 DEVUELTA\n");
//     freeMemory(ptr4);
//     printf("Libero 4 \n");
//     freeMemory(ptr5);
//     printf("Libero 5 \n");
//     printf("%d valor del ptr 6 sin mover \n", ptr6);
//     freeMemory(ptr6);
//     printf("LIBERO TODO MENOS 10 bloques que me pidio el ptr3\n");
//     // //
//     for (i = 0; i < CANTBLOCKS; i++)
//     {
//         printf("Is FREE= %d con ID: %d con start: %d \n", bitMapMemory[i].isFree, bitMapMemory[i].id_request, bitMapMemory[i].start);
//     }
//     // //
//     // printf("Ya LIBERE toda la memoria \n");
//     return 0;
// }

// void *dummy_malloc_with_blocks(int requestedCantOfBlocks)
// {
//     memoryBlock mb;

//     mb.cantOfBlocks = requestedCantOfBlocks;

//     char *r;
//     int t = 0;
//     for (; t < indexMemoryAsigned; t++) // Busco una posicion en el arreglo para reutilizar
//     {
//         if (asignedMemory[t].isFree && asignedMemory[t].cantOfBlocks >= requestedCantOfBlocks)
//         {
//             printf("Reutilizo un bloque \n");
//             mb.start = asignedMemory[t].start;
//             asignedMemory[t] = mb;
//             asignedMemory[t].isFree = 0;
//             r = mb.start;
//             return r;
//         }
//     }

//     if (next - mb.start <= MEMORY_SIZE - (mb.cantOfBlocks * BLOCK)) //se fija si entra en la memoria a partir de next
//     {
//         mb.start = next;
//         next += (mb.cantOfBlocks * BLOCK);

//         mb.isFree = 0;
//         asignedMemory[indexMemoryAsigned++] = mb;
//         r = mb.start;

//         return r;
//     }
//     else
//     {
//         return NULL; //NO encontro espacio liberado NI le entro en el espacio que quedaba en memoria
//     }
// }

// void freeMemory(char *ptr)
// {
//     int index_of_block = indexOfMemoryBlock(ptr);
//     if (index_of_block == -1 || asignedMemory[index_of_block].isFree)
//     {
//         return;
//     }
//     asignedMemory[index_of_block].isFree = 1; // Deja el espacio libre para escritura, no la limpia
// }

// int indexOfMemoryBlock(char *ptr)
// {
//     int i = 0;

//     for (; i < indexMemoryAsigned; i++)
//     {
//         if (ptr >= asignedMemory[i].start && ptr < (asignedMemory[i].start + (asignedMemory[i].cantOfBlocks * BLOCK)))
//         {
//             return i;
//         }
//     }
//     return -1;
// }
