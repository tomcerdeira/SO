#include <scheduler2.h>

#define KILLED 0
#define ACTIVE 1
#define BLOCKED 2
#define CANT_PROCESS 10
#define STACK_SIZE 4096
#define CANT_PRIO 3
#define DEATH_INNER_P -1
#define HALTER_POSITION 0
#define MAX_TIME_SLOT 10

typedef struct
{
    char *name;
    int pid;
    void *function;
    uint64_t *stackPointer;
    uint64_t *memory;
    int state;
    int timeSlot;
    int currentRunningTime;
} process;

int currentProcess = -1;
int cantProcesses = 0;
process processes[CANT_PROCESS];
int globalPID = 0;
int firstTime = 1;

void initScheduler()
{
    process halterProcess;
    halterProcess.pid = globalPID++;
    halterProcess.function = &(_hlt); //REV
    halterProcess.memory = mallocNUESTRO(STACK_SIZE);
    halterProcess.state = ACTIVE;
    halterProcess.timeSlot = 1;
    halterProcess.currentRunningTime = 0;
    halterProcess.stackPointer = initStack(halterProcess.memory + STACK_SIZE, wrapper, halterProcess.function, NULL, NULL, halterProcess.pid);
    processes[HALTER_POSITION] = halterProcess;
    cantProcesses = 1;

    int i = 1;

    for (; i < CANT_PROCESS; i++)
    {
        process p;
        p.state = KILLED;
        p.pid = 0;
        p.memory = 0;
    }
}

int chooseNextProcess()
{
    if (currentProcess != -1)
    {
        if (processes[currentProcess].currentRunningTime < processes[currentProcess].timeSlot && processes[currentProcess].state == ACTIVE)
        {
            return currentProcess; //Si no termino con su timeSlot, sigue corriendo el mismo proceso
        }
        int i = currentProcess + 1;
        int j = 0;
        for (; j < CANT_PROCESS; j++, i++)
        {
            int auxIndex = (i % CANT_PROCESS);
            if (auxIndex != currentProcess && processes[auxIndex].state == ACTIVE && auxIndex != HALTER_POSITION)
            {
                return auxIndex;
            }
        }
        if (processes[currentProcess].state == ACTIVE)
        {
            processes[currentProcess].currentRunningTime = 0; //Si no hay otro proceso activo, se sigue corriendo el current
        }
        else
        {
            return HALTER_POSITION;
        }
    }
    return currentProcess;
}

int getFreeProcessIndex()
{
    int i = 0;
    for (; i < CANT_PROCESS; i++)
    {
        if (processes[i].state == KILLED)
        {
            return i;
        }
    }
    return -1;
}

//Retorna el pid del proceso creado
int createNewProcess(char *name, void *func(int, char **), int argc, char *argv[], int timeSlot)
{
    int pIndex = getFreeProcessIndex();
    if (pIndex < 0)
    {
        return pIndex; // No hay lugar para crear el nuevo proceso
    }

    processes[pIndex].function = func;
    processes[pIndex].state = ACTIVE;
    processes[pIndex].name = name;
    processes[pIndex].pid = globalPID++;
    processes[pIndex].memory = mallocNUESTRO(STACK_SIZE);
    processes[pIndex].stackPointer = initStack(processes[pIndex].memory + STACK_SIZE,
                                               wrapper, processes[pIndex].function, argc, argv, processes[pIndex].pid);

    processes[pIndex].timeSlot = (timeSlot > MAX_TIME_SLOT) ? MAX_TIME_SLOT : timeSlot;
    processes[pIndex].currentRunningTime = 0;
    if (currentProcess == -1)
    { // Me fijo si es el primer proceso que se esta creando
        print("CAMBIO CURRENT", 0xDE, 0x32);
        currentProcess = pIndex;
    }
    return processes[pIndex].pid;
}

uint64_t *sched(uint64_t *rsp)
{
    if (currentProcess == -1)
    {
        print("KERNEL", 0xFE, 0x32);
        return rsp; // Sigue en el kernel
    }
    else
    {
        // print("currentProces != -1 valor: ", 0xFE, 0x32);
        // char buf[10] = {0};
        // numToStr(buf, currentProcess);
        // print(buf, 0xFE, 0x32);
        if (!firstTime)
        {
            processes[currentProcess].stackPointer = rsp; // Ver si no falla la primera q viene desde kernel
        }
        firstTime = 0;
        int nextProcessIndex = chooseNextProcess();
        currentProcess = nextProcessIndex;
        print("CHOOSE NEXT PROCESS RETORNA valor: ", 0xFE, 0x32);
        char buf[10] = {0};
        numToStr(buf, currentProcess);
        print(buf, 0xFE, 0x32);
        return processes[currentProcess].stackPointer;
    }
}

void wrapper(void *func(int, char **), int argc, char *argv[], int pid)
{
    int retValue;
    retValue = (int)(*func)(argc, argv); // --> return --> wrapper -->  kill (libere todo) --> return a shell
                                         // exit -->kill (libere todo) --> return a padre
    // print("Salgo del proceso",0xFF,0x32);
    exit(retValue);
}

void exit(int status)
{
    //kill();
    print("EXIT", 0x32, 0x32);
    //timerTickInterrupt();
}

int getPid()
{
    return processes[currentProcess].pid;
}
