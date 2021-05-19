#include <standardLib.h>

int fontColor[1] = {0};
// int backgroundColor[1] = {0};

void setFontColor(int color)
{
    *fontColor = color;
}

// void setBackGroundColor(int color)
// {
//     *backgroundColor = color;
// }

void putChar(char str)
{
    // char buff[2] = {0};
    // buff[0] = str;
    printf("%c", str);
}

char getChar()
{

    char res = 0;
    while (res == 0)
    // -- > opcion comentada en syshandler va sin el while
    {
        readKeyBuff(&res, 1, 0);
        //halt();
    }

    return res;
}

//////////////////////////////////////////////
// Ayuda sacada de: https://iq.opengenus.org/how-printf-and-scanf-function-works-in-c-internally/

void printf(const char *format, ...) //... ya que los parametros son variables
{
    char toRet[SCREEN_WIDTH];

    va_list valist; //lista de parametros
    va_start(valist, format);

    int index = 0;

    for (int i = 0; format[i] != 0; i++)
    {
        if (format[i] == '%')
        {
            i++;
            int largoDelInt = 10;
            char aux[largoDelInt]; //como maximo puede tener 10 digitos el integer (arbitratio)

            int counter; //me transforma el int a un string

            char *string2;

            int j = 0;
            switch (format[i])
            {
            case 'c':
                toRet[index++] = (char)(va_arg(valist, int));
                break;

            case 'd':
                counter = numToStr(aux, va_arg(valist, int));
                if (counter > largoDelInt)
                {
                    /* should throw exception*/ //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                }
                for (int j = 0; j < counter; j++)
                {
                    toRet[index++] = aux[j];
                }
                break;

            case 's':
                string2 = (char *)va_arg(valist, char *);

                while (string2[j] != 0) //busco que termine el string a copiar
                {

                    toRet[index++] = string2[j++];
                }

                break;

            default:
                /* should throw exception*/ //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                //changeLetterColor(0xFF0000);
                printf("Expresion %s is unsupported \n", format[i]);
                //changeLetterColor(DEFAULT_LETTER_COLOR);
                //expression not suported
                break;
            }
        }
        else //just copy the string
        {
            toRet[index++] = format[i];
        }
    }
    va_end(valist);
    toRet[index] = 0;
    // PARECE QUE VA A HABER QUE BORRAR EL 1000!!                           //fin del string
    write(toRet, *fontColor, 0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int scanf(const char *format, ...)
{
    char usrInput[SCREEN_WIDTH];

    int index = 0;

    char in = getChar();

    while (in != '\n')
    {

        if (in == '\b') //Si el usr borro
        {
            if (index != 0)
            {

                index--;
                usrInput[index] = 0;
                deleteN(1); // TOMAR DECICISION REPESCTO AL 1 SI CORRESPONDE QUE PUEDA HACER MAS DE 1 O NO !!!!!!!!!!!!!
            }
        }
        else //Sino, lo carga al arreglo
        {
            usrInput[index++] = in;
            putChar(in);
        }
        //
        // printf("%s|| %d",usrInput,index);
        in = getChar(); //Y espera al proximo caracter
    }
    putChar('\n');

    usrInput[index] = 0; //Pongo el 0 final del string
    index = 0;           //Reseteo el indice

    va_list valist;
    va_start(valist, format);
    int number_of_vars = 0;

    for (int i = 0; format[i] != 0; i++)
    {

        if (format[i] == '%') //es que viene un fomrato
        {
            i++;
            number_of_vars++;

            int largoDelInt = 10; //chequear
            char aux[largoDelInt];
            int aux_index = 0;

            char *output;
            int output_index = 0;

            switch (format[i])
            {
            case 'c':
            { //caso char
                *(char *)va_arg(valist, char *) = usrInput[index++];
                break;
            }

            case 'd':
            { //caso integer
                while (usrInput[index] == ' ')
                {
                    index++;
                }

                while (usrInput[index] != 0 && usrInput[index] != ' ')
                {

                    aux[aux_index++] = usrInput[index++]; //Me armo un arreglo de chars con el input
                }
                aux[aux_index++] = 0;

                *(int *)va_arg(valist, int *) = strToInt(aux);
                //Como "d" es un integer, paso el str a int.

                break;
            }
            case 's':
            { //caso string
                output = (char *)va_arg(valist, char *);
                while (usrInput[index] == ' ')
                {
                    index++;
                }

                while (usrInput[index] != ' ' && usrInput[index] != 0)
                {
                    output[output_index++] = usrInput[index++];
                }
                output[output_index] = 0;

                break;
            }

            default:
                /* should throw exception*/
                //changeLetterColor(0xFF0000);
                printf("Expresion %s is unsupported \n", format[i]);
                //changeLetterColor(DEFAULT_LETTER_COLOR);
                //expression not suported
                va_end(valist); // a chequear
                return -1;
            }
        }
    }
    va_end(valist);
    return number_of_vars;
}

//////////////////////////////////////////////////////////////////////////

int strToInt(char *charValue)
{
    int toReturn = 0;
    for (int i = 0; charValue[i] != '\0'; ++i)
        toReturn = toReturn * 10 + charValue[i] - '0';

    return toReturn;
}

//////////////////////////////////////////////////////////////////////////

int numToStr(char *str, int num)
{
    int dim = 0;
    int negativo = 0;
    if (num == 0)
    {
        str[dim++] = num + '0';
    }
    if (num < 0)
    {
        negativo = 1;
        num *= -1;
    }

    while (num != 0)
    {
        int res = num % 10;
        str[dim++] = res + '0';
        num /= 10;
    }
    if (negativo)
    {
        str[dim++] = '-';
    }
    int i = 0;
    int j = dim - 1;
    while (i < j)
    {
        char aux = str[i];
        str[i] = str[j];
        str[j] = aux;
        j--;
        i++;
    }

    str[dim] = 0;
    return dim;
}

////////////////////////////////////////////////////////////////////

int strcmp(char *s1, char *s2)
{
    int cmp = 1;
    int i;
    for (i = 0; s1[i] != 0 && s2[i] != 0 && cmp; i++)
    {
        if (s1[i] != s2[i])
        {
            cmp = 0;
        }
    }

    if ((s1[i] == 0 && s2[i] != 0) || (s1[i] != 0 && s2[i] == 0))
    {
        cmp = 0;
    }
    return cmp;
}

///////////////////////////////////////////////////////////////////////

// provisto por la catedra
uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base)
{
    char *p = buffer;
    char *p1, *p2;
    uint32_t digits = 0;

    //Calculate characters for each digit
    do
    {
        uint32_t remainder = value % base;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
        digits++;
    } while (value /= base);

    // Terminate string in buffer.
    *p = 0;

    //Reverse string in buffer.
    p1 = buffer;
    p2 = p - 1;
    while (p1 < p2)
    {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }

    return digits;
}

//////////....................////////////////////
void printmem(int memoryPos)
{

    unsigned char memory[33] = {0};

    getMemoryState(memory, memoryPos);
    if (memoryPos >= 0)
    {
        printf("Direccion inicial : %d", memoryPos);

        printf("\n");
        printf("siguientes 32 bytes en direcciones relativas");
        char buff[5] = {0};
        for (int i = 0; i < 32; i++)
        {
            int dim = uintToBase(memory[i], buff, 16);
            parseHexa(buff, dim);
            if (i % 8 == 0)
            {
                putChar('\n');
            }
            if (i < 9)
            {
                printf("0");
            }
            printf("%d ", i + 1);
            printf(": %s   ", buff);
        }
        printf("\n");
    }
    else
    {
        setFontColor(0xFF0000);
        printf("Direccion de memoria invalida.\n");
        setFontColor(DEFAULT_FONT_COLOR);
    }
    return;
}

////////////.........////////////////
void parseHexa(char *buff, int dim)
{
    char auxStr[5] = "0x00";
    for (int j = 3; j >= 0 && dim != 0; j--)
    {
        auxStr[j] = buff[dim - 1];
        dim--;
    }
    for (int i = 0; i < 4; i++)
    {
        buff[i] = auxStr[i];
    }
}

void error(char *str1, char *str2)
{
    setFontColor(0xFF0000);
    printf(str1, str2);
    setFontColor(DEFAULT_FONT_COLOR);
}

void printTime()
{
    uint8_t hour;
    uint8_t minutes;
    uint8_t seconds;
    getTime(&hour, 0);

    getTime(&minutes, 1);
    getTime(&seconds, 2);
    if (hour < 10)
    {
        printf(" 0%d hs :", hour);
    }
    else
    {
        printf(" %d hs :", hour);
    }
    if (minutes < 10)
    {
        printf(" 0%d mins :", minutes);
    }
    else
    {
        printf(" %d mins :", minutes);
    }
    if (seconds < 10)
    {
        printf(" 0%d secs\n", seconds);
    }
    else
    {
        printf(" %d secs\n", seconds);
    }
}

void printBase(uint64_t value, uint_least32_t base)
{
    char buffer[10] = {0};
    uintToBase(value, buffer, base);
    printf(buffer);
}

int getDistance(int to, int from)
{
    if (to > from)
    {
        return to - from;
    }
    return from - to;
}

//https://www.techiedelight.com/implement-strcpy-function-c/
char *strcpy(char *destination, const char *source)
{
    char *ptr = destination;
    while (*source != 0)
    {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = 0;
    return ptr;
}

long getMillis()
{
    uint8_t hour;
    uint8_t minutes;
    uint8_t seconds;
    getTime(&hour, 0);

    getTime(&minutes, 1);
    getTime(&seconds, 2);

    long millis = 3600000 * hour + 60000 * minutes + seconds * 1000;
}

//////////////////////////////// REV (si corresponde que este definida aca) y su funcionamiento
int createProcess(char *name, void *func, int argc, char *argv[], int isForeground)
{
    return createP(name, func, argc, argv);
    /////////////// rdi, rsi, rdx, rcx
}

int getPid()
{
    int pid = 0;
    getProcessPid(&pid);
    return pid;
}
