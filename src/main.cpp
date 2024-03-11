#include "headers/cpu.h"

int main()
{
	MEM mem;
	CPU cpu;
	//start - inline a little program
	mem[0xFFFC] = 0x20;
	mem[0xFFFD] = 0x42;
	mem[0xFFFE] = 0x42;
	mem[0x4242] = 0xA9;
	mem[0x4243] = 0x84;
	//end
	cpu.Execute(9, mem);
	cpu.print();
	return 0;
}
