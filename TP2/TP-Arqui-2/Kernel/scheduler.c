#include "scheduler.h"

#define MATADO 0
#define ACTIVO 1
#define BLOQUEADO 2

#define CANT_PROCESS 10
#define STACK_SIZE 4096

process processes[CANT_PROCESS] = {{0}};
uint64_t processMemory[CANT_PROCESS][STACK_SIZE] = {{0}};

int current_process_index = 0;
int cant_of_active_processes = 0;
int first_time_entering = 1;

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
    cant_of_active_processes++;
    // print("EMPECE UN PROCESO", 0x32, 0xFF);
    // print(name, 0x32, 0xFF);
}

void wrapper(void *func(int, char **), int argc, char *argv[], int pid)
{
    int retValue;
    retValue = (int)(*func)(argc, argv); // --> return --> wrapper -->  kill (libere todo) --> return a shell
                                         // exit -->kill (libere todo) --> return a padre
    exit(retValue);
}

uint64_t *activeProcess(uint64_t *rsp)
{
    if (cant_of_active_processes == 0)
    {

        return rsp;
    }
    // RSP_K -->  1   RSP_F --> 22
    else
    {
        if (!first_time_entering)
        {
            processes[current_process_index].stackPointer = rsp;
        }
        int i = 0;
        for (; i < CANT_PROCESS; i++) //TODO esta implementación no usa prioridades, habría que chequear el más prioritario
        {
            if (processes[i].state == ACTIVO)
            {
                first_time_entering = 0;
                // print("CAMBIO PROCESO", 0x44, 0xFE);
                // print(processes[i].name, 0x44, 0xFE);
                current_process_index = i;
                return processes[i].stackPointer; //TODO devolver el más prioritario
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

void exit(int status)
{
    kill(processes[current_process_index].pid);
    timerTickInterrupt();
}
