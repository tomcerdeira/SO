#include <keyboardDriver.h>


// https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html pagina de los scancodes
static const char keyCodes[KEYS][2] = {
    {0, 0}, {ESC, ESC}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'}, {'=', '+'}, {'\b', '\b'}, {'\t', '\t'}, {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'}, {'\n', '\n'}, {CTRL, CTRL}, {'a', 'A'}, {'s', 'S'}, {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'}, {L_SHIFT, L_SHIFT}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'}, {'/', '?'}, {R_SHIFT, R_SHIFT}, {0, 0}, {0, 0}, {ESPACE, ESPACE}, {CAPS_LCK, CAPS_LCK}};

static char buffer[BUFFER_SIZE]; // buffer del teclado que voy lleyendo.
int currentPos = 0;

static int shift = 0;
static int capitalLetters = 0;
// sacar de internet la tabla que indica la relacionn hexacode --> tecla apretada

void checkBuffer()
{
    if (currentPos == (BUFFER_SIZE - 1)) //Si el buffer esta casi lleno
    {                                    //Reseteo el buffer de lectura
        cleanBuffer();
    }
}

void cleanBuffer()
{
    currentPos = 0;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        buffer[i] = 0;
    }
}

int getCorrectKey(int key)
{
    if (key >= 0)
    {
        return key;
    }
    return ERROR;
}

void readKeyboardBuffer()
{
    checkBuffer();

    int key = readKeyboard();

    if (key == R_SHIFT || key == L_SHIFT)
    {
        shift = 1;
        snapShotRegister(); //el SHIFT sirve como la tecla para guardar los registros
    }
    else if (key == R_SHIFT_RELEASED || key == L_SHIFT_RELEASED)
    {
        shift = 0;
    }

    if (key != ERROR)
    {
        //The scancode for key release  is obtained from it by setting the high order bit (adding 0x80 = 128).
        if (key <= 0x4F && key >= 0x01)
        {
            switch (key)
            {
            case (CAPS_LCK):
            {
                capitalLetters += 1;
                capitalLetters %= 2;
                break;
            }
            case (R_SHIFT):
            {
                break;
            }
            default:
                if ((shift || capitalLetters != 0) && (!(R_SHIFT == key || L_SHIFT == key || R_SHIFT_RELEASED == key || L_SHIFT_RELEASED == key)))
                {
                    buffer[currentPos++] = keyCodes[key][1];
                }
                else
                {
                    buffer[currentPos++] = keyCodes[key][0];
                }
            }
        }
        else if (key >= 0x81)
        {
            key -= 0x80;

            switch (key)
            {

            case (L_SHIFT || R_SHIFT):
            {
                shift = 0;
                break;
            }
            case (CAPS_LCK):
            {
                capitalLetters = 0;
                break;
            }
            default:
                break;
            }
        }
    }
    unblockReaders();
}

char *getKeyboardBuffer()
{
    return buffer;
}