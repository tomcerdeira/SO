// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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

