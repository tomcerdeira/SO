#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>
#include <consoleManager.h>
#include <libC.h>

void divideByZeroException(uint64_t *stackFrame);

void invalidOpCodeException(uint64_t *stackFrame);

#endif