#include "headers/mem.h"

MEM::MEM()
{
	for(u32 i = 0; i < MAX_MEM; i++)
	{
		Data[i] = 0;
	}
}

byte& MEM::operator[](u32 Address)
{
	return Data[Address];
}

void MEM::WriteWord(u32& cycles, word value, u32 Address)
{
	Data[Address]	= value & 0xFF;
	Data[Address]	= value >> 8;
	cycles -= 2;
}
