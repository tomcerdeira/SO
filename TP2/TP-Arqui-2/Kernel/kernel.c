// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include <lib.h>
#include <libC.h>
#include <sysHandler.h>
#include <moduleLoader.h>
#include <consoleManager.h>
#include <idt.h>
#include <pipe.h>
#include <buddy_system2.h>
//#include <memory_manager.h>
#include <videoDriver.h>


extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

extern uint64_t *getSP();



static const uint64_t PageSize = 0x1000;

static void *const sampleCodeModuleAddress = (void *)0x400000;
static void *const sampleDataModuleAddress = (void *)0x500000;
static void *const sampleMememoryModuleAddress = (void *)0x600000;

typedef int (*EntryPoint)();

void clearBSS(void *bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void *getStackBase()
{
	return (void *)((uint64_t)&endOfKernel + PageSize * 8 //The size of the stack itself, 32KiB
					- sizeof(uint64_t)					  //Begin at the top of the stack
	);
}

void *initializeKernelBinary()
{
	void *moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress};

	loadModules(&endOfKernelBinary, moduleAddresses);

	clearBSS(&bss, &endOfKernel - &bss);

	return getStackBase();
}

int main()
{
	
	initScreen();

	initializeMemory();
	initPipes();
	createprocesses();


	configureIDT();
	setReturns(sampleCodeModuleAddress, getSP()); //Seteado de IP y SP


	((EntryPoint)sampleCodeModuleAddress)();


	return 0;
}

