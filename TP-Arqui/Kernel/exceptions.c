#include <exceptions.h>

void divideByZeroException(uint64_t *stackFrame)
{
    print("Exception thrown: 0\n", 0xFF0000, 0x000000);
    print("Type: Division by zero\n", 0xFF0000, 0x000000);
    snapShotRegister();
    print("\n", 0xFF0000, 0x000000);
    printRegisters(stackFrame);
    stackFrame[15] = (uint64_t)getIntructionPointer();
    //en la posicion 15 esta el RIP cargado por la excepcion
    ////al interrupir, el cpu pushea varias cosas al stack ya que despues tiene que volver a como estaba todo
    //// los registros, los flags, rsp, rip, etc
    //// cuando se llama al "iretq", el mismo usa esta informacion del stack para vovler a la normalidad
    //// https://www.trustwave.com/en-us/resources/blogs/spiderlabs-blog/linux-kernel-rop-ropping-your-way-to-part-2/
    //// en la posicion 15 del stack queda el registro RIP --> lo pisamos por el SampleCodeModule para que haga un restart
    stackFrame[18] = (uint64_t)getStackPointer();
    //// en la posicion 18 esta el RSP --> lo pisamos por el stackFrame original
    print("\n", 0xFF0000, 0x000000);
    clearConsoleIn(5);
}

void invalidOpCodeException(uint64_t *stackFrame)
{
    print("Exception thrown: 6\n", 0xFF0000, 0x000000);
    print("Type: Command not found\n", 0xFF0000, 0x000000);
    snapShotRegister();
    print("\n", 0xFF0000, 0x000000);
    printRegisters(stackFrame);
    stackFrame[15] = (uint64_t)getIntructionPointer();
    stackFrame[18] = (uint64_t)getStackPointer();
    print("\n", 0xFF0000, 0x000000);
    clearConsoleIn(5);
}