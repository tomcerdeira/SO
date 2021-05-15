#include <shell.h>

void funcion();

int main()
{
	//shellManager();
	// printf("Empiezo la funcion \n");
	// createProcess("funcion", &funcion, 0, 0);
	// printf("Termino la funcion \n");
	createProcess("shell", &shellManager, 0, 0);
	//createProcess("shell2", &shellManager, 0, 0);
	halt();
	//printf("Termino la shell \n");

	while (1)
	{
		/* code */
	}

	// {
	// };

	return 0;
}

void funcion()
{
	printf("HOLAAAAAAAA\n");
}
