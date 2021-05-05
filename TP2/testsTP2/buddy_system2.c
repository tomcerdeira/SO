//// includes......
#include <stdio.h>
#define MAX_HEIGHT 8 //VERRRR!

#define MEMORY_SIZE 1024
#define SMALLEST_BLOCK_SIZE 4
// #define NULL 0
#define CANT_NODES 511 // DESHARCODEAR
char *start[MEMORY_SIZE] = {'\0'};

int initialized = 0;

typedef struct
{
    int id;
    int isFree;    //1 FREE - 0 NOT Free
    int isSplited; //1 YES - 0 NO
    char *startOfMemoryAddress;
    int sizeOfMemory;
    struct node *leftN;
    struct node *rightN;
} node;

node *auxMemoryForNodes[CANT_NODES] = {{0}};
int index = 0;
node *initMemoryRec(char *memoryAddress, int memorySize, int height);
void *mallocNUESTRO(int size);
int getMinBlockSize(int sizeOfMemoryRequested);
void *searchMemoryRec(node *n, int sizeRequired);
void initializeMemory()
{
    initMemoryRec(start, MEMORY_SIZE, MAX_HEIGHT);
    if (auxMemoryForNodes[0]->leftN == NULL || auxMemoryForNodes[0]->rightN == NULL)
    {
        printf("ERROR HIJOS DE ROOT NULL \n");
    }
    initialized++;
}

int count = 0;

node *initMemoryRec(char *memoryAddress, int memorySize, int height)
{
    if (height == 0) // Llegamos al ultimo nivel
    {
        //printf("Llego al height MAX %d\n", count++);
        return NULL;
    }

    auxMemoryForNodes[index]->id = index;
    auxMemoryForNodes[index]->isFree = 1;
    auxMemoryForNodes[index]->isSplited = 0;
    auxMemoryForNodes[index]->startOfMemoryAddress = memoryAddress;
    auxMemoryForNodes[index]->sizeOfMemory = memorySize;
    auxMemoryForNodes[index]->leftN = NULL;
    auxMemoryForNodes[index]->rightN = NULL;
    int myIndex = index;
    index++;

    auxMemoryForNodes[index]->leftN = initMemoryRec(memoryAddress, memorySize / 2, height - 1);
    auxMemoryForNodes[index]->rightN = initMemoryRec(memoryAddress + (memorySize / 2), memorySize / 2, height - 1); //TODO ver si hay que pasarle un +1 o un -1 a la dirección de memoria

    // if (auxMemoryForNodes[index].leftN == NULL && auxMemoryForNodes[index].rightN == NULL)
    // {
    //     printf("HIJO DE %d es null", count++);
    // }

    return auxMemoryForNodes[myIndex];
}

int getMinBlockSize(int sizeOfMemoryRequested)
{
    int i = MEMORY_SIZE;
    for (; i >= SMALLEST_BLOCK_SIZE; i = i / 2)
    {
        printf("Valor de i %d valor pedido %d \n", i, sizeOfMemoryRequested);
        if (sizeOfMemoryRequested >= i)
        {
            return i * 2;
        }
    }
    return SMALLEST_BLOCK_SIZE; // ERROR!
}

void *mallocNUESTRO(int size)
{
    if (initialized == 0)
    {
        initializeMemory();
        initialized++;
    }
    int sizeBlockRequired = getMinBlockSize(size);

    if (sizeBlockRequired > MEMORY_SIZE)
    {
        return NULL; // No se puede alocar tanta memoria
    }
    return searchMemoryRec(&auxMemoryForNodes[0], sizeBlockRequired);
}

void *searchMemoryRec(node *n, int sizeRequired)
{

    if (n->isFree)
    {
        printf("ENTRO 1 tamanio de este bloque %d \n", n->sizeOfMemory);

        if (n->sizeOfMemory == sizeRequired)
        {
            n->isFree = 0;
            return n->startOfMemoryAddress;
        }
    }

    if (sizeRequired > n->sizeOfMemory || (n->isFree == 0 && sizeRequired == n->sizeOfMemory))
    {
        printf("ENTRO 2\n");
        return NULL;
    }

    if (n->isFree && sizeRequired < n->sizeOfMemory)
    {
        printf("ACA 1_____\n");
        node *auxLeft = n->leftN;
        printf("ACA 2 \n");
        node *auxRight = n->rightN;
        printf("ENTRO 3 tamanio del hijo izq %d, hijo der %d \n", auxLeft->sizeOfMemory, auxRight->sizeOfMemory);
        char *toRet = NULL;
        toRet = searchMemoryRec(n->leftN, sizeRequired);
        if (toRet == NULL)
        {
            toRet = searchMemoryRec(n->rightN, sizeRequired);
        }
        if (toRet != NULL)
        {
            n->isFree = 0;
        }
        else
        {
            printf("Retorno un nodo invalido\n");
        }
        return toRet;
    }
    printf("ACA NO DEBO ESTAR \n ");
    return NULL;
}

int main(int argc, char *argv[])
{
    printf("Todavia no inicialice toda la memoria \n");
    initializeMemory();
    printf("Ya inicialice toda la memoria \n");
    char *ptr;
    // int i;
    // int j = 0;
    ptr = mallocNUESTRO(255);
    printf("Ya di el primero \n");
    if (ptr == NULL)
    {
        printf("No pude asignar memoria primer caso!\n");
    }

    char *ptr2;
    ptr2 = mallocNUESTRO(5);
    if (ptr2 == NULL)
    {
        printf("No pude asignar memoria segundo caso!\n");
    }
    char *ptr3;
    ptr3 = mallocNUESTRO(5);
    if (ptr3 == NULL)
    {
        printf("No pude asignar memoria tercer caso!\n");
    }
    char *ptr4;
    ptr4 = mallocNUESTRO(5);
    if (ptr4 == NULL)
    {
        printf("No pude asignar memoria cuarta caso!\n");
    }
    char *ptr5;
    ptr5 = mallocNUESTRO(5);
    if (ptr5 == NULL)
    {
        printf("No pude asignar memoria quinto caso!\n");
    }
    char *ptr6;
    ptr6 = mallocNUESTRO(5);
    if (ptr6 == NULL)
    {
        printf("No pude asignar memoria sexto caso!\n");
    }

    printf("Ya DI toda la memoria \n");
    printf("Voy a liberar la memoria \n");
    printf("%d valor del ptr sin mover \n", ptr);

    // freeMemory(ptr);
    // printf("Libero 1 \n ");

    // freeMemory(ptr2);
    // printf("Libero 2 \n");
    // freeMemory(ptr3);
    // printf("Libero 3 \n");
    // freeMemory(ptr3);
    // ptr3 = dummy_malloc_with_blocks(10); // NO SE LIBERAN
    // printf("Libero 3 DEVUELTA\n");
    // freeMemory(ptr4);
    // printf("Libero 4 \n");
    // freeMemory(ptr5);
    // printf("Libero 5 \n");
    // printf("%d valor del ptr 6 sin mover \n", ptr6);
    // freeMemory(ptr6);
    // printf("LIBERO TODO MENOS 10 bloques que me pidio el ptr3\n");
    // // //
    // for (i = 0; i < CANTBLOCKS; i++)
    // {
    //     printf("Is FREE= %d con ID: %d con start: %d \n", bitMapMemory[i].isFree, bitMapMemory[i].id_request, bitMapMemory[i].start);
    // }
    // //
    // printf("Ya LIBERE toda la memoria \n");
    return 0;
}
