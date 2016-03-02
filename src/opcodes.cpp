
void CPU::XOR(u8 src)
{
	A = A ^ src;
	F = 0;
	if (A == 0) SET_FLAG(FLAG_Z);
}

void CPU::LD_16bit(u16& dst)
{
	dst = m_MMU->read16(PC);
	PC += 2;
}

void CPU::LD_8imm(u8& dst)
{
	dst = m_MMU->read8(PC++);
}

void CPU::LD_8_ind(u16 addr, u8 src)
{
	m_MMU->write8(addr, src);
}

void CPU::LD_8reg(u8& dst, u8 src)
{
	dst = src;
}

void CPU::LDI()
{
	A = m_MMU->read8(HL);
	HL++;
	PC++;
}

void CPU::LDI_ind()
{
	m_MMU->write8(HL, A);
	HL++;
	PC++;
}

void CPU::LDD()
{
	A = m_MMU->read8(HL);
	HL--;
	PC++;
}

void CPU::LDD_ind()
{
	m_MMU->write8(HL, A);
	HL--;
	PC++;
}

int CPU::opcodeUnknown()
{
	return 0;
}

// Opcodes implementation

int CPU::opcode00()
{
	//NOP
	return 4;
}

int CPU::opcode01() { LD_16bit(BC); return 12; }

int CPU::opcode02() { LD_8_ind(BC, A); return 8; }

int CPU::opcode03()
{
	return opcodeUnknown();
}

int CPU::opcode04()
{
	return opcodeUnknown();
}

int CPU::opcode05()
{
	return opcodeUnknown();
}

int CPU::opcode06() { LD_8imm(B); return 8; }

int CPU::opcode07()
{
	return opcodeUnknown();
}

int CPU::opcode08()
{
	return opcodeUnknown();
}

int CPU::opcode09()
{
	return opcodeUnknown();
}

int CPU::opcode0A() { LD_8reg(A, m_MMU->read8(BC)); PC++; return 8; }

int CPU::opcode0B()
{
	return opcodeUnknown();
}

int CPU::opcode0C()
{
	return opcodeUnknown();
}

int CPU::opcode0D()
{
	return opcodeUnknown();
}

int CPU::opcode0E() { LD_8imm(C); return 8; }

int CPU::opcode0F()
{
	return opcodeUnknown();
}


int CPU::opcode10()
{
	return opcodeUnknown();
}

int CPU::opcode11() { LD_16bit(DE); return 12; }

int CPU::opcode12() { LD_8_ind(DE, A); return 8; }

int CPU::opcode13()
{
	return opcodeUnknown();
}

int CPU::opcode14()
{
	return opcodeUnknown();
}

int CPU::opcode15()
{
	return opcodeUnknown();
}

int CPU::opcode16() { LD_8imm(D); return 8; }

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

int CPU::opcode1A() { LD_8reg(A, m_MMU->read8(DE)); PC++; return 8; }

int CPU::opcode1B()
{
	return opcodeUnknown();
}

int CPU::opcode1C()
{
	return opcodeUnknown();
}

int CPU::opcode1D()
{
	return opcodeUnknown();
}

int CPU::opcode1E() { LD_8imm(E); return 8; }

int CPU::opcode1F()
{
	return opcodeUnknown();
}


int CPU::opcode20()
{
	return opcodeUnknown();
}

int CPU::opcode21() { LD_16bit(HL); return 12; }

int CPU::opcode22() { LDI_ind(); return 8; }

int CPU::opcode23()
{
	return opcodeUnknown();
}

int CPU::opcode24()
{
	return opcodeUnknown();
}

int CPU::opcode25()
{
	return opcodeUnknown();
}

int CPU::opcode26() { LD_8imm(H); return 8; }

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

int CPU::opcode2A() { LDI(); return 8; }

int CPU::opcode2B()
{
	return opcodeUnknown();
}

int CPU::opcode2C()
{
	return opcodeUnknown();
}

int CPU::opcode2D()
{
	return opcodeUnknown();
}

int CPU::opcode2E() { LD_8imm(L); return 8; }

int CPU::opcode2F()
{
	return opcodeUnknown();
}


int CPU::opcode30()
{
	return opcodeUnknown();
}

int CPU::opcode31() { LD_16bit(SP); return 12; }

int CPU::opcode32() { LDD_ind(); return 8; }

int CPU::opcode33()
{
	return opcodeUnknown();
}

int CPU::opcode34()
{
	return opcodeUnknown();
}

int CPU::opcode35()
{
	return opcodeUnknown();
}

int CPU::opcode36() { LD_8_ind(HL, m_MMU->read8(PC++)); return 12; }

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

int CPU::opcode3A() { LDD(); return 8; }

int CPU::opcode3B()
{
	return opcodeUnknown();
}

int CPU::opcode3C()
{
	return opcodeUnknown();
}

int CPU::opcode3D()
{
	return opcodeUnknown();
}

int CPU::opcode3E() { LD_8imm(A); return 8; }

int CPU::opcode3F()
{
	return opcodeUnknown();
}


int CPU::opcode40() { LD_8reg(B, B); return 4; }

int CPU::opcode41() { LD_8reg(B, C); return 4; }

int CPU::opcode42() { LD_8reg(B, D); return 4; }

int CPU::opcode43() { LD_8reg(B, E); return 4; }

int CPU::opcode44() { LD_8reg(B, H); return 4; }

int CPU::opcode45() { LD_8reg(B, L); return 4; }

int CPU::opcode46() { LD_8reg(B, m_MMU->read8(HL)); PC++; return 8; }

int CPU::opcode47() { LD_8reg(B, A); return 4; }

int CPU::opcode48() { LD_8reg(C, B); return 4; }

int CPU::opcode49() { LD_8reg(C, C); return 4; }

int CPU::opcode4A() { LD_8reg(C, D); return 4; }

int CPU::opcode4B() { LD_8reg(C, E); return 4; }

int CPU::opcode4C() { LD_8reg(C, H); return 4; }

int CPU::opcode4D() { LD_8reg(C, L); return 4; }

int CPU::opcode4E() { LD_8reg(C, m_MMU->read8(HL)); PC++; return 8; }

int CPU::opcode4F() { LD_8reg(C, A); return 4; }


int CPU::opcode50() { LD_8reg(D, B); return 4; }

int CPU::opcode51() { LD_8reg(D, C); return 4; }

int CPU::opcode52() { LD_8reg(D, D); return 4; }

int CPU::opcode53() { LD_8reg(D, E); return 4; }

int CPU::opcode54() { LD_8reg(D, H); return 4; }

int CPU::opcode55() { LD_8reg(D, L); return 4; }

int CPU::opcode56() { LD_8reg(D, m_MMU->read8(HL)); PC++; return 8; }

int CPU::opcode57() { LD_8reg(D, A); return 4; }

int CPU::opcode58() { LD_8reg(E, B); return 4; }

int CPU::opcode59() { LD_8reg(E, C); return 4; }

int CPU::opcode5A() { LD_8reg(E, D); return 4; }

int CPU::opcode5B() { LD_8reg(E, E); return 4; }

int CPU::opcode5C() { LD_8reg(E, H); return 4; }

int CPU::opcode5D() { LD_8reg(E, L); return 4; }

int CPU::opcode5E() { LD_8reg(E, m_MMU->read8(HL)); PC++; return 8; }

int CPU::opcode5F() { LD_8reg(E, A); return 4; }


int CPU::opcode60() { LD_8reg(H, B); return 4; }

int CPU::opcode61() { LD_8reg(H, C); return 4; }

int CPU::opcode62() { LD_8reg(H, D); return 4; }

int CPU::opcode63() { LD_8reg(H, E); return 4; }

int CPU::opcode64() { LD_8reg(H, H); return 4; }

int CPU::opcode65() { LD_8reg(H, L); return 4; }

int CPU::opcode66() { LD_8reg(H, m_MMU->read8(HL)); PC++; return 8; }

int CPU::opcode67() { LD_8reg(H, A); return 4; }

int CPU::opcode68() { LD_8reg(L, B); return 4; }

int CPU::opcode69() { LD_8reg(L, C); return 4; }

int CPU::opcode6A() { LD_8reg(L, D); return 4; }

int CPU::opcode6B() { LD_8reg(L, E); return 4; }

int CPU::opcode6C() { LD_8reg(L, H); return 4; }

int CPU::opcode6D() { LD_8reg(L, L); return 4; }

int CPU::opcode6E() { LD_8reg(L, m_MMU->read8(HL)); PC++; return 8; }

int CPU::opcode6F() { LD_8reg(L, A); return 4; }


int CPU::opcode70() { LD_8_ind(HL, B); return 8; }

int CPU::opcode71() { LD_8_ind(HL, C); return 8; }

int CPU::opcode72() { LD_8_ind(HL, D); return 8; }

int CPU::opcode73() { LD_8_ind(HL, E); return 8; }

int CPU::opcode74() { LD_8_ind(HL, H); return 8; }

int CPU::opcode75() { LD_8_ind(HL, L); return 8; }

int CPU::opcode76()
{
	return opcodeUnknown();
}

int CPU::opcode77() { LD_8_ind(HL, A); return 8; }

int CPU::opcode78() { LD_8reg(A, B); return 4; }

int CPU::opcode79() { LD_8reg(A, C); return 4; }

int CPU::opcode7A() { LD_8reg(A, D); return 4; }

int CPU::opcode7B() { LD_8reg(A, E); return 4; }

int CPU::opcode7C() { LD_8reg(A, H); return 4; }

int CPU::opcode7D() { LD_8reg(A, L); return 4; }

int CPU::opcode7E() { LD_8reg(A, m_MMU->read8(HL)); PC++; return 8; }

int CPU::opcode7F() { LD_8reg(A, A); return 4; }


int CPU::opcode80()
{
	return opcodeUnknown();
}

int CPU::opcode81()
{
	return opcodeUnknown();
}

int CPU::opcode82()
{
	return opcodeUnknown();
}

int CPU::opcode83()
{
	return opcodeUnknown();
}

int CPU::opcode84()
{
	return opcodeUnknown();
}

int CPU::opcode85()
{
	return opcodeUnknown();
}

int CPU::opcode86()
{
	return opcodeUnknown();
}

int CPU::opcode87()
{
	return opcodeUnknown();
}

int CPU::opcode88()
{
	return opcodeUnknown();
}

int CPU::opcode89()
{
	return opcodeUnknown();
}

int CPU::opcode8A()
{
	return opcodeUnknown();
}

int CPU::opcode8B()
{
	return opcodeUnknown();
}

int CPU::opcode8C()
{
	return opcodeUnknown();
}

int CPU::opcode8D()
{
	return opcodeUnknown();
}

int CPU::opcode8E()
{
	return opcodeUnknown();
}

int CPU::opcode8F()
{
	return opcodeUnknown();
}


int CPU::opcode90()
{
	return opcodeUnknown();
}

int CPU::opcode91()
{
	return opcodeUnknown();
}

int CPU::opcode92()
{
	return opcodeUnknown();
}

int CPU::opcode93()
{
	return opcodeUnknown();
}

int CPU::opcode94()
{
	return opcodeUnknown();
}

int CPU::opcode95()
{
	return opcodeUnknown();
}

int CPU::opcode96()
{
	return opcodeUnknown();
}

int CPU::opcode97()
{
	return opcodeUnknown();
}

int CPU::opcode98()
{
	return opcodeUnknown();
}

int CPU::opcode99()
{
	return opcodeUnknown();
}

int CPU::opcode9A()
{
	return opcodeUnknown();
}

int CPU::opcode9B()
{
	return opcodeUnknown();
}

int CPU::opcode9C()
{
	return opcodeUnknown();
}

int CPU::opcode9D()
{
	return opcodeUnknown();
}

int CPU::opcode9E()
{
	return opcodeUnknown();
}

int CPU::opcode9F()
{
	return opcodeUnknown();
}


int CPU::opcodeA0()
{
	return opcodeUnknown();
}

int CPU::opcodeA1()
{
	return opcodeUnknown();
}

int CPU::opcodeA2()
{
	return opcodeUnknown();
}

int CPU::opcodeA3()
{
	return opcodeUnknown();
}

int CPU::opcodeA4()
{
	return opcodeUnknown();
}

int CPU::opcodeA5()
{
	return opcodeUnknown();
}

int CPU::opcodeA6()
{
	return opcodeUnknown();
}

int CPU::opcodeA7()
{
	return opcodeUnknown();
}

int CPU::opcodeA8() { XOR(B); return 4; }

int CPU::opcodeA9() { XOR(C); return 4; }

int CPU::opcodeAA() { XOR(D); return 4; }

int CPU::opcodeAB() { XOR(E); return 4; }

int CPU::opcodeAC() { XOR(H); return 4; }

int CPU::opcodeAD() { XOR(L); return 4; }

int CPU::opcodeAE() { XOR(m_MMU->read8(HL)); PC++; return 8; }

int CPU::opcodeAF() { XOR(A); return 4; }


int CPU::opcodeB0()
{
	return opcodeUnknown();
}

int CPU::opcodeB1()
{
	return opcodeUnknown();
}

int CPU::opcodeB2()
{
	return opcodeUnknown();
}

int CPU::opcodeB3()
{
	return opcodeUnknown();
}

int CPU::opcodeB4()
{
	return opcodeUnknown();
}

int CPU::opcodeB5()
{
	return opcodeUnknown();
}

int CPU::opcodeB6()
{
	return opcodeUnknown();
}

int CPU::opcodeB7()
{
	return opcodeUnknown();
}

int CPU::opcodeB8()
{
	return opcodeUnknown();
}

int CPU::opcodeB9()
{
	return opcodeUnknown();
}

int CPU::opcodeBA()
{
	return opcodeUnknown();
}

int CPU::opcodeBB()
{
	return opcodeUnknown();
}

int CPU::opcodeBC()
{
	return opcodeUnknown();
}

int CPU::opcodeBD()
{
	return opcodeUnknown();
}

int CPU::opcodeBE()
{
	return opcodeUnknown();
}

int CPU::opcodeBF()
{
	return opcodeUnknown();
}


int CPU::opcodeC0()
{
	return opcodeUnknown();
}

int CPU::opcodeC1()
{
	return opcodeUnknown();
}

int CPU::opcodeC2()
{
	return opcodeUnknown();
}

int CPU::opcodeC3()
{
	PC = m_MMU->read16(PC);
	return 16;
}

int CPU::opcodeC4()
{
	return opcodeUnknown();
}

int CPU::opcodeC5()
{
	return opcodeUnknown();
}

int CPU::opcodeC6()
{
	return opcodeUnknown();
}

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

int CPU::opcodeCE()
{
	return opcodeUnknown();
}

int CPU::opcodeCF()
{
	return opcodeUnknown();
}


int CPU::opcodeD0()
{
	return opcodeUnknown();
}

int CPU::opcodeD1()
{
	return opcodeUnknown();
}

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

int CPU::opcodeD5()
{
	return opcodeUnknown();
}

int CPU::opcodeD6()
{
	return opcodeUnknown();
}

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


int CPU::opcodeE0()
{
	u8 offset8 = m_MMU->read8(PC++);
	LD_8_ind(0xFF00 + offset8, A);
	return 12;
}

int CPU::opcodeE1()
{
	return opcodeUnknown();
}

int CPU::opcodeE2() { LD_8_ind(0xFF00 + C, A); return 8; }

int CPU::opcodeE3()
{
	return opcodeUnknown();
}

int CPU::opcodeE4()
{
	return opcodeUnknown();
}

int CPU::opcodeE5()
{
	return opcodeUnknown();
}

int CPU::opcodeE6()
{
	return opcodeUnknown();
}

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

int CPU::opcodeEA() { LD_8_ind(PC, A); PC += 2; return 16; }

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

int CPU::opcodeEE()
{
	return opcodeUnknown();
}

int CPU::opcodeEF()
{
	return opcodeUnknown();
}


int CPU::opcodeF0()
{
	u8 offset8 = m_MMU->read8(PC++);
	u8 value = m_MMU->read8(0xFF00 + offset8);
	LD_8reg(A, value);
	return 12;
}

int CPU::opcodeF1()
{
	return opcodeUnknown();
}

int CPU::opcodeF2() { LD_8reg(A, m_MMU->read8(0xFF00 + C)); return 8; }

int CPU::opcodeF3()
{
	return opcodeUnknown();
}

int CPU::opcodeF4()
{
	return opcodeUnknown();
}

int CPU::opcodeF5()
{
	return opcodeUnknown();
}

int CPU::opcodeF6()
{
	return opcodeUnknown();
}

int CPU::opcodeF7()
{
	return opcodeUnknown();
}

int CPU::opcodeF8()
{
	return opcodeUnknown();
}

int CPU::opcodeF9()
{
	return opcodeUnknown();
}

int CPU::opcodeFA()
{ 
	u16 addr = m_MMU->read16(PC);
	PC += 2;
	A = m_MMU->read8(addr);
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

int CPU::opcodeFE()
{
	return opcodeUnknown();
}

int CPU::opcodeFF()
{
	return opcodeUnknown();
}


//CB Prefix


int CPU::opcodeCB00()
{
	return opcodeUnknown();
}

int CPU::opcodeCB01()
{
	return opcodeUnknown();
}

int CPU::opcodeCB02()
{
	return opcodeUnknown();
}

int CPU::opcodeCB03()
{
	return opcodeUnknown();
}

int CPU::opcodeCB04()
{
	return opcodeUnknown();
}

int CPU::opcodeCB05()
{
	return opcodeUnknown();
}

int CPU::opcodeCB06()
{
	return opcodeUnknown();
}

int CPU::opcodeCB07()
{
	return opcodeUnknown();
}

int CPU::opcodeCB08()
{
	return opcodeUnknown();
}

int CPU::opcodeCB09()
{
	return opcodeUnknown();
}

int CPU::opcodeCB0A()
{
	return opcodeUnknown();
}

int CPU::opcodeCB0B()
{
	return opcodeUnknown();
}

int CPU::opcodeCB0C()
{
	return opcodeUnknown();
}

int CPU::opcodeCB0D()
{
	return opcodeUnknown();
}

int CPU::opcodeCB0E()
{
	return opcodeUnknown();
}

int CPU::opcodeCB0F()
{
	return opcodeUnknown();
}


int CPU::opcodeCB10()
{
	return opcodeUnknown();
}

int CPU::opcodeCB11()
{
	return opcodeUnknown();
}

int CPU::opcodeCB12()
{
	return opcodeUnknown();
}

int CPU::opcodeCB13()
{
	return opcodeUnknown();
}

int CPU::opcodeCB14()
{
	return opcodeUnknown();
}

int CPU::opcodeCB15()
{
	return opcodeUnknown();
}

int CPU::opcodeCB16()
{
	return opcodeUnknown();
}

int CPU::opcodeCB17()
{
	return opcodeUnknown();
}

int CPU::opcodeCB18()
{
	return opcodeUnknown();
}

int CPU::opcodeCB19()
{
	return opcodeUnknown();
}

int CPU::opcodeCB1A()
{
	return opcodeUnknown();
}

int CPU::opcodeCB1B()
{
	return opcodeUnknown();
}

int CPU::opcodeCB1C()
{
	return opcodeUnknown();
}

int CPU::opcodeCB1D()
{
	return opcodeUnknown();
}

int CPU::opcodeCB1E()
{
	return opcodeUnknown();
}

int CPU::opcodeCB1F()
{
	return opcodeUnknown();
}


int CPU::opcodeCB20()
{
	return opcodeUnknown();
}

int CPU::opcodeCB21()
{
	return opcodeUnknown();
}

int CPU::opcodeCB22()
{
	return opcodeUnknown();
}

int CPU::opcodeCB23()
{
	return opcodeUnknown();
}

int CPU::opcodeCB24()
{
	return opcodeUnknown();
}

int CPU::opcodeCB25()
{
	return opcodeUnknown();
}

int CPU::opcodeCB26()
{
	return opcodeUnknown();
}

int CPU::opcodeCB27()
{
	return opcodeUnknown();
}

int CPU::opcodeCB28()
{
	return opcodeUnknown();
}

int CPU::opcodeCB29()
{
	return opcodeUnknown();
}

int CPU::opcodeCB2A()
{
	return opcodeUnknown();
}

int CPU::opcodeCB2B()
{
	return opcodeUnknown();
}

int CPU::opcodeCB2C()
{
	return opcodeUnknown();
}

int CPU::opcodeCB2D()
{
	return opcodeUnknown();
}

int CPU::opcodeCB2E()
{
	return opcodeUnknown();
}

int CPU::opcodeCB2F()
{
	return opcodeUnknown();
}


int CPU::opcodeCB30()
{
	return opcodeUnknown();
}

int CPU::opcodeCB31()
{
	return opcodeUnknown();
}

int CPU::opcodeCB32()
{
	return opcodeUnknown();
}

int CPU::opcodeCB33()
{
	return opcodeUnknown();
}

int CPU::opcodeCB34()
{
	return opcodeUnknown();
}

int CPU::opcodeCB35()
{
	return opcodeUnknown();
}

int CPU::opcodeCB36()
{
	return opcodeUnknown();
}

int CPU::opcodeCB37()
{
	return opcodeUnknown();
}

int CPU::opcodeCB38()
{
	return opcodeUnknown();
}

int CPU::opcodeCB39()
{
	return opcodeUnknown();
}

int CPU::opcodeCB3A()
{
	return opcodeUnknown();
}

int CPU::opcodeCB3B()
{
	return opcodeUnknown();
}

int CPU::opcodeCB3C()
{
	return opcodeUnknown();
}

int CPU::opcodeCB3D()
{
	return opcodeUnknown();
}

int CPU::opcodeCB3E()
{
	return opcodeUnknown();
}

int CPU::opcodeCB3F()
{
	return opcodeUnknown();
}


int CPU::opcodeCB40()
{
	return opcodeUnknown();
}

int CPU::opcodeCB41()
{
	return opcodeUnknown();
}

int CPU::opcodeCB42()
{
	return opcodeUnknown();
}

int CPU::opcodeCB43()
{
	return opcodeUnknown();
}

int CPU::opcodeCB44()
{
	return opcodeUnknown();
}

int CPU::opcodeCB45()
{
	return opcodeUnknown();
}

int CPU::opcodeCB46()
{
	return opcodeUnknown();
}

int CPU::opcodeCB47()
{
	return opcodeUnknown();
}

int CPU::opcodeCB48()
{
	return opcodeUnknown();
}

int CPU::opcodeCB49()
{
	return opcodeUnknown();
}

int CPU::opcodeCB4A()
{
	return opcodeUnknown();
}

int CPU::opcodeCB4B()
{
	return opcodeUnknown();
}

int CPU::opcodeCB4C()
{
	return opcodeUnknown();
}

int CPU::opcodeCB4D()
{
	return opcodeUnknown();
}

int CPU::opcodeCB4E()
{
	return opcodeUnknown();
}

int CPU::opcodeCB4F()
{
	return opcodeUnknown();
}


int CPU::opcodeCB50()
{
	return opcodeUnknown();
}

int CPU::opcodeCB51()
{
	return opcodeUnknown();
}

int CPU::opcodeCB52()
{
	return opcodeUnknown();
}

int CPU::opcodeCB53()
{
	return opcodeUnknown();
}

int CPU::opcodeCB54()
{
	return opcodeUnknown();
}

int CPU::opcodeCB55()
{
	return opcodeUnknown();
}

int CPU::opcodeCB56()
{
	return opcodeUnknown();
}

int CPU::opcodeCB57()
{
	return opcodeUnknown();
}

int CPU::opcodeCB58()
{
	return opcodeUnknown();
}

int CPU::opcodeCB59()
{
	return opcodeUnknown();
}

int CPU::opcodeCB5A()
{
	return opcodeUnknown();
}

int CPU::opcodeCB5B()
{
	return opcodeUnknown();
}

int CPU::opcodeCB5C()
{
	return opcodeUnknown();
}

int CPU::opcodeCB5D()
{
	return opcodeUnknown();
}

int CPU::opcodeCB5E()
{
	return opcodeUnknown();
}

int CPU::opcodeCB5F()
{
	return opcodeUnknown();
}


int CPU::opcodeCB60()
{
	return opcodeUnknown();
}

int CPU::opcodeCB61()
{
	return opcodeUnknown();
}

int CPU::opcodeCB62()
{
	return opcodeUnknown();
}

int CPU::opcodeCB63()
{
	return opcodeUnknown();
}

int CPU::opcodeCB64()
{
	return opcodeUnknown();
}

int CPU::opcodeCB65()
{
	return opcodeUnknown();
}

int CPU::opcodeCB66()
{
	return opcodeUnknown();
}

int CPU::opcodeCB67()
{
	return opcodeUnknown();
}

int CPU::opcodeCB68()
{
	return opcodeUnknown();
}

int CPU::opcodeCB69()
{
	return opcodeUnknown();
}

int CPU::opcodeCB6A()
{
	return opcodeUnknown();
}

int CPU::opcodeCB6B()
{
	return opcodeUnknown();
}

int CPU::opcodeCB6C()
{
	return opcodeUnknown();
}

int CPU::opcodeCB6D()
{
	return opcodeUnknown();
}

int CPU::opcodeCB6E()
{
	return opcodeUnknown();
}

int CPU::opcodeCB6F()
{
	return opcodeUnknown();
}


int CPU::opcodeCB70()
{
	return opcodeUnknown();
}

int CPU::opcodeCB71()
{
	return opcodeUnknown();
}

int CPU::opcodeCB72()
{
	return opcodeUnknown();
}

int CPU::opcodeCB73()
{
	return opcodeUnknown();
}

int CPU::opcodeCB74()
{
	return opcodeUnknown();
}

int CPU::opcodeCB75()
{
	return opcodeUnknown();
}

int CPU::opcodeCB76()
{
	return opcodeUnknown();
}

int CPU::opcodeCB77()
{
	return opcodeUnknown();
}

int CPU::opcodeCB78()
{
	return opcodeUnknown();
}

int CPU::opcodeCB79()
{
	return opcodeUnknown();
}

int CPU::opcodeCB7A()
{
	return opcodeUnknown();
}

int CPU::opcodeCB7B()
{
	return opcodeUnknown();
}

int CPU::opcodeCB7C()
{
	return opcodeUnknown();
}

int CPU::opcodeCB7D()
{
	return opcodeUnknown();
}

int CPU::opcodeCB7E()
{
	return opcodeUnknown();
}

int CPU::opcodeCB7F()
{
	return opcodeUnknown();
}


int CPU::opcodeCB80()
{
	return opcodeUnknown();
}

int CPU::opcodeCB81()
{
	return opcodeUnknown();
}

int CPU::opcodeCB82()
{
	return opcodeUnknown();
}

int CPU::opcodeCB83()
{
	return opcodeUnknown();
}

int CPU::opcodeCB84()
{
	return opcodeUnknown();
}

int CPU::opcodeCB85()
{
	return opcodeUnknown();
}

int CPU::opcodeCB86()
{
	return opcodeUnknown();
}

int CPU::opcodeCB87()
{
	return opcodeUnknown();
}

int CPU::opcodeCB88()
{
	return opcodeUnknown();
}

int CPU::opcodeCB89()
{
	return opcodeUnknown();
}

int CPU::opcodeCB8A()
{
	return opcodeUnknown();
}

int CPU::opcodeCB8B()
{
	return opcodeUnknown();
}

int CPU::opcodeCB8C()
{
	return opcodeUnknown();
}

int CPU::opcodeCB8D()
{
	return opcodeUnknown();
}

int CPU::opcodeCB8E()
{
	return opcodeUnknown();
}

int CPU::opcodeCB8F()
{
	return opcodeUnknown();
}


int CPU::opcodeCB90()
{
	return opcodeUnknown();
}

int CPU::opcodeCB91()
{
	return opcodeUnknown();
}

int CPU::opcodeCB92()
{
	return opcodeUnknown();
}

int CPU::opcodeCB93()
{
	return opcodeUnknown();
}

int CPU::opcodeCB94()
{
	return opcodeUnknown();
}

int CPU::opcodeCB95()
{
	return opcodeUnknown();
}

int CPU::opcodeCB96()
{
	return opcodeUnknown();
}

int CPU::opcodeCB97()
{
	return opcodeUnknown();
}

int CPU::opcodeCB98()
{
	return opcodeUnknown();
}

int CPU::opcodeCB99()
{
	return opcodeUnknown();
}

int CPU::opcodeCB9A()
{
	return opcodeUnknown();
}

int CPU::opcodeCB9B()
{
	return opcodeUnknown();
}

int CPU::opcodeCB9C()
{
	return opcodeUnknown();
}

int CPU::opcodeCB9D()
{
	return opcodeUnknown();
}

int CPU::opcodeCB9E()
{
	return opcodeUnknown();
}

int CPU::opcodeCB9F()
{
	return opcodeUnknown();
}


int CPU::opcodeCBA0()
{
	return opcodeUnknown();
}

int CPU::opcodeCBA1()
{
	return opcodeUnknown();
}

int CPU::opcodeCBA2()
{
	return opcodeUnknown();
}

int CPU::opcodeCBA3()
{
	return opcodeUnknown();
}

int CPU::opcodeCBA4()
{
	return opcodeUnknown();
}

int CPU::opcodeCBA5()
{
	return opcodeUnknown();
}

int CPU::opcodeCBA6()
{
	return opcodeUnknown();
}

int CPU::opcodeCBA7()
{
	return opcodeUnknown();
}

int CPU::opcodeCBA8()
{
	return opcodeUnknown();
}

int CPU::opcodeCBA9()
{
	return opcodeUnknown();
}

int CPU::opcodeCBAA()
{
	return opcodeUnknown();
}

int CPU::opcodeCBAB()
{
	return opcodeUnknown();
}

int CPU::opcodeCBAC()
{
	return opcodeUnknown();
}

int CPU::opcodeCBAD()
{
	return opcodeUnknown();
}

int CPU::opcodeCBAE()
{
	return opcodeUnknown();
}

int CPU::opcodeCBAF()
{
	return opcodeUnknown();
}


int CPU::opcodeCBB0()
{
	return opcodeUnknown();
}

int CPU::opcodeCBB1()
{
	return opcodeUnknown();
}

int CPU::opcodeCBB2()
{
	return opcodeUnknown();
}

int CPU::opcodeCBB3()
{
	return opcodeUnknown();
}

int CPU::opcodeCBB4()
{
	return opcodeUnknown();
}

int CPU::opcodeCBB5()
{
	return opcodeUnknown();
}

int CPU::opcodeCBB6()
{
	return opcodeUnknown();
}

int CPU::opcodeCBB7()
{
	return opcodeUnknown();
}

int CPU::opcodeCBB8()
{
	return opcodeUnknown();
}

int CPU::opcodeCBB9()
{
	return opcodeUnknown();
}

int CPU::opcodeCBBA()
{
	return opcodeUnknown();
}

int CPU::opcodeCBBB()
{
	return opcodeUnknown();
}

int CPU::opcodeCBBC()
{
	return opcodeUnknown();
}

int CPU::opcodeCBBD()
{
	return opcodeUnknown();
}

int CPU::opcodeCBBE()
{
	return opcodeUnknown();
}

int CPU::opcodeCBBF()
{
	return opcodeUnknown();
}


int CPU::opcodeCBC0()
{
	return opcodeUnknown();
}

int CPU::opcodeCBC1()
{
	return opcodeUnknown();
}

int CPU::opcodeCBC2()
{
	return opcodeUnknown();
}

int CPU::opcodeCBC3()
{
	return opcodeUnknown();
}

int CPU::opcodeCBC4()
{
	return opcodeUnknown();
}

int CPU::opcodeCBC5()
{
	return opcodeUnknown();
}

int CPU::opcodeCBC6()
{
	return opcodeUnknown();
}

int CPU::opcodeCBC7()
{
	return opcodeUnknown();
}

int CPU::opcodeCBC8()
{
	return opcodeUnknown();
}

int CPU::opcodeCBC9()
{
	return opcodeUnknown();
}

int CPU::opcodeCBCA()
{
	return opcodeUnknown();
}

int CPU::opcodeCBCB()
{
	return opcodeUnknown();
}

int CPU::opcodeCBCC()
{
	return opcodeUnknown();
}

int CPU::opcodeCBCD()
{
	return opcodeUnknown();
}

int CPU::opcodeCBCE()
{
	return opcodeUnknown();
}

int CPU::opcodeCBCF()
{
	return opcodeUnknown();
}


int CPU::opcodeCBD0()
{
	return opcodeUnknown();
}

int CPU::opcodeCBD1()
{
	return opcodeUnknown();
}

int CPU::opcodeCBD2()
{
	return opcodeUnknown();
}

int CPU::opcodeCBD3()
{
	return opcodeUnknown();
}

int CPU::opcodeCBD4()
{
	return opcodeUnknown();
}

int CPU::opcodeCBD5()
{
	return opcodeUnknown();
}

int CPU::opcodeCBD6()
{
	return opcodeUnknown();
}

int CPU::opcodeCBD7()
{
	return opcodeUnknown();
}

int CPU::opcodeCBD8()
{
	return opcodeUnknown();
}

int CPU::opcodeCBD9()
{
	return opcodeUnknown();
}

int CPU::opcodeCBDA()
{
	return opcodeUnknown();
}

int CPU::opcodeCBDB()
{
	return opcodeUnknown();
}

int CPU::opcodeCBDC()
{
	return opcodeUnknown();
}

int CPU::opcodeCBDD()
{
	return opcodeUnknown();
}

int CPU::opcodeCBDE()
{
	return opcodeUnknown();
}

int CPU::opcodeCBDF()
{
	return opcodeUnknown();
}


int CPU::opcodeCBE0()
{
	return opcodeUnknown();
}

int CPU::opcodeCBE1()
{
	return opcodeUnknown();
}

int CPU::opcodeCBE2()
{
	return opcodeUnknown();
}

int CPU::opcodeCBE3()
{
	return opcodeUnknown();
}

int CPU::opcodeCBE4()
{
	return opcodeUnknown();
}

int CPU::opcodeCBE5()
{
	return opcodeUnknown();
}

int CPU::opcodeCBE6()
{
	return opcodeUnknown();
}

int CPU::opcodeCBE7()
{
	return opcodeUnknown();
}

int CPU::opcodeCBE8()
{
	return opcodeUnknown();
}

int CPU::opcodeCBE9()
{
	return opcodeUnknown();
}

int CPU::opcodeCBEA()
{
	return opcodeUnknown();
}

int CPU::opcodeCBEB()
{
	return opcodeUnknown();
}

int CPU::opcodeCBEC()
{
	return opcodeUnknown();
}

int CPU::opcodeCBED()
{
	return opcodeUnknown();
}

int CPU::opcodeCBEE()
{
	return opcodeUnknown();
}

int CPU::opcodeCBEF()
{
	return opcodeUnknown();
}


int CPU::opcodeCBF0()
{
	return opcodeUnknown();
}

int CPU::opcodeCBF1()
{
	return opcodeUnknown();
}

int CPU::opcodeCBF2()
{
	return opcodeUnknown();
}

int CPU::opcodeCBF3()
{
	return opcodeUnknown();
}

int CPU::opcodeCBF4()
{
	return opcodeUnknown();
}

int CPU::opcodeCBF5()
{
	return opcodeUnknown();
}

int CPU::opcodeCBF6()
{
	return opcodeUnknown();
}

int CPU::opcodeCBF7()
{
	return opcodeUnknown();
}

int CPU::opcodeCBF8()
{
	return opcodeUnknown();
}

int CPU::opcodeCBF9()
{
	return opcodeUnknown();
}

int CPU::opcodeCBFA()
{
	return opcodeUnknown();
}

int CPU::opcodeCBFB()
{
	return opcodeUnknown();
}

int CPU::opcodeCBFC()
{
	return opcodeUnknown();
}

int CPU::opcodeCBFD()
{
	return opcodeUnknown();
}

int CPU::opcodeCBFE()
{
	return opcodeUnknown();
}

int CPU::opcodeCBFF()
{
	return opcodeUnknown();
}

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