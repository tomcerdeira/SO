#ifndef IRQ_DISPATCHER_H
#define IRQ_DISPATCHER_H

#include <stdint.h>
#include <consoleManager.h> // borrar
#include <keyboardDriver.h>
#include <time.h> // ????????????????
#include <timer.h>

#include <scheduler2.h>

uint64_t *irqDispatcher(uint64_t irq, uint64_t *sp);
#endif