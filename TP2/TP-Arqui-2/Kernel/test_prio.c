// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include <scheduler.h>
#include <libC.h>

#define MINOR_WAIT 100000000 // TODO: To prevent a process from flooding the screen
#define WAIT 10000000        // TODO: Long enough to see theese processes beeing run at least twice

uint64_t my_getpid2()
{
  return getPid();
}
void bussy_wait2(uint64_t n)
{
  uint64_t i;
  for (i = 0; i < n; i++)
    ;
}
void endless_loop2()
{
  uint64_t pid = my_getpid2();

  while (1)
  {
    printBase(pid, 10);
    // print("\n",0xFFFFFF,0x000000);
    bussy_wait2(MINOR_WAIT);
  }
}
uint64_t my_create_process2(char *name)
{

  return startProcess(name, (void *)&endless_loop2, 0, 0, 1);
  ;
}

uint64_t my_nice2(uint64_t pid, uint64_t newPrio)
{
  nice(pid, newPrio);
  return 1;
}

uint64_t my_kill2(uint64_t pid)
{
  kill(pid);
  return 1;
}

uint64_t my_block2(uint64_t pid)
{
  block(pid);
  return 1;
}

uint64_t my_unblock2(uint64_t pid)
{
  block(pid);
  return 1;
}

#define TOTAL_PROCESSES 3

void test_prio()
{
  uint64_t pids[TOTAL_PROCESSES];
  uint64_t i;

  for (i = 0; i < TOTAL_PROCESSES; i++)
    pids[i] = my_create_process2("endless_loop");

  bussy_wait2(WAIT);
  print("\nCHANGING PRIORITIES...\n", 0xFFFFFF, 0x000000);

  for (i = 0; i < TOTAL_PROCESSES; i++)
  {
    switch (i % 3)
    {
    case 0:
      my_nice2(pids[i], 0); //lowest priority
      break;
    case 1:
      my_nice2(pids[i], 1); //medium priority
      break;
    case 2:
      my_nice2(pids[i], 2); //highest priority
      break;
    }
  }

  bussy_wait2(WAIT);
  print("\nBLOCKING...\n", 0xFFFFFF, 0x000000);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    my_block2(pids[i]);

  print("CHANGING PRIORITIES WHILE BLOCKED...\n", 0xFFFFFF, 0x000000);
  for (i = 0; i < TOTAL_PROCESSES; i++)
  {
    switch (i % 3)
    {
    case 0:
      my_nice2(pids[i], 1); //medium priority
      break;
    case 1:
      my_nice2(pids[i], 1); //medium priority
      break;
    case 2:
      my_nice2(pids[i], 1); //medium priority
      break;
    }
  }

  print("UNBLOCKING...\n", 0xFFFFFF, 0x000000);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    my_unblock2(pids[i]);

  bussy_wait2(WAIT);
  print("\nKILLING...\n", 0xFFFFFF, 0x000000);

  for (i = 0; i < TOTAL_PROCESSES; i++)
    my_kill2(pids[i]);
}
