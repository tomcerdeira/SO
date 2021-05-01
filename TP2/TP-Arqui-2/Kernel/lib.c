#include <libC.h>

void *memset(void *destination, int32_t c, uint64_t length);
static char buffer[64] = {'0'};

void *memset(void *destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char *dst = (char *)destination;

	while (length--)
		dst[length] = chr;

	return destination;
}

void *memcpy(void *destination, const void *source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *)destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t *d = (uint8_t *)destination;
		const uint8_t *s = (const uint8_t *)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

////////////////////////////////////////////////////////////////////////////////////////

int BCDtoInt(uint64_t number)
{

	return ((number & 0xF0) >> 4) * 10 + (number & 0xF);
}

// valores de retorno de la excepcion
static uint64_t *ip;
static uint64_t *sp;

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

// Setter del InstructionPointer y del StackPointer
void setReturns(void *ip_, void *sp_)
{
	ip = ip_;
	sp = sp_;
}

// Getter del InstructionPointer
uint64_t *getIntructionPointer()
{
	return ip;
}

// Getter del StackPointer
uint64_t *getStackPointer()
{
	return sp;
}
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

// provisto por la catedra
void printBase(uint64_t value, uint_least32_t base)
{
	uintToBase(value, buffer, base);
	print(buffer, 0xFF0000, 0x000000);
}

void printRegisters(uint64_t *stackFrame)
{
	char *registers[] = {
		"R15: ", "R14: ", "R13: ", "R12: ", "R11: ",
		"R10: ", "R9: ", "R8: ", "RSI: ", "RDI: ",
		"RBP: ", "RDX: ", "RCX: ", "RBX: ", "RAX: ",
		"RIP: ", "CS:  ", "FLAGS: ", "RSP: "};

	uint64_t buffer[CANT_REGISTERS];
	getRegisterState(buffer, stackFrame);
	for (int i = 0; i < CANT_REGISTERS; i++)
	{
		print(registers[i], 0xFF0000, 0x000000);
		print("0x", 0xFF0000, 0x000000);
		printBase(buffer[i], 16);
		print("\n", 0xFFFFFF, 0x000000);
	}
}

int strcompare(char *s1, char *s2)
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