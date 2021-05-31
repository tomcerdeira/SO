// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <sysHandler.h>
#include <test_mm.h>
#include <test_prio.h>

#define FD_STDIN 1
#define FD_STOUT 2

// System Calls --> casos y llamados a cada uno
// https://stackoverflow.com/questions/37581530/passing-argument-from-c-to-assembly ( orden de los argumetos.)
//      rdi             rsi             rdx         rcx             r8                      //r9
void sysHandler(uint64_t *par1, uint64_t par2, uint64_t par3, int sysCallID, uint64_t *stackFrame, uint64_t *par5, uint64_t *par6)
{

    switch (sysCallID)
    {

    case (0):
    {
        // SYSCALL WRITE
        // codigo de escritura
        // par1 --> buffer donde esta lo que quiero escribir
        // par2 --> FONTCOLOR ----> mentira
        // par3 --> FD
        write(par1, par2, par3);
        return;
    }
    case (1):
    {

        // par1 --> buffer donde escribir lo leido
        // par2 --> long del buffer
        // par3 --> fd
        read(par1, par2, par3); //
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
        setCronometro(*par1);
        break;
    }
    case (10):
    {
        int aux = getSecondsCronometro();
        par1 = (uint64_t *)&aux;
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
        drawRectangle(par1[0], par1[1], par2, par5[0], par5[1]);
        break;
    }
    case (14):
    {
        startProcess((char *)par1, (void *)par6, (int)par2, (char **)par5, (int)par3); //(nombre, funcion, argc, argv,isForeground)
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
        ps((char *)par1);
        break;
    }
    case (20):
    {
        startProcess("test_sync", (void *)&test_sync, 0, NULL, 0);
        break;
    }
    case (21):
    {
        startProcess("test_no_sync", (void *)&test_no_sync, 0, NULL, 0);
        break;
    }
    case (22):
    {
        startProcess("test_processes", (void *)&test_processes, 0, NULL, 0);
        break;
    }
    case (23):
    {
        kill(par2);
        break;
    }
    case (24):
    {
        createNewPipe((int *)par1);
        break;
    }
    case (25):
    {
        setFDNextNewProcess((int)par3, (int)par2);
        break;
    }
    case (26):
    {
        changeOutputFd(par3, par2);
        break;
    }
    case (27):
    {
        getPidByName((char *)par1, (int *)par5);
        break;
    }
    case (28):
    {
        semOpen((char *)par1, (int)par2, (int *)par5);
        break;
    }
    case (29):
    {
        semClose((char *)par1);
        break;
    }
    case (30):
    {
        mySemPost((char *)par1);
        break;
    }
    case (31):
    {
        mySemWait((char *)par1);
        break;
    }
    case (32):
    {
        pipesInfo((char *)par1);
        break;
    }
    case (33):
    {
        *par1 = mallocNUESTRO((int)par2);
        break;
    }
    case (34):
    {
        yield();
        break;
    }
    case (35):
    {
        getSemStatus((char *)par1, (int *)par5);
        break;
    }
    case (36):
    {
        freeMemory((char *)par1);
        break;
    }
    case (37):
    {
        semsInfo((char *)par1);
        break;
    }
    case (38):
    {
        getMemoryInfo((char *)par1);
        break;
    }
    case (39):
    {
        startProcess("test_mm", (void *)&test_mm, 0, NULL, 0);
        break;
    }
    case (40):
    {
        startProcess("test_prio", (void *)&test_prio, 0, NULL, 0);
        break;
    }
    case (41):
    {
        *par1 = shm_open(par2, par3); //par2 = index, par3 = size
        break;
    }
    case (42):
    {
        shm_close(par2); //par2 = index
        break;
    }
    default:
        break;
    }
}

/////////////////////////////////////////////////////////////////
void write(uint64_t *buffer, uint64_t fontColor, uint64_t fd)
{
    int currentPID;
    int fdCurrentOutput;

    switch (fd)
    {
    case FD_STOUT:
        print(" syshandler.c ACA", fontColor, 0x000000);
        print((char *)buffer, fontColor, 0x000000);
        break;
    case 0: // Si quiere escribir en su FD que podria ser la pantalla u otro FD.
        currentPID = getPid();
        fdCurrentOutput = getFdOutput(currentPID);
        if (fdCurrentOutput == FD_STOUT)
        {
            print((char *)buffer, fontColor, 0x000000);
        }
        else
        {
            writePipe(fdCurrentOutput, (char *)buffer);
        }
        break;
    default:
        writePipe(fd, (char *)buffer);
        break;
    }
}

/////////////////////////////////////////////////////////////////
// SE USA UN PARAMETRO DE SALIDA (BUFFER) PARA ALMACENAR LO LEIDO DESDE TECLADO
void read(uint64_t *buffer, uint64_t lengthBuffer, uint64_t fd)
{

    char *keyboardBuffer = {0};
    int sizeRead;
    int currentPID;
    int fdCurrentInput;

    switch (fd)
    {
    case FD_STDIN:

        for (int i = 0; i < lengthBuffer && keyboardBuffer[i] != 0; i++)
        {
            if (keyboardBuffer[i] == ESPACE)
            {
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
        break;

    case 0:
        currentPID = getPid();
        fdCurrentInput = getFdInput(currentPID);
        if (fdCurrentInput == FD_STDIN)
        {

            char *keyboardBuffer;
            while ((keyboardBuffer = getKeyboardBuffer())[0] == 0)
            {
                blockReader(getPid());
            }

            for (int i = 0; i < lengthBuffer && keyboardBuffer[i] != 0; i++)
            {
                if (keyboardBuffer[i] == ESPACE)
                {
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
        else
        {
            readPipe((char *)buffer, 1, fdCurrentInput);
        }
        break;

    default:
        sizeRead = readPipe((char *)buffer, lengthBuffer, fd);
        if (sizeRead < 0)
        {
            print("(sysHandler.c) ERROR: readPipe", 0x000000, 0xFFFFFF);
        }
    }
}

/////////////////////////////////////////////////////////////////
void getDecimalTime(uint8_t *buff, uint64_t fd)
{
    switch (fd)
    {
    case 0:
    {
        *buff = BCDtoInt(getHour());

        break;
    }
    case 1:
    {

        *buff = BCDtoInt(getMins());

        break;
    }
    case 2:
    {

        *buff = BCDtoInt(getSeconds());

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
}