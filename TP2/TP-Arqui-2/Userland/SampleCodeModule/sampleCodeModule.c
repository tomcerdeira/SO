#include <shell.h>

int main()
{
	//shellManager();
	
	createProcess("shell", &shellManager, 0, 0);
	//printf("Termino la shell \n");

	// {
	// };

	return 0;
}