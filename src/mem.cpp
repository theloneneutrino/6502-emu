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
