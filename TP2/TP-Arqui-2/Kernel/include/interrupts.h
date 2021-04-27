#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H
#include <stdint.h>
#include <irqDispatcher.h>
#include <exceptionDispatcher.h>
#include <sysHandler.h>
void _picMasterMask(uint8_t mask);
void _picSlaveMask(uint8_t mask);
void _irq0Handler(); /// rutina de atencion
void _irq1Handler();
void _irq80Handler();
void _excp0Handler();
void _excp6Handler();
void _cli();
void _sti();
void _hlt();

#endif