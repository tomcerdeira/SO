#include <irqDispatcher.h>

void irqDispatcher(uint64_t irq, uint64_t *sp)
{
    //print("LLEGO", 0x32, 0xFF);
    switch (irq)
    {
    case 0:
        timerHandler();
        return activeProcess(sp);
        break;
    case 1:
        readKeyboardBuffer();
        break;
    }
}