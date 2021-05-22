#include <scheduler.h>

#define MATADO 0
#define ACTIVO 1
#define BLOQUEADO 2
#define CANT_PROCESS 10
#define STACK_SIZE 4096
#define TIME_SLOT 3
#define SHELL_POSITION 0
#define FD_STDIN 1
#define FD_STOUT 2
#define NOT_SETED -1

process processes[CANT_PROCESS] = {{0}};
process halter;

int currentProcessIndex = 0;

int cantOfActiveProcesses = 0;
int firstTimeEntering = 1;
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
char bufferHalter[STACK_SIZE]={0};

void createprocesses()
{
    // process procHalter;
    halter.function = &halterProcess;
    halter.name = "Halter";
    halter.pid = globalPid++;
    halter.state = ACTIVO;
    halter.timeSlot = 1;
    halter.timeRunnig = 0;
    halter.memory = bufferHalter;
    // halter.memory =  mallocNUESTRO(STACK_SIZE);
    halter.stackPointer = initStack(halter.memory + STACK_SIZE, wrapper, halter.function, NULL, NULL, halter.pid);
    // halter = procHalter;

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
                cantOfActiveProcesses++;
                return;
            }
            processes[i].state = BLOQUEADO;
            cantOfActiveProcesses--;
            return;
        }
    }
    timerTickInterrupt();
}

void unblockReaders()
{
    foregroundProcess.state = ACTIVO;
    //print("LLEGO", 0xFFFFFF, 0x000000);
    if (foregroundProcess.pid == processes[SHELL_POSITION].pid)
    {
        processes[SHELL_POSITION].state = ACTIVO;
        //   print(ps, 0xFFFFFF, 0x000000);
    }
    cantOfActiveProcesses++;
}
void blockReader(int pid)
{
    foregroundProcess.state = BLOQUEADO;

    if (pid == processes[SHELL_POSITION].pid)
    {
        processes[SHELL_POSITION].state = BLOQUEADO;
    }
    // if(cantOfActiveProcesses == 0){
    //     foo();
    // }
    cantOfActiveProcesses--;
    timerTickInterrupt();
}

// void foo(){}

int getAvailableProcess()
{
    int i = 0;
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
    //2
    int availableProcess = getAvailableProcess(); //0

    if (availableProcess < 0)
    {
        // ERROR --> No hay un lugar para el proceso nuevo
        return -1;
    }

    processes[availableProcess].function = func;
    processes[availableProcess].state = ACTIVO;
    processes[availableProcess].name = name;
    processes[availableProcess].pid = globalPid++;
    if(fdInputNextProcess == NOT_SETED ){
        processes[availableProcess].fdInput = FD_STDIN;
        processes[availableProcess].fdOutput = FD_STOUT;
    }else{
        processes[availableProcess].fdInput = fdInputNextProcess;
        processes[availableProcess].fdOutput = fdOutputNextProcess;
        fdInputNextProcess = NOT_SETED; //Reseteo para el próximo proceso que se cree
        fdOutputNextProcess = NOT_SETED;
    }

    
    processes[availableProcess].timeSlot = TIME_SLOT;

    //processes[prio_name][availableProcess].memory = processMemory[prio_name][availableProcess]; // Habria que liberarla una vez matado el proceso
    processes[availableProcess].memory = mallocNUESTRO(STACK_SIZE);

    processes[availableProcess].stackPointer = initStack(processes[availableProcess].memory + STACK_SIZE,
                                                         wrapper, processes[availableProcess].function, argc, argv, processes[availableProcess].pid);
    // setProcessPriority(&processes[availableProcess]); //?/

    cantOfActiveProcesses++;
    if (isForeground)
    {
        foregroundProcess = processes[availableProcess];
    }
    return processes[availableProcess].pid;
}

void wrapper(void *func(int, char **), int argc, char *argv[], int pid)
{
    int retValue;
    retValue = (int)(*func)(argc, argv); // --> return --> wrapper -->  kill (libere todo) --> return a shell
                                         // exit -->kill (libere todo) --> return a padre
    // print("Salgo del proceso",0xFF,0x32);
    exit(retValue);
}

uint64_t *sched(uint64_t *rsp)
{
    if (cantOfActiveProcesses == 0)
    {
        if (firstTimeEntering)
        {
            rspKernel = rsp;
            return rspKernel;
        }
        else
        {
            int t = 0;
            int flagHalter = 1;
            for (; t < CANT_PROCESS; t++)
            {
                if (processes[t].state == ACTIVO)
                {
                    flagHalter = 0;
                }
            }
            if (flagHalter)
            {
                // if (currentProcessIndex != -1)
                // {
                //     processes[currentProcessIndex].stackPointer = rsp;
                // }else{
                //     halter.stackPointer = rsp;
                // }
                // print("RETURN HALTER EN SCHED", 0x32, 0xFE);
                // char bufferAux[1023] = {0};
                // ps(bufferAux);
                // print(bufferAux, 0x00000, 0xFFFFFF);
                // flagHalter = 1;
                //currentProcessIndex = -1;
                return halter.stackPointer;
            }
        }
    }
    // else
    // {
    if (!firstTimeEntering ) // Esto es para que un proceso se actualice el SP.
    {
        processes[currentProcessIndex].stackPointer = rsp;
    }
    firstTimeEntering = 0;
    if (processes[currentProcessIndex].timeSlot > processes[currentProcessIndex].timeRunnig && processes[currentProcessIndex].state == ACTIVO)
    {
        processes[currentProcessIndex].timeRunnig++;
        return processes[currentProcessIndex].stackPointer;
    }
  
    int auxIndex = currentProcessIndex + 1;
    int j = 0;
    if (!strcompare(foregroundProcess.name, "shell"))
    {
        processes[SHELL_POSITION].state = BLOQUEADO;
    }
    for (; j <= CANT_PROCESS; j++, auxIndex++)
    {
        if (processes[auxIndex % CANT_PROCESS].state == ACTIVO)
        {
            // if(currentProcessIndex !=-1){
                 processes[currentProcessIndex].timeRunnig = 0;
            // }
           
            currentProcessIndex = auxIndex % CANT_PROCESS;
            return processes[currentProcessIndex].stackPointer;
        }
    }
    // }
   // print("_______ACA NO DEBERIA ESTAR________", 0xFF, 0xDA);
    // halter.stackPointer = rsp;
    //  if(currentProcessIndex == -1){
    //      halter.stackPointer = rsp;
    //  }
    return halter.stackPointer;

    // Tira warning pero nunca llega aca (al menos no deberia)
}

// void bar(){}

void kill(int pid)
{
    int pos = 0;
    for (; pos < CANT_PROCESS; pos++)
    {
        if (processes[pos].state != MATADO && processes[pos].pid == pid && !strcompare(processes[pos].name, "shell"))
        {
            processes[pos].state = MATADO;
            freeMemory(processes[pos].memory);
            foregroundProcess = processes[SHELL_POSITION];
            processes[SHELL_POSITION].state = ACTIVO;

            cantOfActiveProcesses--;
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

void setFDNextNewProcess(int fdInput, int fdOutPut){
    fdInputNextProcess  = fdInput;
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
    for (; i < CANT_OF_PIPES; i++)
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