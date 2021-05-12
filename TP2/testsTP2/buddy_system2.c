//// includes......
#include <stdio.h>
#define MAX_HEIGHT 8 //VERRRR!

#define MEMORY_SIZE 1024
#define SMALLEST_BLOCK_SIZE 4
// #define NULL 0
#define CANT_NODES 511 // DESHARCODEAR

char start[MEMORY_SIZE] = {'\0'};

int initialized = 0;

typedef struct
{
    int id;
    //int isFree;    //1 FREE - 0 NOT Free
    //int rightIsFree;
    //int leftIsFree;
    int isSplited; //1 YES - 0 NO
    char *startOfMemoryAddress;
    int sizeOfMemory;
    int sizeOfMemoryFree;
    struct node *leftN;
    struct node *rightN;
} node;

node auxMemoryForNodes[CANT_NODES] = {{0}};
int index = 0;
node * initMemoryRec(char *memoryAddress, int memorySize, int height);
void *mallocNUESTRO(int size);
int getMinBlockSize(int sizeOfMemoryRequested);
void *searchMemoryRec(node *n, int sizeRequired);


void initializeMemory()
{
    initMemoryRec(start, MEMORY_SIZE, MAX_HEIGHT);
    if (auxMemoryForNodes[0].leftN == NULL || auxMemoryForNodes[0].rightN == NULL)
    {
        printf("ERROR HIJOS DE ROOT NULL \n");
    }
    initialized++;  
}

int count = 0;

node * initMemoryRec(char *memoryAddress, int memorySize, int height)
{
    if (height == 0) // Llegamos al ultimo nivel
    {
        //printf("Llego al height MAX %d\n", count++);
        return NULL;
    }
   // printf("Is free %d\n", &auxMemoryForNodes[0]->isFree);
    
    node nodeAux;
    nodeAux.id = index;
 
    //nodeAux.isFree = 1;
    //nodeAux.rightIsFree =1;
    //nodeAux.leftIsFree =1;
    nodeAux.isSplited = 0;
    nodeAux.startOfMemoryAddress = memoryAddress;
    nodeAux.sizeOfMemory = memorySize;
    nodeAux.sizeOfMemoryFree = memorySize;
    
    nodeAux.leftN = NULL;
    nodeAux.rightN = NULL;
    
   // printf("llego a crear el nodo\n");
    int myIndex = index;
    index++;
    nodeAux.leftN = (initMemoryRec(memoryAddress, memorySize / 2, height - 1));
    nodeAux.rightN = (initMemoryRec(memoryAddress + (memorySize / 2), memorySize / 2, height - 1)); //TODO ver si hay que pasarle un +1 o un -1 a la dirección de memoria

   // auxMemoryForNodes[myIndex]->leftN = init

    auxMemoryForNodes[myIndex] = nodeAux;
   // printf("llego a asignar id con bloque de %d, index: %d\n",auxMemoryForNodes[myIndex].sizeOfMemory, myIndex);

    /// crear nodo
    //     node *Node = auxMemoryForNodes[index];
    // ///asignarle las cosas al nodo
    // /// auxMemoryForNodes[index] = &node;
    // printf("llego a crear el nodo\n");
    // Node->id= &index;
    // printf("llego a asignar id\n");
    // Node->isFree = 1;
    // Node->isSplited = 0;
    // Node->startOfMemoryAddress = memoryAddress;
    // Node->sizeOfMemory = memorySize;
    // Node->leftN = NULL;
    // Node->rightN = NULL;
    // int myIndex = index;
    // index++;

   
    // if (auxMemoryForNodes[index].leftN == NULL && auxMemoryForNodes[index].rightN == NULL)
    // {
    //     printf("HIJO DE %d es null", count++);
    // }

    return &(auxMemoryForNodes[myIndex]);
}

int getMinBlockSize(int sizeOfMemoryRequested)
{
    int i = MEMORY_SIZE;
    for (; i >= SMALLEST_BLOCK_SIZE; i = i / 2)
    {
        //printf("Valor de i %d valor pedido %d \n", i, sizeOfMemoryRequested);
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
  //  printf("MALLOC MEMORIA 0 %d\n",auxMemoryForNodes[0].sizeOfMemory);
    return searchMemoryRec((&auxMemoryForNodes[0]), sizeBlockRequired);
}

void *searchMemoryRec(node * n, int sizeRequired)
{
    //printf("SEARCH MEMORY REC tam mem %d , is free %d\n", n->sizeOfMemory,n->isFree);

    if (n->sizeOfMemoryFree == sizeRequired )
    {
     //   printf("ENTRO 1 tamanio de este bloque %d \n", n->sizeOfMemory);
        if (n->sizeOfMemory == sizeRequired)
        {
            n->sizeOfMemoryFree = 0;
            return n->startOfMemoryAddress;
        }
        return NULL;
    }
    char *toRet = NULL;
    if(n->sizeOfMemoryFree >= sizeRequired){
        node * auxNode= n->leftN;
        if(auxNode->sizeOfMemoryFree >= sizeRequired)
        {
            toRet = searchMemoryRec(n->leftN, sizeRequired);
            if(toRet != NULL){
                n->sizeOfMemoryFree -= sizeRequired;
                return toRet;
            }
        }

        auxNode = n->rightN;
        if(auxNode->sizeOfMemoryFree >= sizeRequired)
        {
            toRet = searchMemoryRec(n->rightN, sizeRequired);
            if(toRet != NULL){
                n->sizeOfMemoryFree -= sizeRequired;
                return toRet;
            }
        }

    }
    printf("DEBERIA ESTAR?? \n");

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
    ptr = mallocNUESTRO(256);

    if (ptr == NULL)
    {
        printf("No pude asignar memoria primer caso!\n");
    }else{
    printf("Ya di el primero \n");
    }
    char *ptr2;
    ptr2 = mallocNUESTRO(128);
    if (ptr2 == NULL)
    {
        printf("No pude asignar memoria segundo caso!\n");
    }else{
    printf("Ya di el segundo \n");
    }
    char *ptr3;
    ptr3 = mallocNUESTRO(16);
    if (ptr3 == NULL)
    {
        printf("No pude asignar memoria tercer caso!\n");
    }else{
    printf("Ya di el tercero \n");
    }
    char *ptr4;
    ptr4 = mallocNUESTRO(5);
    if (ptr4 == NULL)
    {
        printf("No pude asignar memoria cuarta caso!\n");
    }else{
    printf("Ya di el cuarto \n");
    }
    char *ptr5;
    ptr5 = mallocNUESTRO(5);
    if (ptr5 == NULL)
    {
        printf("No pude asignar memoria quinto caso!\n");
    }else{
    printf("Ya di el quinto \n");
    }
    char *ptr6;
    ptr6 = mallocNUESTRO(5);
    if (ptr6 == NULL)
    {
        printf("No pude asignar memoria sexto caso!\n");
    }else{
    printf("Ya di el sexto \n");
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
