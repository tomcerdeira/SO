#include <shell.h>

void funcion();

int main()
{
	//shellManager();
	// printf("Empiezo la funcion \n");
	// createProcess("funcion", &funcion, 0, 0);

	createProcess("shell", &shellManager, 0, 0, 10);
	halt_cpu();

	//createProcess("shell2", &shellManager, 0, 0);

	//printf("Termino la shell \n");

	// while (1)
	// {
	// 	/* code */
	// }

	// {
	// };

	return 0;
}

void funcion()
{
	printf("HOLAAAAAAAA\n");
}
