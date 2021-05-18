#include <sysHandler.h>

// System Calls --> casos y llamados a cada uno
// https://stackoverflow.com/questions/37581530/passing-argument-from-c-to-assembly ( orden de los argumetos.)
//      rdi             rsi             rdx         rcx             r8                      //r9
void sysHandler(uint64_t *par1, uint64_t par2, uint64_t par3, int sysCallID, uint64_t *stackFrame, uint64_t *par5, uint64_t *par6)
{

    switch (sysCallID)
    {
        // SYSCALL WRITE
    case (0):
    {

        // codigo de escritura
        // par1 --> buffer donde esta lo que quiero escribir
        // par2 --> fileDescrpitor ----> mentira
        // par3 --> long del buffer
        writeScreen(par1, par2, par3);
        return;
    }
    case (1):
    {

        // par1 --> buffer donde escribir lo leido
        // par2 --> long del buffer
        read(par1, par2);
        return;
    }
    case (2):
    {
        // Pide el tiempo
        // par1 --> int * donde se copia lo pedido
        // par2 --> parametro que indica si quiere la hora, minutos o segundos
        getDecimalTime((uint8_t *)par1, par2);
        return;
    }
    case (3):
    {
        // Funcion que retorna en el arreglo de entrada el estado de los registros
        // par1 --> int * de entrada salida
        //par4 --> stackFrame que contiene todos los registros
        getRegisterState(par1, stackFrame);
        return;
    }
    case (4):
    {
        // Funcion que retorna en el arreglo de entrada el estado de los registros
        // par1 --> unsigned char * de entrada salida
        // par2 --> int que indica el principio del lugar de memoria pedido
        getMemoryState((unsigned char *)par1, par2);
        return;
    }
    case (6):
    {
        // par 1 --> coddigo de la figure
        //par2 --> width de la figura
        //par3 --> height de la figura
        // printBase(par6[1],10);
        //par4 --> arreglo con los colores en el primero el color de la fig y en 1 el del back.
        printFigure((unsigned char *)par1, par6[0], par6[1], par2, par3, par5[0], par5[1]);
        break;
    }
    case (7):
    {

        deleteN(par2);
        break;
    }
    case (8):
    {
        clearConsoleIn(par2);
        break;
    }
    case (9):
    {
        setCronometro(par1);
        break;
    }
    case (10):
    {
        int aux = getSecondsCronometro();
        // char buff[20] = {0};
        // numToStr(buff, aux);
        // print(buff, 0xFFFFFF, 0x000000);
        // newLine(8, 16, 0xFFFFFF, 0x000000);
        par1 = &aux;
        break;
    }
    case (11):
    {
        setCursor(par2, par3);
        break;
    }
    case (12):
    {
        disableCursor();
        break;
    }
    case (13):
    {
        // printBase(par1[0],10);
        // print('  ',0x000000,0x000000);
        // printBase(par1[0],10);
        // print('  ',0x000000,0x000000);
        // printBase(par2,16);
        // print('  ',0x000000,0x000000);
        // printBase(par5[0],10);
        // print('  ',0x000000,0x000000);
        // printBase(par5[1],10);
        // print('  ',0x000000,0x000000);
        drawRectangle(par1[0], par1[1], par2, par5[0], par5[1]);
        break;
    }
    case (14):
    {
        startProcess(par1, par6, par2, par5, par3); //REVISAR!!!!!!!!!!!!!!!!!!!!! //(nombre, funcion, argc, argv)
        timerTickInterrupt();
        break;
    }
    case (15):
    {
        *par1 = getPid();
        break;
    }
    case (16):
    {
        _hlt();
        break;
    }
    case (17):
    {
        nice(par3, par2);
        break;
    }
    case (18):
    {
        block(par2);
        break;
    }
    case (19):
    {
        ps(par1);
        break;
    }
    case (20):
    {
        startProcess("test_sync", &test_sync, NULL, NULL, par3);
        break;
    }
    case (21):
    {
        startProcess("test_no_sync", &test_no_sync, NULL, NULL, par3);
        break;
    }
    case (22):
    {
        startProcess("test_processes", &test_processes, NULL, NULL, par3);
    }

    default:
        break;
    }
}

/////////////////////////////////////////////////////////////////
void writeScreen(uint64_t *buffer, uint64_t fontColor, uint64_t background_color)
{
    // print("SYS WRITE",0xf3,0xd2);
    // if (fd == 0)
    // {

    print((char *)buffer, fontColor, background_color);
    // }
}

/////////////////////////////////////////////////////////////////
// SE USA UN PARAMETRO DE SALIDA (BUFFER) PARA ALMACENAR LO LEIDO DESDE TECLADO
void read(uint64_t *buffer, uint64_t lengthBuffer)
{
    if (currentProcessIsForeground())
    {

        char *keyboardBuffer = getKeyboardBuffer();

        for (int i = 0; i < lengthBuffer && keyboardBuffer[i] != 0; i++)
        {
            if (keyboardBuffer[i] == ESPACE)
            {
                // print(keyboardBuffer,0xFF0000,0x000000);
                ((char *)buffer)[i] = ' ';
            }
            else if (L_SHIFT == keyboardBuffer[i] || R_SHIFT_RELEASED == keyboardBuffer[i] || L_SHIFT_RELEASED == keyboardBuffer[i])
            {
                continue;
            }
            else
            {
                ((char *)buffer)[i] = keyboardBuffer[i];
            }
        }

        // LIMPIAMOS EL BUFFER DEL TECLADO YA QUE LO CONSUMIMOS.
        cleanBuffer();
    }
}

/////////////////////////////////////////////////////////////////
void getDecimalTime(uint8_t *buff, uint64_t fd)
{
    switch (fd)
    {
    case 0:
    {
        // printBase(((getHour() & 0xF0) >> 4) * 10 + (getHour() & 0x0F),10);

        // print("HOURS",0xffffff,0x000000);
        *buff = BCDtoInt(getHour());
        //*buff= getHour();
        break;
    }
    case 1:
    {
        //print("MINS",0xffffff,0x000000);
        *buff = BCDtoInt(getMins());
        //*buff= getMins();
        break;
    }
    case 2:
    {
        // print("SECS",0xffffff,0x000000);
        *buff = BCDtoInt(getSeconds());
        //*buff= getSeconds();
        break;
    }
    }
}
/////////////////////////////////////////////////////////////////
void sysGetRegisterState(uint64_t *buff, uint64_t *stackFrame)
{
    getRegisterState(buff, stackFrame);
}

/////////////////////////////////////////////////////////////////
void getMemoryState(unsigned char par1[], uint64_t memoryStart)
{
    unsigned char *startMemory = (unsigned char *)memoryStart;

    for (int i = 0; i < MEMORY_REQUIRED; i++)
    {
        par1[i] = startMemory[i];
    }

    // memcpy(par1,memoryStart);
}