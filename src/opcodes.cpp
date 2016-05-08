
void CPU::LD_8(u8& dst, u8 src)
{
	dst = src;
}

void CPU::LD_8(u16 addr, u8 src)
{
	m_MMU->write8(addr, src);
}

void CPU::LD_8_ind(u8& dst, u16 addr)
{
	dst = m_MMU->read8(addr);
}

void CPU::LDI()
{
	m_MMU->write8(HL, A);
	HL++;
}

void CPU::LDI_ind()
{
	A = m_MMU->read8(HL);
	HL++;
}

void CPU::LDD()
{
	m_MMU->write8(HL, A);
	HL--;
}

void CPU::LDD_ind()
{
	A = m_MMU->read8(HL);
	HL--;
}

void CPU::LDH()
{
	u8 offset = m_MMU->read8(PC++);
	m_MMU->write8( (u16)(0xFF00) + offset, A);
}

void CPU::LDH_ind()
{
	u8 offset = m_MMU->read8(PC++);
	A = m_MMU->read8( (u16)(0xFF00) + offset );
}

void CPU::LD_16(u16& dst, u16 src)
{
	dst = src;
}

void CPU::LD_16_SP()
{
	SP = m_MMU->read16(PC);
	PC += 2;
}

void CPU::PUSH(u16 src)
{
	m_MMU->write8(SP, (u8)((src & 0x00FF) >> 0) );
	SP--;
	m_MMU->write8(SP, (u8)((src & 0xFF00) >> 8) );
	SP--;
}

void CPU::POP(u16& dst)
{
	u8 hi;
	hi = m_MMU->read8(SP);
	SP++;
	u8 lo;
	lo = m_MMU->read8(SP);
	SP++;
	dst = (hi << 8) | lo;
}

void CPU::LDHL()
{
	s8 offset = m_MMU->read8(PC++);
	HL = SP + offset;
	F = 0;
	//if (offset >= 0) {
		if (SP + offset > 0xFFFF) {
			SET_FLAG(FLAG_C);
		}
		if ((SP & 0x0F00) + ((offset & 0x0F) << 8) > 0x0FFF) {
			SET_FLAG(FLAG_H);
		}
	//}
	/*else {
		if ((s16)HL < 0) {
			SET_FLAG(FLAG_C);
		}
		//set half carry?
	}*/

	//implementation details:
	//do we handle subtracting differently than addition?
	//for 16bits, is the HalfCarry calculated 0F00 or 000F?
}

void CPU::ADD_8(u8 src)
{
	u32 result = A + src;
	F = 0;
	if (result == 0) {
		SET_FLAG(FLAG_Z);
	}
	if (result > 0xFF) {
		SET_FLAG(FLAG_C);
	}
	if ((result & 0x0F) > 0x0F) {
		SET_FLAG(FLAG_H);
	}
	A = result;
}

void CPU::SUB_8(u8 src)
{
	u32 result = A - src;
	F = 0;
	SET_FLAG(FLAG_N);
	if (result == 0) {
		SET_FLAG(FLAG_Z);
	}
	if (src > A) {
		SET_FLAG(FLAG_C);
	}
	if ((src & 0x0F) > (A & 0x0F)) {
		SET_FLAG(FLAG_H);
	}
	A = result;
}

void CPU::ADC_8(u8 src)
{
	u32 result = A + src + CHK_FLAG(FLAG_C);
	F = 0;
	if (result == 0) {
		SET_FLAG(FLAG_Z);
	}
	if (result > 0xFF) {
		SET_FLAG(FLAG_C);
	}
	if ((result & 0x0F) > 0x0F) {
		SET_FLAG(FLAG_H);
	}
	A = result;
}

void CPU::SBC_8(u8 src)
{
	u32 result = A - src - CHK_FLAG(FLAG_C);
	F = 0;
	SET_FLAG(FLAG_N);
	if (result == 0) {
		SET_FLAG(FLAG_Z);
	}
	if (src > A) {
		SET_FLAG(FLAG_C);
	}
	if ((src & 0x0F) > (A & 0x0F)) {
		SET_FLAG(FLAG_H);
	}
	A = result;
}

void CPU::AND_8(u8 src)
{
	A = A & src;
	F = 0;
	SET_FLAG(FLAG_H);
	if (A == 0) SET_FLAG(FLAG_Z);
}

void CPU::XOR_8(u8 src)
{
	A = A ^ src;
	F = 0;
	if (A == 0) SET_FLAG(FLAG_Z);
}

void CPU::OR_8(u8 src)
{
	A = A | src;
	F = 0;
	if (A == 0) SET_FLAG(FLAG_Z);
}

void CPU::CP_8(u8 src)
{
	F = 0;
	SET_FLAG(FLAG_N);
	if (A - src == 0) {
		SET_FLAG(FLAG_Z);
	}
	if (src > A) {
		SET_FLAG(FLAG_C);
	}
	if ((src & 0x0F) > (A & 0x0F)) {
		SET_FLAG(FLAG_H);
	}
}

void CPU::INC(u8& dst)
{
	u8 result = dst + 1;

	F = 0;
	u8 carryFlag = CHK_FLAG(FLAG_C);
	if (result == 0) SET_FLAG(FLAG_Z);
	if ((result & 0x0F) > 0x0F) SET_FLAG(FLAG_H);
	F |= carryFlag;

	dst = result;
}

void CPU::INC_ind(u16 addr)
{
	u8 result = m_MMU->read8(addr) + 1;

	u8 carryFlag = CHK_FLAG(FLAG_C);
	F = 0;
	if (result == 0) SET_FLAG(FLAG_Z);
	if ((result & 0x0F) > 0x0F) SET_FLAG(FLAG_H);
	F |= carryFlag;

	m_MMU->write8(addr, result);
}

void CPU::DEC(u8& dst)
{
	u8 result = dst - 1;

	u8 carryFlag = CHK_FLAG(FLAG_C);
	F = 0;
	if (result == 0) SET_FLAG(FLAG_Z);
	SET_FLAG(FLAG_N);
	if ((result & 0x0F) > 0x0F) SET_FLAG(FLAG_H);
	F |= carryFlag;

	dst = result;
}

void CPU::DEC_ind(u16 addr)
{
	u8 result = m_MMU->read8(addr) - 1;

	u8 carryFlag = CHK_FLAG(FLAG_C);
	F = 0;
	if (result == 0) SET_FLAG(FLAG_Z);
	SET_FLAG(FLAG_N);
	if ((result & 0x0F) > 0x0F) SET_FLAG(FLAG_H);
	F |= carryFlag;

	m_MMU->write8(addr, result);
}

void CPU::JP_addr()
{
	PC = m_MMU->read16(PC);
}

int CPU::JR_cond(u8 cond)
{
	if (cond) {
		u8 offset = m_MMU->read8(PC++);
		if (offset > 3) {
			PC -= ~(s8)offset+1;
		}
		else {
			PC += offset;
		}
		return 12;
	}
	else {
		PC++;
		return 8;
	}
}

void CPU::SET(u8& dst, u8 b)
{
	dst |= 1 << b;
}

void CPU::SET(u16 addr, u8 b)
{
	u8 value = m_MMU->read8(addr);
	SET(value, b);
	m_MMU->write8(addr, value);
}

void CPU::RES(u8& dst, u8 b)
{
	dst &= ~(1 << b);
}

void CPU::RES(u16 addr, u8 b)
{
	u8 value = m_MMU->read8(addr);
	RES(value, b);
	m_MMU->write8(addr, value);
}

void CPU::BIT(u8 src, u8 b)
{
	u8 bit = (src >> b) & 1;

	u8 carryFlag = CHK_FLAG(FLAG_C);
	F = 0;
	if (bit == 0) {
		SET_FLAG(FLAG_Z);
	}
	CLR_FLAG(FLAG_N);
	SET_FLAG(FLAG_H);
	F |= carryFlag;
}

void CPU::BIT(u16 addr, u8 b)
{
	u8 value = m_MMU->read8(addr);
	BIT(value, b);
}

void CPU::SWAP(u8& dst)
{
	u8 lo = dst & 0x0F;
	u8 hi = (dst & 0xF0) >> 4;
	dst = (lo << 4) | hi;

	F = 0;
	if (dst == 0) {
		SET_FLAG(FLAG_Z);
	}
}

void CPU::SWAP(u16 addr)
{
	u8 value = m_MMU->read8(addr);
	SWAP(value);
	m_MMU->write8(addr, value);
}

void CPU::SRL(u8& dst)
{
	u8 LSB = dst & 0x01;
	dst >>= 1;

	F = 0;
	if (dst == 0) {
		SET_FLAG(FLAG_Z);
	}
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);
	if (LSB == 1) {
		SET_FLAG(FLAG_C);
	}
}

void CPU::SRL(u16 addr)
{
	u8 value = m_MMU->read8(addr);
	SRL(value);
	m_MMU->write8(addr, value);
}

void CPU::SLA(u8& dst)
{
	u8 MSB = (dst & 0x80) >> 7;
	dst <<= 1;

	F = 0;
	if (dst == 0) {
		SET_FLAG(FLAG_Z);
	}
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);
	if (MSB == 1) {
		SET_FLAG(FLAG_C);
	}
}

void CPU::SLA(u16 addr)
{
	u8 value = m_MMU->read8(addr);
	SLA(value);
	m_MMU->write8(addr, value);
}

void CPU::SRA(u8& dst)
{
	u8 LSB = dst & 0x01;
	u8 MSB = dst & 0x80;
	dst = MSB | (dst >> 1);

	F = 0;
	if (dst == 0) {
		SET_FLAG(FLAG_Z);
	}
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);
	if (LSB == 1) {
		SET_FLAG(FLAG_C);
	}
}

void CPU::SRA(u16 addr)
{
	u8 value = m_MMU->read8(addr);
	SRA(value);
	m_MMU->write8(addr, value);
}

void CPU::RL(u8& dst)
{
	u8 MSB = (dst & 0x80) >> 7;
	dst = (dst << 1) | CHK_FLAG(FLAG_C);

	F = 0;
	if (dst == 0) {
		SET_FLAG(FLAG_Z);
	}
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);
	if (MSB == 1) {
		SET_FLAG(FLAG_C);
	}
}

void CPU::RL(u16 addr)
{
	u8 value = m_MMU->read8(addr);
	RL(value);
	m_MMU->write8(addr, value);
}

void CPU::RLC(u8& dst)
{
	u8 MSB = (dst & 0x80) >> 7;
	dst = (dst << 1) | MSB;

	F = 0;
	if (dst == 0) {
		SET_FLAG(FLAG_Z);
	}
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);
	if (MSB == 1) {
		SET_FLAG(FLAG_C);
	}
}

void CPU::RLC(u16 addr)
{
	u8 value = m_MMU->read8(addr);
	RLC(value);
	m_MMU->write8(addr, value);
}

void CPU::RR(u8& dst)
{
	u8 LSB = dst & 0x01;
	dst = (CHK_FLAG(FLAG_C) << 7) | (dst >> 1);

	F = 0;
	if (dst == 0) {
		SET_FLAG(FLAG_Z);
	}
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);
	if (LSB == 1) {
		SET_FLAG(FLAG_C);
	}
}

void CPU::RR(u16 addr)
{
	u8 value = m_MMU->read8(addr);
	RR(value);
	m_MMU->write8(addr, value);
}

void CPU::RRC(u8& dst)
{
	u8 LSB = dst & 0x01;
	dst = (LSB << 7) | (dst >> 1);

	F = 0;
	if (dst == 0) {
		SET_FLAG(FLAG_Z);
	}
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);
	if (LSB == 1) {
		SET_FLAG(FLAG_C);
	}
}

void CPU::RRC(u16 addr)
{
	u8 value = m_MMU->read8(addr);
	RRC(value);
	m_MMU->write8(addr, value);
}

int CPU::opcodeUnknown()
{
	return 0;
}

// Opcodes implementation

int CPU::opcode00() { return 4; }

int CPU::opcode01() { LD_16(BC, m_MMU->read16(PC)); PC += 2; return 12; }

int CPU::opcode02() { LD_8(BC, A); return 8; }

int CPU::opcode03()
{
	return opcodeUnknown();
}

int CPU::opcode04() { INC(B); return 4; }

int CPU::opcode05() { DEC(B); return 4; }

int CPU::opcode06() { LD_8(B, m_MMU->read8(PC++)); return 8; }

int CPU::opcode07()
{
	return opcodeUnknown();
}

int CPU::opcode08() { LD_16_SP(); return 20; }

int CPU::opcode09()
{
	return opcodeUnknown();
}

int CPU::opcode0A() { LD_8_ind(A, BC); return 8; }

int CPU::opcode0B()
{
	return opcodeUnknown();
}

int CPU::opcode0C() { INC(C); return 4; }

int CPU::opcode0D() { DEC(C); return 4; }

int CPU::opcode0E() { LD_8(C, m_MMU->read8(PC++)); return 8; }

int CPU::opcode0F()
{
	return opcodeUnknown();
}


int CPU::opcode10()
{
	return opcodeUnknown();
}

int CPU::opcode11() { LD_16(DE, m_MMU->read16(PC)); PC += 2; return 12; }

int CPU::opcode12() { LD_8(DE, A); return 8; }

int CPU::opcode13()
{
	return opcodeUnknown();
}

int CPU::opcode14() { INC(C); return 4; }

int CPU::opcode15() { DEC(D); return 4; }

int CPU::opcode16() { LD_8(D, m_MMU->read8(PC++)); return 8; }

int CPU::opcode17()
{
	return opcodeUnknown();
}

int CPU::opcode18()
{
	return opcodeUnknown();
}

int CPU::opcode19()
{
	return opcodeUnknown();
}

int CPU::opcode1A() { LD_8_ind(A, DE); return 8; }

int CPU::opcode1B()
{
	return opcodeUnknown();
}

int CPU::opcode1C() { INC(E); return 4; }

int CPU::opcode1D() { DEC(E); return 4; }

int CPU::opcode1E() { LD_8(E, m_MMU->read8(PC++)); return 8; }

int CPU::opcode1F()
{
	return opcodeUnknown();
}


int CPU::opcode20() { return JR_cond( !CHK_FLAG(FLAG_Z) ); }

int CPU::opcode21() { LD_16(HL, m_MMU->read16(PC)); PC += 2; return 12; }

int CPU::opcode22() { LDI(); return 8; }

int CPU::opcode23()
{
	return opcodeUnknown();
}

int CPU::opcode24() { INC(H); return 4; }

int CPU::opcode25() { DEC(H); return 4; }

int CPU::opcode26() { LD_8(H, m_MMU->read8(PC++)); return 8; }

int CPU::opcode27()
{
	return opcodeUnknown();
}

int CPU::opcode28()
{
	return opcodeUnknown();
}

int CPU::opcode29()
{
	return opcodeUnknown();
}

int CPU::opcode2A() { LDI_ind(); return 8; }

int CPU::opcode2B()
{
	return opcodeUnknown();
}

int CPU::opcode2C() { INC(L); return 4; }

int CPU::opcode2D() { DEC(L); return 4; }

int CPU::opcode2E() { LD_8(L, m_MMU->read8(PC++)); return 8; }

int CPU::opcode2F()
{
	return opcodeUnknown();
}


int CPU::opcode30()
{
	return opcodeUnknown();
}

int CPU::opcode31() { LD_16(SP, m_MMU->read16(PC)); PC += 2; return 12; }

int CPU::opcode32() { LDD(); return 8; }

int CPU::opcode33()
{
	return opcodeUnknown();
}

int CPU::opcode34() { INC_ind(HL); return 12; }

int CPU::opcode35() { DEC_ind(HL); return 12; }

int CPU::opcode36() { LD_8(HL, m_MMU->read8(PC++)); return 12; }

int CPU::opcode37()
{
	return opcodeUnknown();
}

int CPU::opcode38()
{
	return opcodeUnknown();
}

int CPU::opcode39()
{
	return opcodeUnknown();
}

int CPU::opcode3A() { LDD_ind(); return 8; }

int CPU::opcode3B()
{
	return opcodeUnknown();
}

int CPU::opcode3C() { INC(A); return 4; }

int CPU::opcode3D() { DEC(A); return 4; }

int CPU::opcode3E() { LD_8(A, m_MMU->read8(PC++)); return 8; }

int CPU::opcode3F()
{
	return opcodeUnknown();
}


int CPU::opcode40() { LD_8(B, B); return 4; }

int CPU::opcode41() { LD_8(B, C); return 4; }

int CPU::opcode42() { LD_8(B, D); return 4; }

int CPU::opcode43() { LD_8(B, E); return 4; }

int CPU::opcode44() { LD_8(B, H); return 4; }

int CPU::opcode45() { LD_8(B, L); return 4; }

int CPU::opcode46()
{
	return opcodeUnknown();
}
//{ LD_8reg(B, m_MMU->read8(HL)); return 8; }

int CPU::opcode47() { LD_8(B, A); return 4; }

int CPU::opcode48() { LD_8(C, B); return 4; }

int CPU::opcode49() { LD_8(C, C); return 4; }

int CPU::opcode4A() { LD_8(C, D); return 4; }

int CPU::opcode4B() { LD_8(C, E); return 4; }

int CPU::opcode4C() { LD_8(C, H); return 4; }

int CPU::opcode4D() { LD_8(C, L); return 4; }

int CPU::opcode4E() { LD_8_ind(C, HL); return 8; }

int CPU::opcode4F() { LD_8(C, A); return 4; }


int CPU::opcode50() { LD_8(D, B); return 4; }

int CPU::opcode51() { LD_8(D, C); return 4; }

int CPU::opcode52() { LD_8(D, D); return 4; }

int CPU::opcode53() { LD_8(D, E); return 4; }

int CPU::opcode54() { LD_8(D, H); return 4; }

int CPU::opcode55() { LD_8(D, L); return 4; }

int CPU::opcode56()
{
	return opcodeUnknown();
}
// { LD_8reg(D, m_MMU->read8(HL)); return 8; }

int CPU::opcode57() { LD_8(D, A); return 4; }

int CPU::opcode58() { LD_8(E, B); return 4; }

int CPU::opcode59() { LD_8(E, C); return 4; }

int CPU::opcode5A() { LD_8(E, D); return 4; }

int CPU::opcode5B() { LD_8(E, E); return 4; }

int CPU::opcode5C() { LD_8(E, H); return 4; }

int CPU::opcode5D() { LD_8(E, L); return 4; }

int CPU::opcode5E() { LD_8_ind(E, HL); return 8; }

int CPU::opcode5F() { LD_8(E, A); return 4; }


int CPU::opcode60() { LD_8(H, B); return 4; }

int CPU::opcode61() { LD_8(H, C); return 4; }

int CPU::opcode62() { LD_8(H, D); return 4; }

int CPU::opcode63() { LD_8(H, E); return 4; }

int CPU::opcode64() { LD_8(H, H); return 4; }

int CPU::opcode65() { LD_8(H, L); return 4; }

int CPU::opcode66() 
{
	return opcodeUnknown();
}
//{ LD_8reg(H, m_MMU->read8(HL)); return 8; }

int CPU::opcode67() { LD_8(H, A); return 4; }

int CPU::opcode68() { LD_8(L, B); return 4; }

int CPU::opcode69() { LD_8(L, C); return 4; }

int CPU::opcode6A() { LD_8(L, D); return 4; }

int CPU::opcode6B() { LD_8(L, E); return 4; }

int CPU::opcode6C() { LD_8(L, H); return 4; }

int CPU::opcode6D() { LD_8(L, L); return 4; }

int CPU::opcode6E() { LD_8_ind(L, HL); return 8; }

int CPU::opcode6F() { LD_8(L, A); return 4; }


int CPU::opcode70() { LD_8(HL, B); return 8; }

int CPU::opcode71() { LD_8(HL, C); return 8; }

int CPU::opcode72() { LD_8(HL, D); return 8; }

int CPU::opcode73() { LD_8(HL, E); return 8; }

int CPU::opcode74() { LD_8(HL, H); return 8; }

int CPU::opcode75() { LD_8(HL, L); return 8; }

int CPU::opcode76()
{
	return opcodeUnknown();
}

int CPU::opcode77() { LD_8(HL, A); return 8; }

int CPU::opcode78() { LD_8(A, B); return 4; }

int CPU::opcode79() { LD_8(A, C); return 4; }

int CPU::opcode7A() { LD_8(A, D); return 4; }

int CPU::opcode7B() { LD_8(A, E); return 4; }

int CPU::opcode7C() { LD_8(A, H); return 4; }

int CPU::opcode7D() { LD_8(A, L); return 4; }

int CPU::opcode7E() { LD_8_ind(A, HL); return 8; }

int CPU::opcode7F() { LD_8(A, A); return 4; }


int CPU::opcode80() { ADD_8(B); return 4; }

int CPU::opcode81() { ADD_8(C); return 4; }

int CPU::opcode82() { ADD_8(D); return 4; }

int CPU::opcode83() { ADD_8(E); return 4; }

int CPU::opcode84() { ADD_8(H); return 4; }

int CPU::opcode85() { ADD_8(L); return 4; }

int CPU::opcode86() { ADD_8(m_MMU->read8(HL)); return 8; }

int CPU::opcode87() { ADD_8(A); return 4; }

int CPU::opcode88() { ADC_8(B); return 4; }

int CPU::opcode89() { ADC_8(C); return 4; }

int CPU::opcode8A() { ADC_8(D); return 4; }

int CPU::opcode8B() { ADC_8(E); return 4; }

int CPU::opcode8C() { ADC_8(H); return 4; }

int CPU::opcode8D() { ADC_8(L); return 4; }

int CPU::opcode8E() { ADC_8(m_MMU->read8(HL)); return 8; }

int CPU::opcode8F() { ADC_8(A); return 4; }


int CPU::opcode90() { SUB_8(B); return 4; }

int CPU::opcode91() { SUB_8(C); return 4; }

int CPU::opcode92() { SUB_8(D); return 4; }

int CPU::opcode93() { SUB_8(E); return 4; }

int CPU::opcode94() { SUB_8(H); return 4; }

int CPU::opcode95() { SUB_8(L); return 4; }

int CPU::opcode96() { SUB_8(m_MMU->read8(HL)); return 8; }

int CPU::opcode97() { SUB_8(A); return 4; }

int CPU::opcode98() { SBC_8(B); return 4; }

int CPU::opcode99() { SBC_8(C); return 4; }

int CPU::opcode9A() { SBC_8(D); return 4; }

int CPU::opcode9B() { SBC_8(E); return 4; }

int CPU::opcode9C() { SBC_8(H); return 4; }

int CPU::opcode9D() { SBC_8(L); return 4; }

int CPU::opcode9E() { SBC_8(m_MMU->read8(HL)); return 8; }

int CPU::opcode9F() { SBC_8(A); return 4; }


int CPU::opcodeA0() { AND_8(B); return 4; }

int CPU::opcodeA1() { AND_8(C); return 4; }

int CPU::opcodeA2() { AND_8(D); return 4; }

int CPU::opcodeA3() { AND_8(E); return 4; }

int CPU::opcodeA4() { AND_8(H); return 4; }

int CPU::opcodeA5() { AND_8(L); return 4; }

int CPU::opcodeA6() { AND_8(m_MMU->read8(HL)); return 8; }

int CPU::opcodeA7() { AND_8(A); return 4; }

int CPU::opcodeA8() { XOR_8(B); return 4; }

int CPU::opcodeA9() { XOR_8(C); return 4; }

int CPU::opcodeAA() { XOR_8(D); return 4; }

int CPU::opcodeAB() { XOR_8(E); return 4; }

int CPU::opcodeAC() { XOR_8(H); return 4; }

int CPU::opcodeAD() { XOR_8(L); return 4; }

int CPU::opcodeAE() { XOR_8(m_MMU->read8(HL)); return 8; }

int CPU::opcodeAF() { XOR_8(A); return 4; }


int CPU::opcodeB0() { OR_8(B); return 4; }

int CPU::opcodeB1() { OR_8(C); return 4; }

int CPU::opcodeB2() { OR_8(D); return 4; }

int CPU::opcodeB3() { OR_8(E); return 4; }

int CPU::opcodeB4() { OR_8(H); return 4; }

int CPU::opcodeB5() { OR_8(L); return 4; }

int CPU::opcodeB6() { OR_8(m_MMU->read8(HL)); return 8; }

int CPU::opcodeB7() { OR_8(A); return 4; }

int CPU::opcodeB8() { CP_8(B); return 4; }

int CPU::opcodeB9() { CP_8(C); return 4; }

int CPU::opcodeBA() { CP_8(D); return 4; }

int CPU::opcodeBB() { CP_8(E); return 4; }

int CPU::opcodeBC() { CP_8(H); return 4; }

int CPU::opcodeBD() { CP_8(L); return 4; }

int CPU::opcodeBE() { CP_8(m_MMU->read8(HL)); return 8; }

int CPU::opcodeBF() { CP_8(A); return 4; }


int CPU::opcodeC0()
{
	return opcodeUnknown();
}

int CPU::opcodeC1() { POP(BC); return 12; }

int CPU::opcodeC2()
{
	return opcodeUnknown();
}

int CPU::opcodeC3()
{
	JP_addr();
	return 16;
}

int CPU::opcodeC4()
{
	return opcodeUnknown();
}

int CPU::opcodeC5() { PUSH(BC); return 16; }

int CPU::opcodeC6() { ADD_8(m_MMU->read8(PC++)); return 8; }

int CPU::opcodeC7()
{
	return opcodeUnknown();
}

int CPU::opcodeC8()
{
	return opcodeUnknown();
}

int CPU::opcodeC9()
{
	return opcodeUnknown();
}

int CPU::opcodeCA()
{
	return opcodeUnknown();
}

int CPU::opcodeCB()
{
	return opcodeUnknown();
}

int CPU::opcodeCC()
{
	return opcodeUnknown();
}

int CPU::opcodeCD()
{
	return opcodeUnknown();
}

int CPU::opcodeCE() { ADC_8(m_MMU->read8(PC++)); return 8; }

int CPU::opcodeCF() { SBC_8(m_MMU->read8(PC++)); return 8; }


int CPU::opcodeD0()
{
	return opcodeUnknown();
}

int CPU::opcodeD1() { POP(DE); return 12; }

int CPU::opcodeD2()
{
	return opcodeUnknown();
}

int CPU::opcodeD3()
{
	return opcodeUnknown();
}

int CPU::opcodeD4()
{
	return opcodeUnknown();
}

int CPU::opcodeD5() { PUSH(DE); return 16; }

int CPU::opcodeD6() { SUB_8(m_MMU->read8(PC++)); return 8; }

int CPU::opcodeD7()
{
	return opcodeUnknown();
}

int CPU::opcodeD8()
{
	return opcodeUnknown();
}

int CPU::opcodeD9()
{
	return opcodeUnknown();
}

int CPU::opcodeDA()
{
	return opcodeUnknown();
}

int CPU::opcodeDB()
{
	return opcodeUnknown();
}

int CPU::opcodeDC()
{
	return opcodeUnknown();
}

int CPU::opcodeDD()
{
	return opcodeUnknown();
}

int CPU::opcodeDE()
{
	return opcodeUnknown();
}

int CPU::opcodeDF()
{
	return opcodeUnknown();
}


int CPU::opcodeE0() { LDH(); return 12; }

int CPU::opcodeE1() { POP(HL); return 12; }

int CPU::opcodeE2() { LD_8((u16)(0xFF00) + C, A); PC++; return 8; }

int CPU::opcodeE3()
{
	return opcodeUnknown();
}

int CPU::opcodeE4()
{
	return opcodeUnknown();
}

int CPU::opcodeE5() { PUSH(HL); return 16; }

int CPU::opcodeE6() { AND_8(m_MMU->read8(PC++)); return 8; }

int CPU::opcodeE7()
{
	return opcodeUnknown();
}

int CPU::opcodeE8()
{
	return opcodeUnknown();
}

int CPU::opcodeE9()
{
	return opcodeUnknown();
}

int CPU::opcodeEA() { LD_8( m_MMU->read16(PC), A); PC += 2; return 16; }

int CPU::opcodeEB()
{
	return opcodeUnknown();
}

int CPU::opcodeEC()
{
	return opcodeUnknown();
}

int CPU::opcodeED()
{
	return opcodeUnknown();
}

int CPU::opcodeEE() { XOR_8(m_MMU->read8(PC++)); return 8; }

int CPU::opcodeEF()
{
	return opcodeUnknown();
}


int CPU::opcodeF0() { LDH_ind(); return 12; }

int CPU::opcodeF1() { POP(AF); return 12; }

int CPU::opcodeF2() { LD_8_ind(A, (u16)(0xFF00 + C)); PC++; return 8; }

int CPU::opcodeF3()
{
	return opcodeUnknown();
}

int CPU::opcodeF4()
{
	return opcodeUnknown();
}

int CPU::opcodeF5() { PUSH(AF); return 16; }

int CPU::opcodeF6() { OR_8(m_MMU->read8(PC++)); return 8; }

int CPU::opcodeF7()
{
	return opcodeUnknown();
}

int CPU::opcodeF8() { LDHL(); return 12; }

int CPU::opcodeF9() { LD_16(SP,HL); return 8; }

int CPU::opcodeFA()
{ 
	u16 addr = m_MMU->read16(PC);
	PC += 2;
	LD_8_ind(A, addr);
	return 16;
}

int CPU::opcodeFB()
{
	return opcodeUnknown();
}

int CPU::opcodeFC()
{
	return opcodeUnknown();
}

int CPU::opcodeFD()
{
	return opcodeUnknown();
}

int CPU::opcodeFE() { CP_8(m_MMU->read8(PC++)); return 8; }

int CPU::opcodeFF()
{
	return opcodeUnknown();
}


//CB Prefix


int CPU::opcodeCB00() { RLC(B); return 8; }

int CPU::opcodeCB01() { RLC(C); return 8; }

int CPU::opcodeCB02() { RLC(D); return 8; }

int CPU::opcodeCB03() { RLC(E); return 8; }

int CPU::opcodeCB04() { RLC(H); return 8; }

int CPU::opcodeCB05() { RLC(L); return 8; }

int CPU::opcodeCB06() { RLC(HL); return 16; }

int CPU::opcodeCB07() { RLC(A); return 8; }

int CPU::opcodeCB08() { RRC(B); return 8; }

int CPU::opcodeCB09() { RRC(C); return 8; }

int CPU::opcodeCB0A() { RRC(D); return 8; }

int CPU::opcodeCB0B() { RRC(E); return 8; }

int CPU::opcodeCB0C() { RRC(H); return 8; }

int CPU::opcodeCB0D() { RRC(L); return 8; }

int CPU::opcodeCB0E() { RRC(HL); return 16; }

int CPU::opcodeCB0F() { RRC(A); return 8; }


int CPU::opcodeCB10() { RL(B); return 8; }

int CPU::opcodeCB11() { RL(C); return 8; }

int CPU::opcodeCB12() { RL(D); return 8; }

int CPU::opcodeCB13() { RL(E); return 8; }

int CPU::opcodeCB14() { RL(H); return 8; }

int CPU::opcodeCB15() { RL(L); return 8; }

int CPU::opcodeCB16() { RL(HL); return 16; }

int CPU::opcodeCB17() { RL(A); return 8; }

int CPU::opcodeCB18() { RR(B); return 8; }

int CPU::opcodeCB19() { RR(C); return 8; }

int CPU::opcodeCB1A() { RR(D); return 8; }

int CPU::opcodeCB1B() { RR(E); return 8; }

int CPU::opcodeCB1C() { RR(H); return 8; }

int CPU::opcodeCB1D() { RR(L); return 8; }

int CPU::opcodeCB1E() { RR(HL); return 16; }

int CPU::opcodeCB1F() { RR(A); return 8; }


int CPU::opcodeCB20() { SLA(B); return 8; }

int CPU::opcodeCB21() { SLA(C); return 8; }

int CPU::opcodeCB22() { SLA(D); return 8; }

int CPU::opcodeCB23() { SLA(E); return 8; }

int CPU::opcodeCB24() { SLA(H); return 8; }

int CPU::opcodeCB25() { SLA(L); return 8; }

int CPU::opcodeCB26() { SLA(HL); return 16; }

int CPU::opcodeCB27() { SLA(A); return 8; }

int CPU::opcodeCB28() { SRA(B); return 8; }

int CPU::opcodeCB29() { SRA(C); return 8; }

int CPU::opcodeCB2A() { SRA(D); return 8; }

int CPU::opcodeCB2B() { SRA(E); return 8; }

int CPU::opcodeCB2C() { SRA(H); return 8; }

int CPU::opcodeCB2D() { SRA(L); return 8; }

int CPU::opcodeCB2E() { SRA(HL); return 16; }

int CPU::opcodeCB2F() { SRA(A); return 8; }


int CPU::opcodeCB30() { SWAP(B); return 8; }

int CPU::opcodeCB31() { SWAP(C); return 8; }

int CPU::opcodeCB32() { SWAP(D); return 8; }

int CPU::opcodeCB33() { SWAP(E); return 8; }

int CPU::opcodeCB34() { SWAP(H); return 8; }

int CPU::opcodeCB35() { SWAP(L); return 8; }

int CPU::opcodeCB36() { SWAP(HL); return 16; }

int CPU::opcodeCB37() { SWAP(A); return 8; }

int CPU::opcodeCB38() { SRL(B); return 8; }

int CPU::opcodeCB39() { SRL(C); return 8; }

int CPU::opcodeCB3A() { SRL(D); return 8; }

int CPU::opcodeCB3B() { SRL(E); return 8; }

int CPU::opcodeCB3C() { SRL(H); return 8; }

int CPU::opcodeCB3D() { SRL(L); return 8; }

int CPU::opcodeCB3E() { SRL(HL); return 16; }

int CPU::opcodeCB3F() { SRL(A); return 8; }


int CPU::opcodeCB40() { BIT(B, 0); return 8; }

int CPU::opcodeCB41() { BIT(C, 0); return 8; }

int CPU::opcodeCB42() { BIT(D, 0); return 8; }

int CPU::opcodeCB43() { BIT(E, 0); return 8; }

int CPU::opcodeCB44() { BIT(H, 0); return 8; }

int CPU::opcodeCB45() { BIT(L, 0); return 8; }

int CPU::opcodeCB46() { BIT(HL, 0); return 16; }

int CPU::opcodeCB47() { BIT(A, 0); return 8; }

int CPU::opcodeCB48() { BIT(B, 1); return 8; }

int CPU::opcodeCB49() { BIT(C, 1); return 8; }

int CPU::opcodeCB4A() { BIT(D, 1); return 8; }

int CPU::opcodeCB4B() { BIT(E, 1); return 8; }

int CPU::opcodeCB4C() { BIT(H, 1); return 8; }

int CPU::opcodeCB4D() { BIT(L, 1); return 8; }

int CPU::opcodeCB4E() { BIT(HL, 1); return 16; }

int CPU::opcodeCB4F() { BIT(A, 1); return 8; }


int CPU::opcodeCB50() { BIT(B, 2); return 8; }

int CPU::opcodeCB51() { BIT(C, 2); return 8; }

int CPU::opcodeCB52() { BIT(D, 2); return 8; }

int CPU::opcodeCB53() { BIT(E, 2); return 8; }

int CPU::opcodeCB54() { BIT(H, 2); return 8; }

int CPU::opcodeCB55() { BIT(L, 2); return 8; }

int CPU::opcodeCB56() { BIT(HL, 2); return 16; }

int CPU::opcodeCB57() { BIT(A, 2); return 8; }

int CPU::opcodeCB58() { BIT(B, 3); return 8; }

int CPU::opcodeCB59() { BIT(C, 3); return 8; }

int CPU::opcodeCB5A() { BIT(D, 3); return 8; }

int CPU::opcodeCB5B() { BIT(E, 3); return 8; }

int CPU::opcodeCB5C() { BIT(H, 3); return 8; }

int CPU::opcodeCB5D() { BIT(L, 3); return 8; }

int CPU::opcodeCB5E() { BIT(HL, 3); return 16; }

int CPU::opcodeCB5F() { BIT(A, 3); return 8; }


int CPU::opcodeCB60() { BIT(B, 4); return 8; }

int CPU::opcodeCB61() { BIT(C, 4); return 8; }

int CPU::opcodeCB62() { BIT(D, 4); return 8; }

int CPU::opcodeCB63() { BIT(E, 4); return 8; }

int CPU::opcodeCB64() { BIT(H, 4); return 8; }

int CPU::opcodeCB65() { BIT(L, 4); return 8; }

int CPU::opcodeCB66() { BIT(HL, 4); return 16; }

int CPU::opcodeCB67() { BIT(A, 4); return 8; }

int CPU::opcodeCB68() { BIT(B, 5); return 8; }

int CPU::opcodeCB69() { BIT(C, 5); return 8; }

int CPU::opcodeCB6A() { BIT(D, 5); return 8; }

int CPU::opcodeCB6B() { BIT(E, 5); return 8; }

int CPU::opcodeCB6C() { BIT(H, 5); return 8; }

int CPU::opcodeCB6D() { BIT(L, 5); return 8; }

int CPU::opcodeCB6E() { BIT(HL, 5); return 16; }

int CPU::opcodeCB6F() { BIT(A, 5); return 8; }


int CPU::opcodeCB70() { BIT(B, 6); return 8; }

int CPU::opcodeCB71() { BIT(C, 6); return 8; }

int CPU::opcodeCB72() { BIT(D, 6); return 8; }

int CPU::opcodeCB73() { BIT(E, 6); return 8; }

int CPU::opcodeCB74() { BIT(H, 6); return 8; }

int CPU::opcodeCB75() { BIT(L, 6); return 8; }

int CPU::opcodeCB76() { BIT(HL, 6); return 16; }

int CPU::opcodeCB77() { BIT(A, 6); return 8; }

int CPU::opcodeCB78() { BIT(B, 7); return 8; }

int CPU::opcodeCB79() { BIT(C, 7); return 8; }

int CPU::opcodeCB7A() { BIT(D, 7); return 8; }

int CPU::opcodeCB7B() { BIT(E, 7); return 8; }

int CPU::opcodeCB7C() { BIT(H, 7); return 8; }

int CPU::opcodeCB7D() { BIT(L, 7); return 8; }

int CPU::opcodeCB7E() { BIT(HL, 7); return 16; }

int CPU::opcodeCB7F() { BIT(A, 7); return 8; }


int CPU::opcodeCB80() { RES(B, 0); return 8; }

int CPU::opcodeCB81() { RES(C, 0); return 8; }

int CPU::opcodeCB82() { RES(D, 0); return 8; }

int CPU::opcodeCB83() { RES(E, 0); return 8; }

int CPU::opcodeCB84() { RES(H, 0); return 8; }

int CPU::opcodeCB85() { RES(L, 0); return 8; }

int CPU::opcodeCB86() { RES(HL, 0); return 16; }

int CPU::opcodeCB87() { RES(A, 0); return 8; }

int CPU::opcodeCB88() { RES(B, 1); return 8; }

int CPU::opcodeCB89() { RES(C, 1); return 8; }

int CPU::opcodeCB8A() { RES(D, 1); return 8; }

int CPU::opcodeCB8B() { RES(E, 1); return 8; }

int CPU::opcodeCB8C() { RES(H, 1); return 8; }

int CPU::opcodeCB8D() { RES(L, 1); return 8; }

int CPU::opcodeCB8E() { RES(HL, 1); return 16; }

int CPU::opcodeCB8F() { RES(A, 1); return 8; }


int CPU::opcodeCB90() { RES(B, 2); return 8; }

int CPU::opcodeCB91() { RES(C, 2); return 8; }

int CPU::opcodeCB92() { RES(D, 2); return 8; }

int CPU::opcodeCB93() { RES(E, 2); return 8; }

int CPU::opcodeCB94() { RES(H, 2); return 8; }

int CPU::opcodeCB95() { RES(L, 2); return 8; }

int CPU::opcodeCB96() { RES(HL, 2); return 16; }

int CPU::opcodeCB97() { RES(A, 2); return 8; }

int CPU::opcodeCB98() { RES(B, 3); return 8; }

int CPU::opcodeCB99() { RES(C, 3); return 8; }

int CPU::opcodeCB9A() { RES(D, 3); return 8; }

int CPU::opcodeCB9B() { RES(E, 3); return 8; }

int CPU::opcodeCB9C() { RES(H, 3); return 8; }

int CPU::opcodeCB9D() { RES(L, 3); return 8; }

int CPU::opcodeCB9E() { RES(HL, 3); return 16; }

int CPU::opcodeCB9F() { RES(A, 3); return 8; }


int CPU::opcodeCBA0() { RES(B, 4); return 8; }

int CPU::opcodeCBA1() { RES(C, 4); return 8; }

int CPU::opcodeCBA2() { RES(D, 4); return 8; }

int CPU::opcodeCBA3() { RES(E, 4); return 8; }

int CPU::opcodeCBA4() { RES(H, 4); return 8; }

int CPU::opcodeCBA5() { RES(L, 4); return 8; }

int CPU::opcodeCBA6() { RES(HL, 4); return 16; }

int CPU::opcodeCBA7() { RES(A, 4); return 8; }

int CPU::opcodeCBA8() { RES(B, 5); return 8; }

int CPU::opcodeCBA9() { RES(C, 5); return 8; }

int CPU::opcodeCBAA() { RES(D, 5); return 8; }

int CPU::opcodeCBAB() { RES(E, 5); return 8; }

int CPU::opcodeCBAC() { RES(H, 5); return 8; }

int CPU::opcodeCBAD() { RES(L, 5); return 8; }

int CPU::opcodeCBAE() { RES(HL, 5); return 16; }

int CPU::opcodeCBAF() { RES(A, 5); return 8; }


int CPU::opcodeCBB0() { RES(B, 6); return 8; }

int CPU::opcodeCBB1() { RES(C, 6); return 8; }

int CPU::opcodeCBB2() { RES(D, 6); return 8; }

int CPU::opcodeCBB3() { RES(E, 6); return 8; }

int CPU::opcodeCBB4() { RES(H, 6); return 8; }

int CPU::opcodeCBB5() { RES(L, 6); return 8; }

int CPU::opcodeCBB6() { RES(HL, 6); return 16; }

int CPU::opcodeCBB7() { RES(A, 6); return 8; }

int CPU::opcodeCBB8() { RES(B, 7); return 8; }

int CPU::opcodeCBB9() { RES(C, 7); return 8; }

int CPU::opcodeCBBA() { RES(D, 7); return 8; }

int CPU::opcodeCBBB() { RES(E, 7); return 8; }

int CPU::opcodeCBBC() { RES(H, 7); return 8; }

int CPU::opcodeCBBD() { RES(L, 7); return 8; }

int CPU::opcodeCBBE() { RES(HL, 7); return 16; }

int CPU::opcodeCBBF() { RES(A, 7); return 8; }


int CPU::opcodeCBC0() { SET(B, 0); return 8; }

int CPU::opcodeCBC1() { SET(C, 0); return 8; }

int CPU::opcodeCBC2() { SET(D, 0); return 8; }

int CPU::opcodeCBC3() { SET(E, 0); return 8; }

int CPU::opcodeCBC4() { SET(H, 0); return 8; }

int CPU::opcodeCBC5() { SET(L, 0); return 8; }

int CPU::opcodeCBC6() { SET(HL, 0); return 16; }

int CPU::opcodeCBC7() { SET(A, 0); return 8; }

int CPU::opcodeCBC8() { SET(B, 1); return 8; }

int CPU::opcodeCBC9() { SET(C, 1); return 8; }

int CPU::opcodeCBCA() { SET(D, 1); return 8; }

int CPU::opcodeCBCB() { SET(E, 1); return 8; }

int CPU::opcodeCBCC() { SET(H, 1); return 8; }

int CPU::opcodeCBCD() { SET(L, 1); return 8; }

int CPU::opcodeCBCE() { SET(HL, 1); return 16; }

int CPU::opcodeCBCF() { SET(A, 1); return 8; }


int CPU::opcodeCBD0() { SET(B, 2); return 8; }

int CPU::opcodeCBD1() { SET(C, 2); return 8; }

int CPU::opcodeCBD2() { SET(D, 2); return 8; }

int CPU::opcodeCBD3() { SET(E, 2); return 8; }

int CPU::opcodeCBD4() { SET(H, 2); return 8; }

int CPU::opcodeCBD5() { SET(L, 2); return 8; }

int CPU::opcodeCBD6() { SET(HL, 2); return 16; }

int CPU::opcodeCBD7() { SET(A, 2); return 8; }

int CPU::opcodeCBD8() { SET(B, 3); return 8; }

int CPU::opcodeCBD9() { SET(C, 3); return 8; }

int CPU::opcodeCBDA() { SET(D, 3); return 8; }

int CPU::opcodeCBDB() { SET(E, 3); return 8; }

int CPU::opcodeCBDC() { SET(H, 3); return 8; }

int CPU::opcodeCBDD() { SET(L, 3); return 8; }

int CPU::opcodeCBDE() { SET(HL, 3); return 16; }

int CPU::opcodeCBDF() { SET(A, 3); return 8; }


int CPU::opcodeCBE0() { SET(B, 4); return 8; }

int CPU::opcodeCBE1() { SET(C, 4); return 8; }

int CPU::opcodeCBE2() { SET(D, 4); return 8; }

int CPU::opcodeCBE3() { SET(E, 4); return 8; }

int CPU::opcodeCBE4() { SET(H, 4); return 8; }

int CPU::opcodeCBE5() { SET(L, 4); return 8; }

int CPU::opcodeCBE6() { SET(HL, 4); return 16; }

int CPU::opcodeCBE7() { SET(A, 4); return 8; }

int CPU::opcodeCBE8() { SET(B, 5); return 8; }

int CPU::opcodeCBE9() { SET(C, 5); return 8; }

int CPU::opcodeCBEA() { SET(D, 5); return 8; }

int CPU::opcodeCBEB() { SET(E, 5); return 8; }

int CPU::opcodeCBEC() { SET(H, 5); return 8; }

int CPU::opcodeCBED() { SET(L, 5); return 8; }

int CPU::opcodeCBEE() { SET(HL, 5); return 16; }

int CPU::opcodeCBEF() { SET(A, 5); return 8; }


int CPU::opcodeCBF0() { SET(B, 6); return 8; }

int CPU::opcodeCBF1() { SET(C, 6); return 8; }

int CPU::opcodeCBF2() { SET(D, 6); return 8; }

int CPU::opcodeCBF3() { SET(E, 6); return 8; }

int CPU::opcodeCBF4() { SET(H, 6); return 8; }

int CPU::opcodeCBF5() { SET(L, 6); return 8; }

int CPU::opcodeCBF6() { SET(HL, 6); return 16; }

int CPU::opcodeCBF7() { SET(A, 6); return 8; }

int CPU::opcodeCBF8() { SET(B, 7); return 8; }

int CPU::opcodeCBF9() { SET(C, 7); return 8; }

int CPU::opcodeCBFA() { SET(D, 7); return 8; }

int CPU::opcodeCBFB() { SET(E, 7); return 8; }

int CPU::opcodeCBFC() { SET(H, 7); return 8; }

int CPU::opcodeCBFD() { SET(L, 7); return 8; }

int CPU::opcodeCBFE() { SET(HL, 7); return 16; }

int CPU::opcodeCBFF() { SET(A, 7); return 8; }

// Assign function pointers

const Opcode CPU::opcodes[NB_OPCODES] =
{
	&CPU::opcode00,
	&CPU::opcode01,
	&CPU::opcode02,
	&CPU::opcode03,
	&CPU::opcode04,
	&CPU::opcode05,
	&CPU::opcode06,
	&CPU::opcode07,
	&CPU::opcode08,
	&CPU::opcode09,
	&CPU::opcode0A,
	&CPU::opcode0B,
	&CPU::opcode0C,
	&CPU::opcode0D,
	&CPU::opcode0E,
	&CPU::opcode0F,

	&CPU::opcode10,
	&CPU::opcode11,
	&CPU::opcode12,
	&CPU::opcode13,
	&CPU::opcode14,
	&CPU::opcode15,
	&CPU::opcode16,
	&CPU::opcode17,
	&CPU::opcode18,
	&CPU::opcode19,
	&CPU::opcode1A,
	&CPU::opcode1B,
	&CPU::opcode1C,
	&CPU::opcode1D,
	&CPU::opcode1E,
	&CPU::opcode1F,

	&CPU::opcode20,
	&CPU::opcode21,
	&CPU::opcode22,
	&CPU::opcode23,
	&CPU::opcode24,
	&CPU::opcode25,
	&CPU::opcode26,
	&CPU::opcode27,
	&CPU::opcode28,
	&CPU::opcode29,
	&CPU::opcode2A,
	&CPU::opcode2B,
	&CPU::opcode2C,
	&CPU::opcode2D,
	&CPU::opcode2E,
	&CPU::opcode2F,

	&CPU::opcode30,
	&CPU::opcode31,
	&CPU::opcode32,
	&CPU::opcode33,
	&CPU::opcode34,
	&CPU::opcode35,
	&CPU::opcode36,
	&CPU::opcode37,
	&CPU::opcode38,
	&CPU::opcode39,
	&CPU::opcode3A,
	&CPU::opcode3B,
	&CPU::opcode3C,
	&CPU::opcode3D,
	&CPU::opcode3E,
	&CPU::opcode3F,

	&CPU::opcode40,
	&CPU::opcode41,
	&CPU::opcode42,
	&CPU::opcode43,
	&CPU::opcode44,
	&CPU::opcode45,
	&CPU::opcode46,
	&CPU::opcode47,
	&CPU::opcode48,
	&CPU::opcode49,
	&CPU::opcode4A,
	&CPU::opcode4B,
	&CPU::opcode4C,
	&CPU::opcode4D,
	&CPU::opcode4E,
	&CPU::opcode4F,

	&CPU::opcode50,
	&CPU::opcode51,
	&CPU::opcode52,
	&CPU::opcode53,
	&CPU::opcode54,
	&CPU::opcode55,
	&CPU::opcode56,
	&CPU::opcode57,
	&CPU::opcode58,
	&CPU::opcode59,
	&CPU::opcode5A,
	&CPU::opcode5B,
	&CPU::opcode5C,
	&CPU::opcode5D,
	&CPU::opcode5E,
	&CPU::opcode5F,

	&CPU::opcode60,
	&CPU::opcode61,
	&CPU::opcode62,
	&CPU::opcode63,
	&CPU::opcode64,
	&CPU::opcode65,
	&CPU::opcode66,
	&CPU::opcode67,
	&CPU::opcode68,
	&CPU::opcode69,
	&CPU::opcode6A,
	&CPU::opcode6B,
	&CPU::opcode6C,
	&CPU::opcode6D,
	&CPU::opcode6E,
	&CPU::opcode6F,

	&CPU::opcode70,
	&CPU::opcode71,
	&CPU::opcode72,
	&CPU::opcode73,
	&CPU::opcode74,
	&CPU::opcode75,
	&CPU::opcode76,
	&CPU::opcode77,
	&CPU::opcode78,
	&CPU::opcode79,
	&CPU::opcode7A,
	&CPU::opcode7B,
	&CPU::opcode7C,
	&CPU::opcode7D,
	&CPU::opcode7E,
	&CPU::opcode7F,

	&CPU::opcode80,
	&CPU::opcode81,
	&CPU::opcode82,
	&CPU::opcode83,
	&CPU::opcode84,
	&CPU::opcode85,
	&CPU::opcode86,
	&CPU::opcode87,
	&CPU::opcode88,
	&CPU::opcode89,
	&CPU::opcode8A,
	&CPU::opcode8B,
	&CPU::opcode8C,
	&CPU::opcode8D,
	&CPU::opcode8E,
	&CPU::opcode8F,

	&CPU::opcode90,
	&CPU::opcode91,
	&CPU::opcode92,
	&CPU::opcode93,
	&CPU::opcode94,
	&CPU::opcode95,
	&CPU::opcode96,
	&CPU::opcode97,
	&CPU::opcode98,
	&CPU::opcode99,
	&CPU::opcode9A,
	&CPU::opcode9B,
	&CPU::opcode9C,
	&CPU::opcode9D,
	&CPU::opcode9E,
	&CPU::opcode9F,

	&CPU::opcodeA0,
	&CPU::opcodeA1,
	&CPU::opcodeA2,
	&CPU::opcodeA3,
	&CPU::opcodeA4,
	&CPU::opcodeA5,
	&CPU::opcodeA6,
	&CPU::opcodeA7,
	&CPU::opcodeA8,
	&CPU::opcodeA9,
	&CPU::opcodeAA,
	&CPU::opcodeAB,
	&CPU::opcodeAC,
	&CPU::opcodeAD,
	&CPU::opcodeAE,
	&CPU::opcodeAF,

	&CPU::opcodeB0,
	&CPU::opcodeB1,
	&CPU::opcodeB2,
	&CPU::opcodeB3,
	&CPU::opcodeB4,
	&CPU::opcodeB5,
	&CPU::opcodeB6,
	&CPU::opcodeB7,
	&CPU::opcodeB8,
	&CPU::opcodeB9,
	&CPU::opcodeBA,
	&CPU::opcodeBB,
	&CPU::opcodeBC,
	&CPU::opcodeBD,
	&CPU::opcodeBE,
	&CPU::opcodeBF,

	&CPU::opcodeC0,
	&CPU::opcodeC1,
	&CPU::opcodeC2,
	&CPU::opcodeC3,
	&CPU::opcodeC4,
	&CPU::opcodeC5,
	&CPU::opcodeC6,
	&CPU::opcodeC7,
	&CPU::opcodeC8,
	&CPU::opcodeC9,
	&CPU::opcodeCA,
	&CPU::opcodeCB,
	&CPU::opcodeCC,
	&CPU::opcodeCD,
	&CPU::opcodeCE,
	&CPU::opcodeCF,

	&CPU::opcodeD0,
	&CPU::opcodeD1,
	&CPU::opcodeD2,
	&CPU::opcodeD3,
	&CPU::opcodeD4,
	&CPU::opcodeD5,
	&CPU::opcodeD6,
	&CPU::opcodeD7,
	&CPU::opcodeD8,
	&CPU::opcodeD9,
	&CPU::opcodeDA,
	&CPU::opcodeDB,
	&CPU::opcodeDC,
	&CPU::opcodeDD,
	&CPU::opcodeDE,
	&CPU::opcodeDF,

	&CPU::opcodeE0,
	&CPU::opcodeE1,
	&CPU::opcodeE2,
	&CPU::opcodeE3,
	&CPU::opcodeE4,
	&CPU::opcodeE5,
	&CPU::opcodeE6,
	&CPU::opcodeE7,
	&CPU::opcodeE8,
	&CPU::opcodeE9,
	&CPU::opcodeEA,
	&CPU::opcodeEB,
	&CPU::opcodeEC,
	&CPU::opcodeED,
	&CPU::opcodeEE,
	&CPU::opcodeEF,

	&CPU::opcodeF0,
	&CPU::opcodeF1,
	&CPU::opcodeF2,
	&CPU::opcodeF3,
	&CPU::opcodeF4,
	&CPU::opcodeF5,
	&CPU::opcodeF6,
	&CPU::opcodeF7,
	&CPU::opcodeF8,
	&CPU::opcodeF9,
	&CPU::opcodeFA,
	&CPU::opcodeFB,
	&CPU::opcodeFC,
	&CPU::opcodeFD,
	&CPU::opcodeFE,
	&CPU::opcodeFF,


	//Prefix CB


	&CPU::opcodeCB00,
	&CPU::opcodeCB01,
	&CPU::opcodeCB02,
	&CPU::opcodeCB03,
	&CPU::opcodeCB04,
	&CPU::opcodeCB05,
	&CPU::opcodeCB06,
	&CPU::opcodeCB07,
	&CPU::opcodeCB08,
	&CPU::opcodeCB09,
	&CPU::opcodeCB0A,
	&CPU::opcodeCB0B,
	&CPU::opcodeCB0C,
	&CPU::opcodeCB0D,
	&CPU::opcodeCB0E,
	&CPU::opcodeCB0F,

	&CPU::opcodeCB10,
	&CPU::opcodeCB11,
	&CPU::opcodeCB12,
	&CPU::opcodeCB13,
	&CPU::opcodeCB14,
	&CPU::opcodeCB15,
	&CPU::opcodeCB16,
	&CPU::opcodeCB17,
	&CPU::opcodeCB18,
	&CPU::opcodeCB19,
	&CPU::opcodeCB1A,
	&CPU::opcodeCB1B,
	&CPU::opcodeCB1C,
	&CPU::opcodeCB1D,
	&CPU::opcodeCB1E,
	&CPU::opcodeCB1F,

	&CPU::opcodeCB20,
	&CPU::opcodeCB21,
	&CPU::opcodeCB22,
	&CPU::opcodeCB23,
	&CPU::opcodeCB24,
	&CPU::opcodeCB25,
	&CPU::opcodeCB26,
	&CPU::opcodeCB27,
	&CPU::opcodeCB28,
	&CPU::opcodeCB29,
	&CPU::opcodeCB2A,
	&CPU::opcodeCB2B,
	&CPU::opcodeCB2C,
	&CPU::opcodeCB2D,
	&CPU::opcodeCB2E,
	&CPU::opcodeCB2F,

	&CPU::opcodeCB30,
	&CPU::opcodeCB31,
	&CPU::opcodeCB32,
	&CPU::opcodeCB33,
	&CPU::opcodeCB34,
	&CPU::opcodeCB35,
	&CPU::opcodeCB36,
	&CPU::opcodeCB37,
	&CPU::opcodeCB38,
	&CPU::opcodeCB39,
	&CPU::opcodeCB3A,
	&CPU::opcodeCB3B,
	&CPU::opcodeCB3C,
	&CPU::opcodeCB3D,
	&CPU::opcodeCB3E,
	&CPU::opcodeCB3F,

	&CPU::opcodeCB40,
	&CPU::opcodeCB41,
	&CPU::opcodeCB42,
	&CPU::opcodeCB43,
	&CPU::opcodeCB44,
	&CPU::opcodeCB45,
	&CPU::opcodeCB46,
	&CPU::opcodeCB47,
	&CPU::opcodeCB48,
	&CPU::opcodeCB49,
	&CPU::opcodeCB4A,
	&CPU::opcodeCB4B,
	&CPU::opcodeCB4C,
	&CPU::opcodeCB4D,
	&CPU::opcodeCB4E,
	&CPU::opcodeCB4F,

	&CPU::opcodeCB50,
	&CPU::opcodeCB51,
	&CPU::opcodeCB52,
	&CPU::opcodeCB53,
	&CPU::opcodeCB54,
	&CPU::opcodeCB55,
	&CPU::opcodeCB56,
	&CPU::opcodeCB57,
	&CPU::opcodeCB58,
	&CPU::opcodeCB59,
	&CPU::opcodeCB5A,
	&CPU::opcodeCB5B,
	&CPU::opcodeCB5C,
	&CPU::opcodeCB5D,
	&CPU::opcodeCB5E,
	&CPU::opcodeCB5F,

	&CPU::opcodeCB60,
	&CPU::opcodeCB61,
	&CPU::opcodeCB62,
	&CPU::opcodeCB63,
	&CPU::opcodeCB64,
	&CPU::opcodeCB65,
	&CPU::opcodeCB66,
	&CPU::opcodeCB67,
	&CPU::opcodeCB68,
	&CPU::opcodeCB69,
	&CPU::opcodeCB6A,
	&CPU::opcodeCB6B,
	&CPU::opcodeCB6C,
	&CPU::opcodeCB6D,
	&CPU::opcodeCB6E,
	&CPU::opcodeCB6F,

	&CPU::opcodeCB70,
	&CPU::opcodeCB71,
	&CPU::opcodeCB72,
	&CPU::opcodeCB73,
	&CPU::opcodeCB74,
	&CPU::opcodeCB75,
	&CPU::opcodeCB76,
	&CPU::opcodeCB77,
	&CPU::opcodeCB78,
	&CPU::opcodeCB79,
	&CPU::opcodeCB7A,
	&CPU::opcodeCB7B,
	&CPU::opcodeCB7C,
	&CPU::opcodeCB7D,
	&CPU::opcodeCB7E,
	&CPU::opcodeCB7F,

	&CPU::opcodeCB80,
	&CPU::opcodeCB81,
	&CPU::opcodeCB82,
	&CPU::opcodeCB83,
	&CPU::opcodeCB84,
	&CPU::opcodeCB85,
	&CPU::opcodeCB86,
	&CPU::opcodeCB87,
	&CPU::opcodeCB88,
	&CPU::opcodeCB89,
	&CPU::opcodeCB8A,
	&CPU::opcodeCB8B,
	&CPU::opcodeCB8C,
	&CPU::opcodeCB8D,
	&CPU::opcodeCB8E,
	&CPU::opcodeCB8F,

	&CPU::opcodeCB90,
	&CPU::opcodeCB91,
	&CPU::opcodeCB92,
	&CPU::opcodeCB93,
	&CPU::opcodeCB94,
	&CPU::opcodeCB95,
	&CPU::opcodeCB96,
	&CPU::opcodeCB97,
	&CPU::opcodeCB98,
	&CPU::opcodeCB99,
	&CPU::opcodeCB9A,
	&CPU::opcodeCB9B,
	&CPU::opcodeCB9C,
	&CPU::opcodeCB9D,
	&CPU::opcodeCB9E,
	&CPU::opcodeCB9F,

	&CPU::opcodeCBA0,
	&CPU::opcodeCBA1,
	&CPU::opcodeCBA2,
	&CPU::opcodeCBA3,
	&CPU::opcodeCBA4,
	&CPU::opcodeCBA5,
	&CPU::opcodeCBA6,
	&CPU::opcodeCBA7,
	&CPU::opcodeCBA8,
	&CPU::opcodeCBA9,
	&CPU::opcodeCBAA,
	&CPU::opcodeCBAB,
	&CPU::opcodeCBAC,
	&CPU::opcodeCBAD,
	&CPU::opcodeCBAE,
	&CPU::opcodeCBAF,

	&CPU::opcodeCBB0,
	&CPU::opcodeCBB1,
	&CPU::opcodeCBB2,
	&CPU::opcodeCBB3,
	&CPU::opcodeCBB4,
	&CPU::opcodeCBB5,
	&CPU::opcodeCBB6,
	&CPU::opcodeCBB7,
	&CPU::opcodeCBB8,
	&CPU::opcodeCBB9,
	&CPU::opcodeCBBA,
	&CPU::opcodeCBBB,
	&CPU::opcodeCBBC,
	&CPU::opcodeCBBD,
	&CPU::opcodeCBBE,
	&CPU::opcodeCBBF,

	&CPU::opcodeCBC0,
	&CPU::opcodeCBC1,
	&CPU::opcodeCBC2,
	&CPU::opcodeCBC3,
	&CPU::opcodeCBC4,
	&CPU::opcodeCBC5,
	&CPU::opcodeCBC6,
	&CPU::opcodeCBC7,
	&CPU::opcodeCBC8,
	&CPU::opcodeCBC9,
	&CPU::opcodeCBCA,
	&CPU::opcodeCBCB,
	&CPU::opcodeCBCC,
	&CPU::opcodeCBCD,
	&CPU::opcodeCBCE,
	&CPU::opcodeCBCF,

	&CPU::opcodeCBD0,
	&CPU::opcodeCBD1,
	&CPU::opcodeCBD2,
	&CPU::opcodeCBD3,
	&CPU::opcodeCBD4,
	&CPU::opcodeCBD5,
	&CPU::opcodeCBD6,
	&CPU::opcodeCBD7,
	&CPU::opcodeCBD8,
	&CPU::opcodeCBD9,
	&CPU::opcodeCBDA,
	&CPU::opcodeCBDB,
	&CPU::opcodeCBDC,
	&CPU::opcodeCBDD,
	&CPU::opcodeCBDE,
	&CPU::opcodeCBDF,

	&CPU::opcodeCBE0,
	&CPU::opcodeCBE1,
	&CPU::opcodeCBE2,
	&CPU::opcodeCBE3,
	&CPU::opcodeCBE4,
	&CPU::opcodeCBE5,
	&CPU::opcodeCBE6,
	&CPU::opcodeCBE7,
	&CPU::opcodeCBE8,
	&CPU::opcodeCBE9,
	&CPU::opcodeCBEA,
	&CPU::opcodeCBEB,
	&CPU::opcodeCBEC,
	&CPU::opcodeCBED,
	&CPU::opcodeCBEE,
	&CPU::opcodeCBEF,

	&CPU::opcodeCBF0,
	&CPU::opcodeCBF1,
	&CPU::opcodeCBF2,
	&CPU::opcodeCBF3,
	&CPU::opcodeCBF4,
	&CPU::opcodeCBF5,
	&CPU::opcodeCBF6,
	&CPU::opcodeCBF7,
	&CPU::opcodeCBF8,
	&CPU::opcodeCBF9,
	&CPU::opcodeCBFA,
	&CPU::opcodeCBFB,
	&CPU::opcodeCBFC,
	&CPU::opcodeCBFD,
	&CPU::opcodeCBFE,
	&CPU::opcodeCBFF
};