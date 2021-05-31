// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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
        return; // NO HAY PIPES
    }
    // pipe newPipe;
    pipes[index].buffer = mallocNUESTRO(SIZE_OF_PIPE);
    pipes[index].fd = globalFD++;
    pipes[index].isFree = NOT_FREE;
    pipes[index].cantOfProcessesConsuming++;
    int *retValue = 0;
    pipes[index].sem = semOpen("prueba", 1, retValue);

    // pipes[index] = newPipe;

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

    if (buffLength > SIZE_OF_PIPE) //Como el buffer es circular, si se escribe algo más grande se escribe el final
    {
        int diff = buffLength - SIZE_OF_PIPE;
        buffLength = SIZE_OF_PIPE;
        buffer += diff;
    }

    mySemWait(pipes[index].sem->name);

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
}

int readPipe(char *buffer, int size, int fd)
{
    int index = getPipeByFD(fd);

    if (index < 0)
    {
        return -1;
    }

    int i = 0;

    mySemWait(pipes[index].sem->name);
    for (; i < SIZE_OF_PIPE && i < size && pipes[index].buffer[i] != 0; i++)
    {
        if (pipes[index].readIndex == pipes[index].writeIndex)
        {

            mySemPost(pipes[index].sem->name);
            return i; // Aca termina
        }
        buffer[i] = pipes[index].buffer[pipes[index].readIndex];
        pipes[index].readIndex++;
        pipes[index].readIndex %= SIZE_OF_PIPE;
    }
    mySemPost(pipes[index].sem->name);
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
