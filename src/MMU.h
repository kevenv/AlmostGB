#pragma once

#define MEMORY_DEBUG
#define MEMORY_LOG

#if defined(MEMORY_DEBUG) || defined(MEMORY_LOG)
#include <string>
#endif
#include "utils.h"

class Cartridge;

/*
MEMORY MAP

0000-3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
4000-7FFF   16KB ROM Bank 01..NN (in cartridge, switchable bank number)
8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
C000-CFFF   4KB Work RAM Bank 0 (WRAM)
D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)
FE00-FE9F   Sprite Attribute Table (OAM)
FEA0-FEFF   Not Usable
FF00-FF7F   I/O Ports
FF80-FFFE   High RAM (HRAM)
FFFF        Interrupt Enable Register

*/

enum class MEMORY_MAP
{
	ROM_00 = 0,
	ROM_NN = 1,
	VRAM = 2,
	ERAM = 3,
	RAM_0 = 4,
	RAM_1 = 5,
	ECHO_RAM = 6,
	OAM = 7,
	UNUSED = 8,
	IO = 9,
	HRAM = 10,
	IER = 11
};

class MMU
{
public:
	MMU();
	~MMU();

	void mapCartridge(Cartridge& cartridge);

	u8 read8(u16 address);
	u16 read16(u16 address);
	void write8(u16 address, u8 value);

private:
	u8* m_memoryMap[12]{ nullptr };

	u8 m_RAM[8*1024];

	u8 read_memory(MEMORY_MAP map, u16 address, u16 offset);
	void write_memory(MEMORY_MAP map, u16 address, u16 offset, u8 value);
	bool check_map(MEMORY_MAP map, u16 address, u16 offset, bool write = false);

#ifdef MEMORY_DEBUG
	static void mem_access_error(const std::string& msg, MEMORY_MAP map, u16 address, u16 offset);
#endif

#if defined(MEMORY_DEBUG) || defined(MEMORY_LOG)
	static std::string mapToString(MEMORY_MAP map);
#endif
};
