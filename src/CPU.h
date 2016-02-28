#pragma once

#define CPU_LOG

#ifdef CPU_LOG
#include <string>
#endif
#include "utils.h"

class MMU;

/*
	8 bit
	Z80 (Similar)
	4.194304 MHz:
		4.194304 E6 cycles / s
		60 frame / s
		=
		4194304 / 60 = 69905 cycles / frame

	opcode size : 1 byte: xx
				  2 bytes: CB xx
	instruction size : 1-3 bytes
*/

class CPU
{
public:
	CPU();
	~CPU();

	void reset();
	int tick();
	void connectMMU(MMU& mmu) { m_MMU = &mmu; }

	static const int MAX_CYCLES_PER_FRAME{ 69905 };

private:
	//Registers
	u16 PC;
	u16 SP;

	union {
		u16 AF;
		struct {
			u8 F; //Flags
			u8 A; //Accumulator
		};
	};

	/*
	Flags

	Bit  Name  Set Clr  Expl.
	7    zf    Z   NZ   Zero Flag
	6    n     -   -    Add/Sub-Flag (BCD)
	5    h     -   -    Half Carry Flag (BCD)
	4    cy    C   NC   Carry Flag
	3-0  -     -   -    Not used (always zero)

	Z: 1 if result last operation is 0
	C: 1 if result last add > 0xFF (8bit) 0xFFFF (16bit)
	     if result last sub < 0
		 if result last rot/shift has shifted-out 1 bit
	N,H: DAA instruction (see doc)
	*/

	union {
		u16 BC;
		struct {
			u8 C;
			u8 B;
		};
	};

	union {
		u16 DE;
		struct {
			u8 E;
			u8 D;
		};
	};

	union {
		u16 HL;
		struct {
			u8 L;
			u8 H;
		};
	};

	MMU* m_MMU{ nullptr };

#ifdef CPU_LOG
	static std::string opToString(u8 op);
#endif
};
