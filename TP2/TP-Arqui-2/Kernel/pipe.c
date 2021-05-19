#include <pipe.h>

int globalFD = 3; // 2 es stdin y 1 stdout
pipe pipes[CANT_OF_PIPES] = {{0}};

void initPipes()
{
    pipe auxPipe;
    auxPipe.readIndex = 0;
    auxPipe.writeIndex = 0;
    auxPipe.fd = 0;
    auxPipe.isFree = 1;
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
    newPipe.isFree = 0;
    newPipe.cantOfProcessesConsuming++;

    pipes[index] = newPipe;
    printBase(pipes[index].fd, 10);
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
        pipes[index].isFree = 1;
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
}

int readPipe(char *buffer, int size, int fd)
{
    int index = getPipeByFD(fd);

    if (index < 0)
    {
        return -1;
    }

    int i = 0;
    for (; i < SIZE_OF_PIPE; i++)
    {
        if (pipes[index].readIndex == pipes[index].writeIndex)
        {
            return i; // Aca termina
        }
        buffer[i] = pipes[index].buffer[pipes[index].readIndex];
        pipes[index].readIndex++;
        pipes[index].readIndex %= SIZE_OF_PIPE;
    }
    return i;
}
