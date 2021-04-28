#include <shell.h>

int main()
{
	//shellManager();
	createProcess("shell", &shellManager, 0, 0);
	while (1)
	{
	};

	return 0;
}