#include <scheduler.h>


#define MATADO 0
#define ACTIVO   1
#define BLOQUEADO 2
#define CANT_PROCESS 10
#define STACK_SIZE 4096
#define MAX_PROCESSES_PER_PRIO 10
#define CANT_PRIO 3

process processes[CANT_PROCESS] = {{0}};
uint64_t processMemory[CANT_PROCESS][STACK_SIZE] = {{0}};

char *priorityProcessesNames[] = {"shell", "time", "printmem"};
int priorityProcessesValue[] = {1,2,2};

int current_process_index = 0;
int cant_of_active_processes = 0;
int first_time_entering = 1;
int rsp_kernel = 0;

// Creo y lleno el arreglo processes con todos los proceso que puedo tener
// Version 1.0 de manejo de procesos

//TODO crearlos de manera "dinamica" a medida que se necesiten
// hacer que el pid sea incremental
void createprocesses()
{
    int p = 1;
    for (; p <= CANT_PROCESS; p++)
    {
        process proc;
        proc.pid = p;
        proc.memory = processMemory[p - 1];
        proc.state = MATADO;
        proc.priority = 0;
        proc.innerPriority = 20; 
        processes[p - 1] = proc;

    }
}

int getAvailableProcess(process *processes)
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

void startProcess(char *name, void *func(int, char **), int argc, char *argv[])
//se fija entre todos los procesos, agarra uno que esté muerto/disponible, le asigna la tarea, lo activa,
{
    // print("Creo proceso",0x00,0xFF);
    // print(name,0x00,0xFF);
    int availableProcess = getAvailableProcess(processes);

    while ((availableProcess = getAvailableProcess(processes)) < 0)
    {
        // _hlt(); //REVVVVVV!!!!!!!
        availableProcess = getAvailableProcess(processes);
    }

    processes[availableProcess].function = func;
    processes[availableProcess].state = ACTIVO;
    processes[availableProcess].name = name;
    processes[availableProcess].memory = processMemory[availableProcess]; // Habria que liberarla una vez matado el proceso
    processes[availableProcess].stackPointer = initStack(processes[availableProcess].memory + STACK_SIZE,
                                                         wrapper, processes[availableProcess].function, argc, argv, processes[availableProcess].pid);
    setProcessPriority(&processes[availableProcess]);
    processes[availableProcess].innerPriority = 0;
    cant_of_active_processes++;
    
}

void setProcessPriority(process * p){
    int i=0;
    for (; i < 3; i++)
    {
        if(strcompare(p->name,priorityProcessesNames[i])){
            p->priority = priorityProcessesValue[i];
        }
    }
    p->priority = CANT_PRIO - 1; //Si no está le asigna la peor prioridad
}

    void
    wrapper(void *func(int, char **), int argc, char *argv[], int pid)
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
        if (first_time_entering){
            rsp_kernel = rsp;
        }
        return rsp_kernel;
    }
    else
    {
        if (!first_time_entering) // Esto es para que un proceso se actualice el SP.
        {
            processes[current_process_index].stackPointer = rsp;
        }
        int prio = 0;
        int found = 0;
        int minInnerPriorityProcess = 0;
        for (; prio < CANT_PRIO; prio++)
        {
            int i = 0;
            for (; i < CANT_PROCESS; i++) //TODO esta implementación no usa prioridades, habría que chequear el más prioritario
            {
                if (processes[i].state == ACTIVO && processes[i].priority == prio)
                {
                    if (processes[i].innerPriority < processes[minInnerPriorityProcess].innerPriority)
                    {
                        minInnerPriorityProcess = i;
                        found = 1;
                    }
                }
            }
             if(found){
                first_time_entering = 0;
                current_process_index = minInnerPriorityProcess;
                processes[minInnerPriorityProcess].innerPriority += 1;
                return processes[minInnerPriorityProcess].stackPointer; //TODO devolver el más prioritario
            }
           
        }
    }
    return (uint64_t *)-1;
    // Tira warning pero nunca llega aca (al menos no deberia)
}

void kill(int pid)
{
    int pos = 0;
    for (; pos < cant_of_active_processes; pos++)
    {
        if (processes[pos].pid == pid)
        {
            processes[pos].state = MATADO;
            cant_of_active_processes--;
        }
    }
}

void kill_current(){
    processes[current_process_index].state = MATADO;
    cant_of_active_processes--;
}

void exit(int status)
{

    kill_current();
    timerTickInterrupt();
}
 