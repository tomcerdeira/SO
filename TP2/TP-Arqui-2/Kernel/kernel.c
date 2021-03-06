#include <stdint.h>
// #include <string.h>
#include <lib.h>
#include <libC.h>
#include <sysHandler.h>
#include <moduleLoader.h>
#include <consoleManager.h>
// #include <naiveConsole.h>
#include <idt.h>
#include <pipe.h>

// /////// SACAR
// #include <scheduler2.h>

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

/////////// SACAR
void funcion();
void funcion1();

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
	//_cli();
	initScreen();
	//////

	//initScheduler();
	initializeMemory();
	initPipes();
	createprocesses();

	// print("LLEGO 2", 0x32, 0xFF);
	//////
	configureIDT();
	setReturns(sampleCodeModuleAddress, getSP()); //Seteado de IP y SP

	//_cli();
	// print("AAAAAAAAAAAAAAAAAAAAAAAAA", 0xFF, 0x32);
	//startProcess("prueba", &funcion, NULL, NULL);
	// print("EEEEEEEEEEEEEEEEEEEEEEEEEE", 0xFF, 0x32);
	//_sti();
	// startProcess("prueba", &funcion1, NULL, NULL);
	// startProcess("prueba", &funcion, NULL, NULL);

	// while (1)
	// {
	// 	/* code */
	// }

	//print("LLEGO 3", 0x32, 0xFF);

	//_sti();

	((EntryPoint)sampleCodeModuleAddress)();
	// print("LLEGO000000000 2", 0xFF, 0x32);
	// while (1)
	// {
	// 	print("WHILE", 0x32, 0xFF);
	// }

	//////////////////////

	return 0;
}

void funcion()
{
	int i = 0;
	while (i < 10)
	{
		print("FUNCION", 0x32, 0xFF);
		i++;
	}
}
void funcion1()
{
	int i = 0;
	while (i < 10)
	{
		print("FUNCION 1 ", 0x32, 0xFF);
		i++;
	}
}