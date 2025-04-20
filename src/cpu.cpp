#include "headers/cpu.h" 

CPU::CPU()
{
	PC = 0xFFFC;
  C = Z = I = D = B = V = N = 0;

	A = X = Y = 0;

	fn_Opcode[0xA5] = &CPU::INS_LDA_ZP;
	fn_Opcode[0xA9] = &CPU::INS_LDA_IM;
	fn_Opcode[0xB5] = &CPU::INS_LDA_ZPX;
}

byte CPU::FetchByte( u32& cycles, MEM& memory )
{
	byte data = memory[PC];
	PC++;
	cycles--;
	return data;
}

word CPU::FetchWord( u32& cycles, MEM& memory)
{
	word data = memory[PC];
	PC++;
	data |= (memory[PC] << 8 );
	PC++;
	cycles -= 2;

	return data;
}

byte CPU::ReadByte( u32& cycles, MEM& memory, byte place )
{
	byte data = memory[place];
	cycles--;
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

void CPU::print()
{
	printf("A: %d, X: %d Y: %d\n", A, X, Y);
}

void CPU::LDASetStatus()
{
	PS[6] = (A == 0);
	PS[0] = (A & 0b10000000) > 0;
}
// Instructions

void CPU::INS_LDA_IM(u32& cycles, MEM& memory) // 0xA9
{
	A = FetchByte(cycles, memory);
	LDASetStatus();
}

void CPU::INS_LDA_ZP(u32& cycles, MEM& memory) // 0xA5
{
	byte ZeroPageAddress = FetchByte(cycles, memory);
	A = ReadByte(cycles, memory, ZeroPageAddress);
	LDASetStatus();
}

void CPU::INS_LDA_ZPX(u32& cycles, MEM& memory) // 0xB5
{
	byte ZeroPageAddress = FetchByte(cycles, memory);
	ZeroPageAddress += X;
	cycles--;
	A = ReadByte(cycles, memory, ZeroPageAddress);
	LDASetStatus();
}


void CPU::INS_JSR(u32& cycles, MEM& memory) // 0x20
{
	word SubAddr = FetchWord( cycles, memory );
	memory.WriteWord(cycles, PC - 1, SP);
	PC = SubAddr;
	cycles--;
}
