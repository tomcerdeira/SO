#include <irqDispatcher.h>

void irqDispatcher(uint64_t irq)
{
    //print("LLEGO", 0x32, 0xFF);
    switch (irq)
    {
    case 0:
        timerHandler();
        break;
    case 1:
        readKeyboardBuffer();
        break;
    }
}