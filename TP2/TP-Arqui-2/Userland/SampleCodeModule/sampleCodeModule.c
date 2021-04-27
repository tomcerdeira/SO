#include <shell.h>

int main()
{
	//shellManager();
	printf("LLEGO SHELL\n");
	createProcess("shell", &shellManager, 0, 0);
	return 0;
}