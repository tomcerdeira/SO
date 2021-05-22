// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <buddy_system2.h>

static char *const start = (void *)0x600000;
int initialized = 0;
node auxMemoryForNodes[MAX_BLOCKS] = {{0}};
int index = 0;



void initializeMemory()
{
    initMemoryRec(start, MEMORY_SIZE, MAX_HEIGHT);
    if (auxMemoryForNodes[0].leftN == NULL || auxMemoryForNodes[0].rightN == NULL)
    {
        print("ERROR HIJOS DE ROOT NULL \n",0xFFFFFF,0x000000);
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
    nodeAux.leftN = (node *) (initMemoryRec(memoryAddress, memorySize / 2, height - 1));
    nodeAux.rightN = (node *) (initMemoryRec(memoryAddress + (memorySize / 2), memorySize / 2, height - 1)); 
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
    
    if (n->sizeOfMemoryFree >= sizeRequired ) 
    {
        if (n->sizeOfMemory == sizeRequired)
        {
            n->sizeOfMemoryFree = 0;
            return n->startOfMemoryAddress;
        }
       
    }
    char *toRet = NULL;
    if(n->sizeOfMemoryFree >= sizeRequired){
        node * auxNode= (node *) n->leftN;


        if(auxNode->sizeOfMemoryFree >= sizeRequired)
        {
            toRet = searchMemoryRec((node*) n->leftN, sizeRequired);
            if(toRet != NULL){
                n->sizeOfMemoryFree -= sizeRequired;
                return toRet;
            }
        }

        auxNode = (node *) n->rightN;
        if(auxNode->sizeOfMemoryFree >= sizeRequired)
        {
            toRet = searchMemoryRec((node *)n->rightN, sizeRequired);
            if(toRet != NULL){
                n->sizeOfMemoryFree -= sizeRequired;
                return toRet;
            }
        }
    
    }
    return NULL;
}

void freeMemory(char * ptr){
    int ret = freeMemoryRec(&(auxMemoryForNodes[0]),ptr);
    if (ret < 0)
    {
        print("NO SE PUDO LIBERAR LA MEMORIA\n",0xFFFFFF,0x000000);
    } 
}

int freeMemoryRec(node * n, char * ptr){

        if(ptr > (start + MEMORY_SIZE) && ptr < start){
            return -2; //ERROR
        }

        node *auxNodeLeft = (node *)n->leftN;
        node *auxNodeRight = (node *)n->rightN;

        // Si el ptr es de mi inicio y yo tengo 0 libre y mis hijos tienen memoria libre --> La di yo
        if(ptr == n->startOfMemoryAddress && n->sizeOfMemoryFree == 0)
        {
            if(n->leftN == NULL && n->rightN == NULL){
                n->sizeOfMemoryFree += n->sizeOfMemory;
                
                   return n->sizeOfMemoryFree;
            }else if (auxNodeLeft->sizeOfMemoryFree != 0 && auxNodeRight->sizeOfMemoryFree != 0) {
                n->sizeOfMemoryFree += n->sizeOfMemory;
            
                   return n->sizeOfMemoryFree;
            }
            
        }

        if(ptr < (n->startOfMemoryAddress + (n->sizeOfMemory/2)))
        {
            int retLeft = freeMemoryRec((node *)n->leftN, ptr);
            if (retLeft != -1)
            {
                n->sizeOfMemoryFree += retLeft;
                }
        
            return retLeft;
        }else{
            int retRight = freeMemoryRec((node *)n->rightN, ptr);
            if (retRight != -1)
            {
                n->sizeOfMemoryFree += retRight;
                }
            
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

void getMemoryInfo(char *buffer)
{

    int j = 0;

    char *header = "Total\t\tEn uso\tLibre\n";

    memcpy(buffer, header, strlen(header));
    j = strlen(header);

            //Total
            char auxTotal[6];
            numToStr(auxTotal, getTotalMemorySize());
            memcpy(buffer + j, auxTotal, strlen(auxTotal));
            j += strlen(auxTotal);
            memcpy(buffer + j, "\t\t\t", strlen("t\t\t"));
            j += strlen("\t\t\t");

            //En uso
            char auxUsed[2];
            numToStr(auxUsed, getMemoryUsed());
            memcpy(buffer + j, auxUsed, strlen(auxUsed));
            j += strlen(auxUsed);
            memcpy(buffer + j, "\t\t\t", strlen("\t\t\t"));
            j += strlen("\t\t\t");

            //Libre
            char auxFree[6];
            numToStr(auxFree, getMemoryAvailable());
            memcpy(buffer + j, auxFree, strlen(auxFree));
            j += strlen(auxFree);

            memcpy(buffer + j, "\n", strlen("\n"));
            j += strlen("\n");

}