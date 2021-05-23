#ifndef EXCEPTION_DISPATCHER_H
#define EXCEPTION_DISPATCHER_H

#include <stdint.h>
#include <consoleManager.h>
#include <exceptions.h>

void exceptionDispatcher(uint64_t excp, uint64_t *stackFrame);

#endif