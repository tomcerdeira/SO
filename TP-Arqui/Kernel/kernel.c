#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <libC.h>
#include <sysHandler.h>
#include <moduleLoader.h>
#include <consoleManager.h>
// #include <naiveConsole.h>
#include <idt.h>

////////////////////////////

//#include "text_driver.h"
//#include "./include/video_driver.h"
#include <videoDriver.h>

///////////////////////////

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
	configureIDT();
	setReturns(sampleCodeModuleAddress, getSP()); //Seteado de IP y SP
	// print("por dividir",0x555555,0x118822);
	//int i = 1 / 0;
	// print("listo dividir",0x22,0x22);

	((EntryPoint)sampleCodeModuleAddress)();

	//////////////////////

	return 0;
}
