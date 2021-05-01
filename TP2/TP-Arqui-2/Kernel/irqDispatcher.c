#include <irqDispatcher.h>

uint64_t *irqDispatcher(uint64_t irq, uint64_t *sp)
{
    //print("DISPATCHER", 0x32, 0xFF);
    switch (irq)
    {
    case 0:
        timerHandler();
        //return sp;
        //return activeProcess(sp);
       return changeProcess(sp);
        break;
    case 1:
        readKeyboardBuffer();
        return sp;
        break;
    }
}