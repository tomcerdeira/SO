#include <pipe.h>

int globalFD = 3; // 2 es stdin y 1 stdout
pipe pipes[CANT_OF_PIPES] = {{0}};

void initPipes()
{
    pipe auxPipe;
    auxPipe.readIndex = 0;
    auxPipe.writeIndex = 0;
    auxPipe.fd = 0;
    auxPipe.isFree = FREE;
    auxPipe.buffer = 0;
    auxPipe.cantOfProcessesConsuming = 0;
    int i = 0;
    for (; i < CANT_OF_PIPES; i++)
    {
        pipes[i] = auxPipe;
    }
}

int getFreePipe()
{
    int i = 0;
    for (; i < CANT_OF_PIPES; i++)
    {
        if (pipes[i].isFree)
        {
            return i;
        }
    }
    return -1;
}

void createNewPipe(int *fd)
{
    int index = getFreePipe();
    if (index < 0)
    {
        print("ENTRO CASO ERROR", 0x000000, 0xFFFFFF);
        *fd = -1;
        return index; // NO HAY PIPES
    }
    pipe newPipe;
    newPipe.buffer = mallocNUESTRO(SIZE_OF_PIPE);
    newPipe.fd = globalFD++;
    newPipe.isFree = NOT_FREE;
    newPipe.cantOfProcessesConsuming++;
    int * retValue = 0;
    newPipe.sem = semOpen("prueba",1,retValue);

    pipes[index] = newPipe;
   
    *fd = pipes[index].fd;
}

int getPipeByFD(int fd)
{
    int i = 0;
    for (; i < SIZE_OF_PIPE; i++)
    {
        if (pipes[i].fd == fd)
        {
            return i;
        }
    }
    return -1;
}

void closePipe(int fd)
{
    int index = getPipeByFD(fd);

    if (index < 0)
    {
        return; //ERROR : fd NO existe
    }

    pipes[index].cantOfProcessesConsuming--;
    if (pipes[index].cantOfProcessesConsuming == 0) //Si no hay más procesos con el pipe, se libera
    {
        pipes[index].isFree = FREE;
        freeMemory(pipes[index].buffer);
        pipes[index].readIndex = 0;
        pipes[index].writeIndex = 0;
    }
}

void writePipe(int fd, char *buffer)
{
    int index = getPipeByFD(fd);

    if (index < 0)
    {
        return; //ERROR : fd NO existe
    }


    int buffLength = strlen(buffer);

    // print(buffer,0x000000,0xC0DE);

    if (buffLength > SIZE_OF_PIPE) //Como el buffer es circular, si se escribe algo más grande se escribe el final
    {
        int diff = buffLength - SIZE_OF_PIPE;
        buffLength = SIZE_OF_PIPE;
        buffer += diff;
    }
    // print("WAIT WRITE",0xDEAD,0xC0DE);
    mySemWait(pipes[index].sem->name);
    // print("Salgo wait WRITE",0xDEAD,0xC0DE);

    if (pipes[index].writeIndex + buffLength > SIZE_OF_PIPE)
    {
        // logica de circularidad
        int lastPartLength = SIZE_OF_PIPE - pipes[index].writeIndex;
        memcpy(pipes[index].buffer + pipes[index].writeIndex, buffer, lastPartLength);
        pipes[index].writeIndex = 0;
        int sizeLeftToWrite = buffLength - lastPartLength;
        memcpy(pipes[index].buffer, buffer + lastPartLength, sizeLeftToWrite);
        pipes[index].writeIndex += sizeLeftToWrite;
    }
    else
    {
        memcpy(pipes[index].buffer + pipes[index].writeIndex, buffer, buffLength);
        pipes[index].writeIndex += buffLength;
    }
    mySemPost(pipes[index].sem->name);
    //print(pipes[index].buffer, 0xFF0000, 0x000000);
}

int readPipe(char *buffer, int size, int fd)
{
    int index = getPipeByFD(fd);

    if (index < 0)
    {
        return -1;
    }   
    // print(buffer,0x3232,0xFFFFF);
    int i = 0;
    // if(pipes[index].readIndex == pipes[index].writeIndex){
    mySemWait(pipes[index].sem->name);
    //print("Salgo wait read",0xDEAD,0xC0DE);
    for (; i < SIZE_OF_PIPE && i<size && pipes[index].buffer[i]!=0; i++)
    {
        if (pipes[index].readIndex == pipes[index].writeIndex )
        {
           
             mySemPost(pipes[index].sem->name);
            return i; // Aca termina
        }
        buffer[i] = pipes[index].buffer[pipes[index].readIndex];
        pipes[index].readIndex++;
        pipes[index].readIndex %= SIZE_OF_PIPE;
    }
    //buffer[i+1] = 0;
    // memcpy(buffer, pipes[i].buffer, 256);
    // print(buffer, 0x000000, 0xFFFFFF);
    mySemPost(pipes[index].sem->name);
   // print("POST READ", 0xCAFE, 0xC0DE);
    // }
    return i;
}

void pipesInfo(char *buffer)
{
    int i = 0;
    int j = 0;

    char *header = "Read\tWrite\tFD\t\tCant. proc\n";

    memcpy(buffer, header, strlen(header));
    j = strlen(header);

    for (; i < CANT_OF_PIPES; i++)
    {
        if (!pipes[i].isFree)
        {
            //Read
            char auxRead[1];
            numToStr(auxRead, pipes[i].readIndex);
            memcpy(buffer + j, auxRead, strlen(auxRead));
            j += strlen(auxRead);
            memcpy(buffer + j, "\t\t\t\t\t\t", strlen("\t\t\t\t\t\t"));
            j += strlen("\t\t\t\t");

            //Write
            char auxWrite[1];
            numToStr(auxWrite, pipes[i].writeIndex);
            memcpy(buffer + j, auxWrite, strlen(auxWrite));
            j += strlen(auxWrite);
            memcpy(buffer + j, "\t\t\t\t\t\t", strlen("\t\t\t\t\t\t"));
            j += strlen("\t\t\t\t\t\t");

            //FD
            char auxFD[2];
            numToStr(auxFD, pipes[i].fd);
            memcpy(buffer + j, auxFD, strlen(auxFD));
            j += strlen(auxFD);
            memcpy(buffer + j, "\t\t\t", strlen("\t\t\t"));
            j += strlen("\t\t\t");

            memcpy(buffer + j, "\t\t\t", strlen("\t\t\t"));
            j += strlen("\t\t\t");

            //Cant of processes
            char auxCant[10];
            numToStr(auxCant, pipes[i].cantOfProcessesConsuming);
            memcpy(buffer + j, auxCant, strlen(auxCant));
            j += strlen(auxCant);

            memcpy(buffer + j, "\n", strlen("\n"));
            j += strlen("\n");
        }
    }
}
//// FUNCION AUX BORRAR /////

// char * getBuffOf(char * buff, int fd){
//     int i=0;
//     for(;i<CANT_OF_PIPES;i++)
//     {
//         if(pipes[i].fd==fd)
//         {
//             //buff = pipes[i].buffer;
//             memcpy(buff, pipes[i].buffer, 256);
//             //print(buff, 0x000000, 0xFFFFFF);
//         }
//     }
//     return -1;

// }