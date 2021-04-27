#ifndef MODULELOADER_H
#define MODULELOADER_H

#include <libC.h>

void loadModules(void * payloadStart, void ** moduleTargetAddress);

#endif