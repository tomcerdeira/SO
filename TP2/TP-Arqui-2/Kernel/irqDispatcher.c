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
}