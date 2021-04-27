#include <timer.h>
#include <consoleManager.h>

static unsigned long ticks = 0;
static unsigned long ticksCronometro = 0;
static int cron = 0;

void timerHandler()
{
    ticks++;
    ticksCronometro++;
    if (cron)
    {
        setCursor(screenWidth() / 2 - 5 * CHAR_WIDTH, 2);
        print("TIMER: ", 0xFF0000, 0x000000);
        printBase(ticksCronometro / 18, 10);
        disableCursor();
    }
}

int getTicks()
{
    return ticks;
}

int getSecondsTimer()
{
    return ticks / 18;
}

void setCronometro(int activate)
{
    if (activate)
    {
        ticksCronometro = 0;
        cron = 1;
    }
    else
    {
        cron = 0;
    }
}

int getSecondsCronometro(){
    return ticksCronometro /18;
}