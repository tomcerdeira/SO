#include <irqDispatcher.h>

uint64_t *irqDispatcher(uint64_t irq, uint64_t *sp)
{
    print("DISPATCHER", 0x32, 0xFF);
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