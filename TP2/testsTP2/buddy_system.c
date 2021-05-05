// #include "includes.h"

#define MEMORY_SIZE 1024
#define NULL 0

char *start[MEMORY_SIZE] = {0};
//static char *const start = (void *)0x600000;

typedef struct node
{
    int id;
    int isFree;    //1 FREE - 0 NOT Free
    int isSplited; //1 YES - 0 NO
    char *startOfMemoryAddress;
    int sizeOfMemory;
    node *leftN;
    node *rightN;
} node;

node root;
int id = 0;

void initBuddyMalloc()
{
    node rootAux;
    rootAux.id = id++;
    rootAux.isFree = 1;
    rootAux.isSplited = 0;
    rootAux.startOfMemoryAddress = start;
    rootAux.sizeOfMemory = MEMORY_SIZE;
    rootAux.leftN = NULL;
    rootAux.rightN = NULL;
    root = rootAux;
}

node *newNode(int size, char *memory)
{
}

node *splitTree(int sizeOfMemoryNeeded) //entra una potencia de 2
{
    if (root.isFree)
    {
        if (root.sizeOfMemory == sizeOfMemoryNeeded)
        {
            root.isFree = 0;
            return &root;
        }
        if (!root.isSplited)
        {
            root.leftN = newNode(root.sizeOfMemory / 2, root.startOfMemoryAddress);
            root.rightN = newNode(root.sizeOfMemory / 2, root.startOfMemoryAddress + root.sizeOfMemory / 2); /// Podria ir un -1 o +1
            root.isSplited = 1;
            root.isFree = 0;
            // creo hijos
        }
    }
    else if (root.sizeOfMemory < sizeOfMemoryNeeded || (root.isFree == 0 && root.leftN == NULL && root.rightN == NULL))
    {
        return -1; //El bloque mas grande (toda la memoria) esta ocupada
    }

    char *toRet = 0;
    toRet = splitTreeRec(root.leftN, sizeOfMemoryNeeded);
    if (toRet == NULL)
    {
        toRet = splitTreeRec(root.rightN, sizeOfMemoryNeeded);
    }
    return toRet;

    // splitTreeRec(root, sizeOfMemoryNeeded);
    // if (root.isFree)
    // {
    //     if (root.sizeOfMemory == sizeOfMemoryNeeded)
    //     {
    //         //Encontré
    //     } else {
    //         root.leftN = newsplitTreeRecNode(root.leftN ,root.sizeOfMemory / 2);
    //         root.rightN = newNode(root.sizeOfMemory / 2);
    //         root.isFree = 0;
    //     }
    //encontré el bloque que necesito
}

char *splitTreeRec(node *n, int sizeOfMemoryNeeded)
{
    if (n->isFree)
    {
        if (n->sizeOfMemory == sizeOfMemoryNeeded)
        {
            return n->startOfMemoryAddress;
        }
        if (!n->isSplited)
        {
            n->leftN = newNode(n->sizeOfMemory / 2, n->startOfMemoryAddress);
            n->rightN = newNode(n->sizeOfMemory / 2, n->startOfMemoryAddress + n->sizeOfMemory / 2); /// Podria ir un -1 o +1
            n->isSplited = 1;
            n->isFree = 0;
            // creo hijos
        }
    }
    else if (n->sizeOfMemory < sizeOfMemoryNeeded || (n->isFree == 0 && n->isSplited == 0))
    {
        return NULL; //El bloque mas grande (toda la memoria) esta ocupada
    }
    // no libre pero divido
    char *toRet = 0;
    toRet = splitTreeRec(n->leftN, sizeOfMemoryNeeded);
    if (toRet == NULL)
    {
        toRet = splitTreeRec(n->rightN, sizeOfMemoryNeeded);
    }
    return toRet;

    // if(n == NULL){
    //     node newN = newNode(sizeN);
    // }
    // if (n.isFree)
    // {
    //     if (n.sizeOfMemory == sizeOfMemoryNeeded)
    //     {
    //         return &n;
    //     }
    //     else if (n.sizeOfMemory > sizeOfMemoryNeeded)
    //     {
    //         n.leftN = splitTreeRec(newNode(n.sizeOfMemory / 2), sizeOfMemoryNeeded);
    //         if(n.leftN == -1){
    //             n.rightN = splitTreeRec(newNode(n.sizeOfMemory / 2), sizeOfMemoryNeeded);
    //         }

    //         n.isFree = 0;
    //     }else{
    //         return NULL;
    //     }
    //     //encontré el bloque que necesito
    // }
    // return -1;
}

//1°: entra un size
//2°: ese size lo va comparando con bloques de potencias de 2
//ir partiendo la memoria libre de a bloques de potencias de 2

int getMinBlockSize(int sizeOfMemoryRequested)
{
    int i = MEMORY_SIZE;
    for (; i >= 0; i / 2)
    {
        if (sizeOfMemoryRequested >= i)
        {
            return i * 2;
        }
    }
    return -1; // ERROR!
}

//
//              malloc()
//                  int cantidadMemoria= parseaLaCantidad (getMin....)
//                  char * toRet = splitTree(cantidadMemoria)
//                  return toRet;
//
//

// void *mallocPowersOfTwo(int sizeOf)
// {
//     int i = MEMORY_SIZE;

//     for (; i >= 0; i / 2)
//     {
//         if (sizeOf >= i)
//         {
//             return mallocNUESTRO(i * 2);
//         }
//     }
//     return NULL; // ERROR!
// }