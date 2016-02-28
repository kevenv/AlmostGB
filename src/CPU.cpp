#include "CPU.h"

#ifdef CPU_LOG
#include <iostream>
#include "libs\cppformat\format.h"
#endif
#include "MMU.h"

#define SET_FLAG(n) F |= 1 << n;
#define CLR_FLAG(n) F &= ~(1 << n);

CPU::CPU()
{

}

CPU::~CPU()
{

}

void CPU::reset()
{
	PC = 0x100;
	SP = 0xFFFE;

	AF = 0x01B0;
	BC = 0x0013;
	DE = 0x00D8;
	HL = 0x014D;

	m_MMU->write8(0xFF05, 0x00); // TIMA
	m_MMU->write8(0xFF06, 0x00); // TMA
	m_MMU->write8(0xFF07, 0x00); // TAC
	m_MMU->write8(0xFF10, 0x80); // NR10
	m_MMU->write8(0xFF11, 0xBF); // NR11
	m_MMU->write8(0xFF12, 0xF3); // NR12
	m_MMU->write8(0xFF14, 0xBF); // NR14
	m_MMU->write8(0xFF16, 0x3F); // NR21
	m_MMU->write8(0xFF17, 0x00); // NR22
	m_MMU->write8(0xFF19, 0xBF); // NR24
	m_MMU->write8(0xFF1A, 0x7F); // NR30
	m_MMU->write8(0xFF1B, 0xFF); // NR31
	m_MMU->write8(0xFF1C, 0x9F); // NR32
	m_MMU->write8(0xFF1E, 0xBF); // NR33
	m_MMU->write8(0xFF20, 0xFF); // NR41
	m_MMU->write8(0xFF21, 0x00); // NR42
	m_MMU->write8(0xFF22, 0x00); // NR43
	m_MMU->write8(0xFF23, 0xBF); // NR30
	m_MMU->write8(0xFF24, 0x77); // NR50
	m_MMU->write8(0xFF25, 0xF3); // NR51
	m_MMU->write8(0xFF26, 0xF1); // NR52
	m_MMU->write8(0xFF40, 0x91); // LCDC
	m_MMU->write8(0xFF42, 0x00); // SCY
	m_MMU->write8(0xFF43, 0x00); // SCX
	m_MMU->write8(0xFF45, 0x00); // LYC
	m_MMU->write8(0xFF47, 0xFC); // BGP
	m_MMU->write8(0xFF48, 0xFF); // OBP0
	m_MMU->write8(0xFF49, 0xFF); // OBP1
	m_MMU->write8(0xFF4A, 0x00); // WY
	m_MMU->write8(0xFF4B, 0x00); // WX
	m_MMU->write8(0xFFFF, 0x00); // IE
}

int CPU::tick()
{
	u8 n8 = 0;
	u16 n16 = 0;

	u8 op = m_MMU->read8(PC++);
#ifdef CPU_LOG
	std::cout << fmt::format("EXEC ({:#x}) {}", op, opToString(op)) << std::endl;
#endif
	switch (op) {

	//NOP
	case 0x00:
		return 4;

	//XOR n
	case 0xAF:
		A = A ^ A;
		if (A == 0) {
			SET_FLAG(FLAG_Z);
		}
		else {
			CLR_FLAG(FLAG_Z);
		}
		return 4;
	case 0xA8:
		A = A ^ B;
		if (A == 0) {
			SET_FLAG(FLAG_Z);
		}
		else {
			CLR_FLAG(FLAG_Z);
		}
		return 4;
	case 0xA9:
		A = A ^ C;
		if (A == 0) {
			SET_FLAG(FLAG_Z);
		}
		else {
			CLR_FLAG(FLAG_Z);
		}
		return 4;
	case 0xAA:
		A = A ^ D;
		if (A == 0) {
			SET_FLAG(FLAG_Z);
		}
		else {
			CLR_FLAG(FLAG_Z);
		}
		return 4;
	case 0xAB:
		A = A ^ E;
		if (A == 0) {
			SET_FLAG(FLAG_Z);
		}
		else {
			CLR_FLAG(FLAG_Z);
		}
		return 4;
	case 0xAC:
		A = A ^ H;
		if (A == 0) {
			SET_FLAG(FLAG_Z);
		}
		else {
			CLR_FLAG(FLAG_Z);
		}
		return 4;
	case 0xAD:
		A = A ^ L;
		if (A == 0) {
			SET_FLAG(FLAG_Z);
		}
		else {
			CLR_FLAG(FLAG_Z);
		}
		return 4;
	case 0xAE:
		A = A ^ m_MMU->read8(HL);
		if (A == 0) {
			SET_FLAG(FLAG_Z);
		}
		else {
			CLR_FLAG(FLAG_Z);
		}
		return 8;
	case 0xEE:
		n8 = m_MMU->read8(PC++);
		A = A ^ n8;
		if (A == 0) {
			SET_FLAG(FLAG_Z);
		}
		else {
			CLR_FLAG(FLAG_Z);
		}
		return 8;

	//JP nn nn
	case 0xC3:
		PC = m_MMU->read16(PC);
		return 16;

	default:
#ifdef CPU_LOG
		std::cout << fmt::format("EXEC ERROR ({:#x}) {}: {}", op, opToString(op), "unimplemented instruction") << std::endl;
#endif
		return 0;
	}
}

#ifdef CPU_LOG

std::string CPU::opToString(u8 op)
{
	switch (op) {
	#include "gen/opcodes_str.cpp"
	default: return "Unknown instruction";
	}
}

#endif