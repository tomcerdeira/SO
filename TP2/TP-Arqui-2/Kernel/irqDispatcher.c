// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <irqDispatcher.h>

uint64_t *irqDispatcher(uint64_t irq, uint64_t *sp)
{

    switch (irq)
    {
    case 0:
        timerHandler();
        return sched(sp);
        break;
    case 1:
        readKeyboardBuffer();
        return sp;
        break;
    }
    return (uint64_t *) 1;
}