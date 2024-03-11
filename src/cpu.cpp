#include "headers/cpu.h"

CPU::CPU()
{
	PC = 0xFFFC;
	for (bool * i = &PS[0]; i <= &PS[7]; i++)
	{
		*i = 0;
	}

	A = X = Y = 0;

	fn_Opcode[0xA5] = &CPU::INS_LDA_ZP;
	fn_Opcode[0xA9] = &CPU::INS_LDA_IM;
}

byte CPU::FetchByte( u32& cycles, MEM& memory )
{
	byte data = memory[PC];
	PC++;
	cycles--;
	return data;
}

byte CPU::ReadByte( u32& cycles, MEM& memory, word place )
{
	byte data = memory[place];
	PC++;
	return data;
}

void CPU::Execute(u32 cycles, MEM& memory)
{ 
	while ( cycles > 0 )
	{
		byte Ins = FetchByte( cycles, memory);
		(this->*fn_Opcode[Ins])(cycles, memory);
	}
}

// Instructions

void CPU::INS_LDA_ZP(u32& cycles, MEM& memory)
{
	byte ZeroPageAddress = FetchByte(cycles, memory);
	A = ReadByte(cycles, memory, ZeroPageAddress);
	PS[6] = (A == 0);
	PS[0] = (A & 0b10000000) > 0;

}

void CPU::INS_LDA_IM(u32& cycles, MEM& memory) // 0xA9
{
	A = FetchByte(cycles, memory);
	PS[6] = (A == 0);
	PS[0] = (A & 0b10000000) > 0;
}


