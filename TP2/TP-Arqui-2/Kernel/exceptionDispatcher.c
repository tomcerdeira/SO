// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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