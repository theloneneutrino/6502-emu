#include "mem.h"

class CPU
{
	word PC;
	byte SP;

	byte A, X, Y; //registers
	bool PS[8];   //status of CPU: NV_BDIZC
	
	void (CPU::*fn_Opcode[256]) (u32& cycles, MEM& memory);

	byte FetchByte( u32& cycles, MEM& memory );
	
	word FetchWord( u32& cycles, MEM& memory );

	byte ReadByte( u32& cycles, MEM& memory, byte place );
	
	void LDASetStatus();

	public:
	
	CPU();
	
	void Execute(u32 cycles, MEM& memory);

	void print();

	private:
	
	void INS_LDA_IM(u32&, MEM&); // 0xA9
	void INS_LDA_ZP(u32&, MEM&); // 0xA5
	void INS_LDA_ZPX(u32&, MEM&); // 0xB5
	void INS_JSR(u32&, MEM&);
};
