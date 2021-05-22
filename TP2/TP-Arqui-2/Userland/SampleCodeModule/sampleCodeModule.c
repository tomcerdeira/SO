#include <shell.h>


int main()
{
	createProcess("shell", &shellManager, 0, 0, 1);
	halt();

	while (1)
	{
		/* code */
	}

	return 0;
}

