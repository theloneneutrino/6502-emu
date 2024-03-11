#include "mem.h"

class CPU
{
	word PC;
	byte SP;

	byte A, X, Y; //registers
	bool PS[8];   //status of CPU: NV_BDIZC
	
	void (CPU::*fn_Opcode[256]) (u32& cycles, MEM& memory);

	byte FetchByte( u32& cycles, MEM& memory );
	
	byte ReadByte( u32& cycles, MEM& memory, word place );
	
	public:
	
	CPU();
	
	void Execute(u32 cycles, MEM& memory);

	private:
	
	void INS_LDA_ZP(u32& cycles, MEM& memory); // 0xA5
	void INS_LDA_IM(u32& cycles, MEM& memory); // 0xA9
};
