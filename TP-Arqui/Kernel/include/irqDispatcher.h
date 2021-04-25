#ifndef IRQ_DISPATCHER_H
#define IRQ_DISPATCHER_H

#include <stdint.h>
#include <consoleManager.h> // borrar
#include <keyboardDriver.h>
#include <time.h>   // ????????????????
#include <timer.h>
void irqDispatcher(uint64_t irq);
#endif