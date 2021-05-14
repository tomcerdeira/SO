//// includes......
#include "buddy_system2.h"

char start[MEMORY_SIZE] = {'\0'};

int initialized = 0;



node auxMemoryForNodes[CANT_NODES] = {{0}};
int index = 0;



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
    if (height == -1) // Llegamos al ultimo nivel, es -1 porque al nivel 0 todavía quedan los bloques de tamaño 4
    {
        return NULL;
    }
    
    node nodeAux;
    nodeAux.id = index;
    nodeAux.isSplited = 0;
    nodeAux.startOfMemoryAddress = memoryAddress;
    nodeAux.sizeOfMemory = memorySize;
    nodeAux.sizeOfMemoryFree = memorySize;
    nodeAux.leftN = NULL;
    nodeAux.rightN = NULL;
    
    int myIndex = index;
    index++;
    nodeAux.leftN = (initMemoryRec(memoryAddress, memorySize / 2, height - 1));
    nodeAux.rightN = (initMemoryRec(memoryAddress + (memorySize / 2), memorySize / 2, height - 1)); //TODO ver si hay que pasarle un +1 o un -1 a la dirección de memoria
    auxMemoryForNodes[myIndex] = nodeAux;
       return &(auxMemoryForNodes[myIndex]);
}

int getMinBlockSize(int sizeOfMemoryRequested)
{
    int i = MEMORY_SIZE;
    for (; i >= SMALLEST_BLOCK_SIZE; i = i / 2)
    {
        if (sizeOfMemoryRequested > i)
        {
            return i*2;
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
    return searchMemoryRec((&auxMemoryForNodes[0]), sizeBlockRequired);
}

void *searchMemoryRec(node * n, int sizeRequired)
{
    //printf("%d size \t",sizeRequired);
    if (n->sizeOfMemoryFree >= sizeRequired ) //CAMBIE == POR >=
    {
        if (n->sizeOfMemory == sizeRequired)
        {
            n->sizeOfMemoryFree = 0;
            return n->startOfMemoryAddress;
        }
        //return NULL;
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
    //printf("No hay memoria para %d\n", sizeRequired); //Si llega acá es porque no tiene memoria suficiente para lo solicitado
    return NULL;
}

void freeMemory(char * ptr){
    int ret = freeMemoryRec(&(auxMemoryForNodes[0]),ptr);
    if (ret < 0)
    {
        printf("NO SE PUDO LIBERAR LA MEMORIA\n");
    } 
}

int freeMemoryRec(node * n, char * ptr){

        if(ptr > (start + MEMORY_SIZE) && ptr < start){
            return -2; //ERROR
        }

        node * auxNodeLeft= n->leftN;  
         node * auxNodeRight= n->rightN;      

        // Si el ptr es de mi inicio y yo tengo 0 libre y mis hijos tienen memoria libre --> La di yo
        if(ptr == n->startOfMemoryAddress && n->sizeOfMemoryFree == 0)
        {
            if(n->leftN == NULL && n->rightN == NULL){
                n->sizeOfMemoryFree += n->sizeOfMemory;
                //printf("entro 1\n");
                   return n->sizeOfMemoryFree;
            }else if (auxNodeLeft->sizeOfMemoryFree != 0 && auxNodeRight->sizeOfMemoryFree != 0) {
                n->sizeOfMemoryFree += n->sizeOfMemory;
                //printf("entro 2\n");
                   return n->sizeOfMemoryFree;
            }
            //printf("Se libero %d memoria mios y el valor del ptr es %d y izqFree:%d, derFree %d \n",n->sizeOfMemoryFree,ptr,auxNodeLeft->sizeOfMemoryFree,auxNodeRight->sizeOfMemoryFree );
          
        }

        if(ptr < (n->startOfMemoryAddress + (n->sizeOfMemory/2)))
        {
            int retLeft = freeMemoryRec(n->leftN,ptr);
                if(retLeft != -1){
                    n->sizeOfMemoryFree += retLeft;
                }
                //printf("Se libero %d memoria de mi hijo izquierdo \n",retLeft);
            return retLeft;
        }else{
              int retRight = freeMemoryRec(n->rightN,ptr);
                if(retRight != -1){
                    n->sizeOfMemoryFree += retRight;
                }
                //printf("Se libero %d memoria hijo derecho\n",retRight);
            return retRight;
        }
        return -1;
    }

    int getTotalMemorySize()
    {
        return MEMORY_SIZE;
    }

    int getMemoryAvailable()
    {
        return auxMemoryForNodes[0].sizeOfMemoryFree;
    }

    int getMemoryUsed()
    {
        return (getTotalMemorySize() - getMemoryAvailable());
    }


void *memsetNUESTRO(char *ptr, int toWrite, int size)
{
    int i=0;
    for(;i<size;i++){
        ptr[i]= toWrite;
    }
    return ptr;
}


// int main(int argc, char *argv[])
// {
//     printf("Todavia no inicialice toda la memoria \n");
//     initializeMemory();
//     printf("Ya inicialice toda la memoria \n");
//     char *ptr;
//     // int i;
//     // int j = 0;
//     ptr = mallocNUESTRO(512);
//
//     if (ptr == NULL)
//     {
//         printf("No pude asignar memoria primer caso!\n");
//     }else{
//     printf("Ya di el primero \n");
//     }
//     char *ptr2;
//     ptr2 = mallocNUESTRO(256);
//     if (ptr2 == NULL)
//     {
//         printf("No pude asignar memoria segundo caso!\n");
//     }else{
//     printf("Ya di el segundo \n");
//     }
//     char *ptr3;
//     ptr3 = mallocNUESTRO(256);
//     if (ptr3 == NULL)
//     {
//         printf("No pude asignar memoria tercer caso!\n");
//     }else{
//     printf("Ya di el tercero \n");
//     }
//     char *ptr4;
//     ptr4 = mallocNUESTRO(256);
//     if (ptr4 == NULL)
//     {
//         printf("No pude asignar memoria cuarta caso!\n");
//     }else{
//     printf("Ya di el cuarto \n");
//     }
//     char *ptr5;
//     // ptr5 = mallocNUESTRO(5);
//     // if (ptr5 == NULL)
//     // {
//     //     printf("No pude asignar memoria quinto caso!\n");
//     // }else{
//     // printf("Ya di el quinto \n");
//     // }
//     char *ptr6;
//     // ptr6 = mallocNUESTRO(5);
//     // if (ptr6 == NULL)
//     // {
//     //     printf("No pude asignar memoria sexto caso!\n");
//     // }else{
//     // printf("Ya di el sexto \n");
//     // }

//     printf("Ya DI toda la memoria \n");
//     printf("Voy a liberar la memoria \n");
//     printf("%d valor del ptr sin mover \n", ptr);

//     freeMemory(ptr);
//     printf("Libero 1 \n ");

//     freeMemory(ptr2);
//     printf("Libero 2 \n");
//     freeMemory(ptr3);
//     printf("Libero 3 \n");
//     // freeMemory(ptr3);
//     // ptr3 = dummy_malloc_with_blocks(10); // NO SE LIBERAN
//     // printf("Libero 3 DEVUELTA\n");
//     freeMemory(ptr4);
//     printf("Libero 4 \n");
//     freeMemory(ptr5);
//     printf("Libero 5 \n");
//     printf("%d valor del ptr 6 sin mover \n", ptr6);
//     freeMemory(ptr6);
//     printf("LIBERO TODO MENOS 10 bloques que me pidio el ptr3\n");
//     // //
//     // for (i = 0; i < CANTBLOCKS; i++)
//     // {
//     //     printf("Is FREE= %d con ID: %d con start: %d \n", bitMapMemory[i].isFree, bitMapMemory[i].id_request, bitMapMemory[i].start);
//     // }
//     // //
//     // printf("Ya LIBERE toda la memoria \n");
//
//     return 0;
 //}
