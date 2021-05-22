#include <scheduler.h>

process processes[CANT_PROCESS] = {{0}};

int currentProcessIndex = -1;

//int firstTimeEntering = 1;
int rspKernel = 0;
int globalPid = 0;
process foregroundProcess = {0};
int fdInputNextProcess = NOT_SETED;
int fdOutputNextProcess = NOT_SETED;

// Version 1.0 de manejo de procesos

void halterProcess()
{
    while (1)
    {
        _hlt();
    }
    // unblockReaders();
    // block(1);
    timerTickInterrupt();
}

void createprocesses()
{

    int p = 0;
    for (; p < CANT_PROCESS; p++)
    {
        process proc;
        proc.pid = -1;
        //proc.memory = processMemory[prio][p];
        proc.memory = 0;
        proc.state = MATADO;
        proc.timeRunnig = 0;
        proc.timeSlot = 0;
        processes[p] = proc;
    }
}
void nice(int pid, int newTimeSlot)
{
    int i = 0;
    for (; i < CANT_PROCESS; i++)
    {
        if (processes[i].pid == pid)
        {
            processes[i].timeSlot = newTimeSlot;
            return;
        }
    }
}

void block(int pid)
{
    int i = 0;
    for (; i < CANT_PROCESS; i++)
    {
        if ((processes[i].state != MATADO) && processes[i].pid == pid && !strcompare(processes[i].name, "shell"))
        { //sacar lo de la shell
            if (processes[i].state == BLOQUEADO)
            {
                processes[i].state = ACTIVO;
                return;
            }
            processes[i].state = BLOQUEADO;
            timerTickInterrupt();
            return;
        }
    }
}

///////////////////////////////
void unblockMultiple(int *pids, int cant)
{
    int i = 0;
    for (; i < cant; i++)
    {
        processes[getIndexOfPid(pids[i])].state = ACTIVO;
    }
}

///////////////////////////////

void unblockReaders()
{
    foregroundProcess.state = ACTIVO;
    if (foregroundProcess.pid == processes[SHELL_POSITION].pid)
    {
        processes[SHELL_POSITION].state = ACTIVO;
    }
}
void blockReader(int pid)
{
    foregroundProcess.state = BLOQUEADO;

    if (pid == processes[SHELL_POSITION].pid)
    {
        processes[SHELL_POSITION].state = BLOQUEADO;
    }
    timerTickInterrupt();
}

int getAvailableProcess()
{
    int i = 1;
    for (; i < CANT_PROCESS; i++)
    {
        if (processes[i].state == MATADO)
        {
            return i;
        }
    }
    return -1;
}

int startProcess(char *name, void *func(int, char **), int argc, char *argv[], int isForeground)
//se fija entre todos los procesos, agarra uno que esté muerto/disponible, le asigna la tarea, lo activa,
{
    if (globalPid == 0)
    {
        process halter;
        halter.function = &halterProcess;
        halter.name = "Halter";
        halter.pid = globalPid++;
        halter.state = MATADO;
        halter.timeSlot = 1;
        halter.timeRunnig = 0;
        halter.memory = mallocNUESTRO(STACK_SIZE);
        halter.stackPointer = initStack(halter.memory + STACK_SIZE, wrapper, halter.function, NULL, NULL, halter.pid);
        processes[HALTER_POSITION] = halter;
        currentProcessIndex = CANT_PROCESS - 1;
        //firstTimeEntering =0;
    }

    int availableProcess = getAvailableProcess();

    if (availableProcess < 0)
    {
        // ERROR --> No hay un lugar para el proceso nuevo
        return -1;
    }

    processes[availableProcess].function = func;
    processes[availableProcess].state = ACTIVO;
    processes[availableProcess].name = name;
    processes[availableProcess].pid = globalPid++;
    if (fdInputNextProcess == NOT_SETED)
    {
        processes[availableProcess].fdInput = FD_STDIN;
        processes[availableProcess].fdOutput = FD_STOUT;
    }
    else
    {
        processes[availableProcess].fdInput = fdInputNextProcess;
        processes[availableProcess].fdOutput = fdOutputNextProcess;
        fdInputNextProcess = NOT_SETED; //Reseteo para el próximo proceso que se cree
        fdOutputNextProcess = NOT_SETED;
    }

    processes[availableProcess].timeSlot = TIME_SLOT;

    processes[availableProcess].memory = mallocNUESTRO(STACK_SIZE);

    processes[availableProcess].stackPointer = initStack(processes[availableProcess].memory + STACK_SIZE,
                                                         wrapper, processes[availableProcess].function, argc, argv, processes[availableProcess].pid);

    if (isForeground)
    {
        foregroundProcess = processes[availableProcess];
    }
    return processes[availableProcess].pid;
}

void wrapper(void *func(int, char **), int argc, char *argv[], int pid)
{
    int retValue;
    // WARNING: "cast from pointer to integer of different size"
    retValue = (int)(*func)(argc, argv); // --> return --> wrapper -->  kill (libere todo) --> return a shell
                                         // exit -->kill (libere todo) --> return a padre;
    exit(retValue);
}

uint64_t *sched(uint64_t *rsp)
{
    if (currentProcessIndex == -1)
    {
        return rsp;
    }
    else
    {
        processes[currentProcessIndex].stackPointer = rsp;

        if (processes[currentProcessIndex].state == ACTIVO && processes[currentProcessIndex].timeSlot > processes[currentProcessIndex].timeRunnig)
        {
            processes[currentProcessIndex].timeRunnig++;
            return processes[currentProcessIndex].stackPointer;
        }

        int i = currentProcessIndex + 1;
        int j = 0;
        for (; j < CANT_PROCESS; j++, i++)
        {
            if (processes[i % CANT_PROCESS].state == ACTIVO)
            {
                currentProcessIndex = i % CANT_PROCESS;
                return processes[i % CANT_PROCESS].stackPointer;
            }
        }
        currentProcessIndex = HALTER_POSITION;
        return processes[currentProcessIndex].stackPointer;
    }
}

// void bar(){}

void kill(int pid)
{
    int pos = 0;
    for (; pos < CANT_PROCESS; pos++)
    {
        if (processes[pos].pid == pid && !strcompare(processes[pos].name, "shell"))
        {
            processes[pos].state = MATADO;
            freeMemory(processes[pos].memory);
            processes[pos].pid = -1;
            processes[pos].function = 0;
            processes[pos].memory = 0;
            processes[pos].timeRunnig = 0;
            processes[pos].timeSlot = 0;

            if (foregroundProcess.pid == pid)
            {
                foregroundProcess = processes[SHELL_POSITION];
                processes[SHELL_POSITION].state = ACTIVO;
            }
        }
    }
}

void exit(int status)
{
    kill(processes[currentProcessIndex].pid);
    timerTickInterrupt();
}

int getPid()
{
    return processes[currentProcessIndex].pid;
}

void ps(char *buffer)
{
    int i = 0;
    int j = 0;

    char *header = "PID\tPRIO\tNAME\t\tSTACK\t\tSTATE\n";

    memcpy(buffer, header, strlen(header));
    j = strlen(header);

    for (; i < CANT_PROCESS; i++)
    {
        if (processes[i].state != MATADO)
        {
            //PID
            char auxPID[5];
            numToStr(auxPID, processes[i].pid);
            memcpy(buffer + j, auxPID, strlen(auxPID));
            j += strlen(auxPID);
            memcpy(buffer + j, "\t", strlen("\t"));
            j += strlen("\t");

            //Prioridad
            char auxPrio[5];
            numToStr(auxPrio, processes[i].timeSlot);
            memcpy(buffer + j, auxPrio, strlen(auxPrio));
            j += strlen(auxPrio);
            memcpy(buffer + j, "\t", strlen("\t"));
            j += strlen("\t");

            //Name
            memcpy(buffer + j, processes[i].name, strlen(processes[i].name));
            j += strlen(processes[i].name);
            memcpy(buffer + j, "\t", strlen("\t"));
            j += strlen("\t");

            memcpy(buffer + j, "\t", strlen("\t"));
            j += strlen("\t");

            //Stack
            char auxStack[10];
            numToStr(auxStack, processes[i].stackPointer);
            memcpy(buffer + j, auxStack, strlen(auxStack));
            j += strlen(auxStack);

            memcpy(buffer + j, "\t", strlen("\t"));
            j += strlen("\t");

            //Estado
            if (processes[i].state == ACTIVO)
            {
                memcpy(buffer + j, "A\n", strlen("A\n"));
            }
            else
            {
                memcpy(buffer + j, "B\n", strlen("A\n"));
            }
            j += strlen("A\n");
        }
    }
}

void setFDNextNewProcess(int fdInput, int fdOutPut)
{
    fdInputNextProcess = fdInput;
    fdOutputNextProcess = fdOutPut;
}

void yield()
{
    processes[currentProcessIndex].timeRunnig = processes[currentProcessIndex].timeSlot;
    timerTickInterrupt();
}

int currentProcessIsForeground()
{
    return processes[currentProcessIndex].pid == foregroundProcess.pid;
}

void getPidByName(char *name, int *pid)
{
    int i = 0;
    for (; i < CANT_PROCESS; i++)
    {
        if (strcompare(processes[i].name, name))
        {
            *pid = processes[i].pid;
            return;
        }
    }
    *pid = -1;
}

int getIndexOfPid(int pid)
{
    int i = 0;
    for (; i < CANT_PROCESS; i++)
    {
        if (processes[i].pid == pid)
        {
            return i;
        }
    }
    return -1;
}

void changeOutputFd(int pid, int fd)
{
    int index = getIndexOfPid(pid);
    if (index < 0)
    {
        return; //ERROR
    }
    processes[index].fdOutput = fd;
}

void changeInputFd(int pid, int fd)
{
    int index = getIndexOfPid(pid);
    if (index < 0)
    {
        return; //ERROR
    }
    processes[index].fdInput = fd;
}

int getFdOutput(int pid)
{
    int index = getIndexOfPid(pid);
    if (index < 0)
    {
        return; //ERROR
    }
    return processes[index].fdOutput;
}

int getFdInput(int pid)
{
    int index = getIndexOfPid(pid);
    if (index < 0)
    {
        return; //ERROR
    }
    return processes[index].fdInput;
}