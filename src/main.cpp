#include "headers/cpu.h"

int main()
{
	MEM mem;
	CPU cpu;
	//start - inline a little program
	mem[0xFFFC] = 0xA9;
	mem[0xFFFD] = 0x2A;
	//end
	cpu.Execute(2, mem);
	return 0;
}
