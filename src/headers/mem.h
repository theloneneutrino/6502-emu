#include "includes.h"

class MEM
{
	static constexpr u32 MAX_MEM = 1024 * 64;
	byte Data[MAX_MEM];
	
	public:
	
	MEM();
	
	byte& operator[](u32 Address);
	
	void WriteWord(u32& cycles, word value, u32 Address);
};
