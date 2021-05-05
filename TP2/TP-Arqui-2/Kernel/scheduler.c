#include <scheduler.h>

#define MATADO 0
#define ACTIVO 1
#define BLOQUEADO 2
#define CANT_PROCESS 10
#define STACK_SIZE 4096
#define MAX_PROCESSES_PER_PRIO 10
#define CANT_PRIO 3
#define DEATH_INNER_P -1

//process processes[CANT_PROCESS] = {{0}};
process processes[CANT_PRIO][CANT_PROCESS] = {{0}};

// uint64_t processMemory[CANT_PRIO][CANT_PROCESS][STACK_SIZE] = {{0}};

char *priorityProcessesNames[] = {"shell", "time", "printmem", "loop"};
int priorityProcessesValue[] = {2, 1, 2, 1};

int current_process_index = 0;
int current_prio_index = 0;
int cant_of_active_processes = 0;
int first_time_entering = 1;
int rsp_kernel = 0;
int last_pid = 5;

// Creo y lleno el arreglo processes con todos los proceso que puedo tener
// Version 1.0 de manejo de procesos

//TODO crearlos de manera "dinamica" a medida que se necesiten
// hacer que el pid sea incremental
void createprocesses()
{
    int prio = 0;
    for (; prio < CANT_PRIO; prio++)
    {
        int p = 0;
        for (; p < CANT_PROCESS; p++)
        {
            process proc;
            proc.pid = 0;
            //proc.memory = processMemory[prio][p];
            proc.memory = 0;
            proc.state = MATADO;
            proc.priority = prio;
            proc.innerPriority = DEATH_INNER_P;
            processes[prio][p] = proc;
        }
    }
}

int getAvailableProcessInPrio(int prio)
{
    int i = 0;
    for (; i < CANT_PROCESS; i++)
    {
        if (processes[prio][i].state == MATADO)
        {
            return i;
        }
    }
    return -1;
}

int getPriority(char *name)
{
    int i = 0;
    for (; i < 3; i++) //TODO no hardcodear el 3
    {
        if (strcompare(name, priorityProcessesNames[i]))
        {
            return priorityProcessesValue[i];
        }
    }
    return CANT_PRIO - 1; //si no está definido, le da la menor prioridad
}

int startProcess(char *name, void *func(int, char **), int argc, char *argv[])
//se fija entre todos los procesos, agarra uno que esté muerto/disponible, le asigna la tarea, lo activa,
{
    int prio_name = getPriority(name);                           //2
    int availableProcess = getAvailableProcessInPrio(prio_name); //0

    if (availableProcess < 0)
    {
        // ERROR --> No hay un lugar para el proceso nuevo
        return;
    }

    processes[prio_name][availableProcess].function = func;
    processes[prio_name][availableProcess].state = ACTIVO;
    processes[prio_name][availableProcess].name = name;
    processes[prio_name][availableProcess].pid = last_pid++;
    //processes[prio_name][availableProcess].memory = processMemory[prio_name][availableProcess]; // Habria que liberarla una vez matado el proceso
    processes[prio_name][availableProcess].memory = mallocNUESTRO(STACK_SIZE);

    processes[prio_name][availableProcess].stackPointer = initStack(processes[prio_name][availableProcess].memory + STACK_SIZE,
                                                                    wrapper, processes[prio_name][availableProcess].function, argc, argv, processes[prio_name][availableProcess].pid);
    // setProcessPriority(&processes[availableProcess]); //?/
    processes[prio_name][availableProcess].innerPriority = 0;
    cant_of_active_processes++;
    // char buf[12] = {0};
    // numToStr(buf, processes[prio_name][availableProcess].pid);
    // print(buf, 0xFF, 0x32);
    return processes[prio_name][availableProcess].pid;
}

void wrapper(void *func(int, char **), int argc, char *argv[], int pid)
{
    int retValue;
    retValue = (int)(*func)(argc, argv); // --> return --> wrapper -->  kill (libere todo) --> return a shell
                                         // exit -->kill (libere todo) --> return a padre
    // print("Salgo del proceso",0xFF,0x32);
    exit(retValue);
}

uint64_t *activeProcess(uint64_t *rsp)
{
    if (cant_of_active_processes == 0)
    {
        if (first_time_entering)
        {
            rsp_kernel = rsp;
        }
        return rsp_kernel;
    }
    else
    {
        if (!first_time_entering) // Esto es para que un proceso se actualice el SP.
        {
            processes[current_prio_index][current_process_index].stackPointer = rsp;
        }
        int prio = 0;
        int found = 0;
        int minInnerPriorityIndex = 0;
        for (; prio < CANT_PRIO; prio++)
        {
            int i = 0;
            for (; i < CANT_PROCESS; i++)
            {
                if (processes[prio][i].state == ACTIVO)
                {
                    if (processes[prio][i].innerPriority <= processes[prio][minInnerPriorityIndex].innerPriority && processes[prio][minInnerPriorityIndex].innerPriority != DEATH_INNER_P)
                    {
                        // print(processes[prio][i].name, 0x32, 0xFF);
                        minInnerPriorityIndex = i;
                        found = 1;
                    }
                }
            }
            if (found)
            {
                //  print("BBBBBBBBBBBBBBBBBBBBBBBBBBBB", 0xFF, 0x32);
                first_time_entering = 0;
                current_process_index = minInnerPriorityIndex;
                current_prio_index = prio;
                processes[prio][minInnerPriorityIndex].innerPriority++;
                return processes[prio][minInnerPriorityIndex].stackPointer; //TODO devolver el más prioritario
            }
            else
            {
                minInnerPriorityIndex = 0;
            }
        }
    }
    print("_______ACA NO DEBERIA ESTAR________", 0x32, 0xFF);
    return (uint64_t *)-1;
    // Tira warning pero nunca llega aca (al menos no deberia)
}

void kill(int pid)
{
    int prio = 0;
    for (; prio < CANT_PRIO; prio++)
    {
        int pos = 0;
        for (; pos < CANT_PROCESS; pos++)
        {
            if (processes[prio][pos].pid == pid)
            {
                processes[prio][pos].state = MATADO;
                processes[prio][pos].innerPriority = DEATH_INNER_P;
                freeMemory(processes[prio][pos].memory);
                cant_of_active_processes--;
            }
        }
    }
}

void exit(int status)
{
    kill(processes[current_prio_index][current_process_index].pid);
    timerTickInterrupt();
}

int getPid()
{
    return processes[current_prio_index][current_process_index].pid;
}
