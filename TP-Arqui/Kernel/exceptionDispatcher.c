#include <exceptionDispatcher.h>

void exceptionDispatcher(uint64_t excp, uint64_t *stackFrame)
{
    switch (excp)
    {
    case 0:
        divideByZeroException(stackFrame);
        break;
    case 6:
        invalidOpCodeException(stackFrame);
        break;
    }
}