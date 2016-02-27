#include"MMU.h"

#if defined(MEMORY_DEBUG) || defined(MEMORY_LOG)
#include <iostream>
#include "libs\cppformat\format.h"
#endif
#include "Cartridge.h"

MMU::MMU()
{

}

MMU::~MMU()
{

}

void MMU::mapCartridge(Cartridge& cartridge)
{
	m_memoryMap[(int)MEMORY_MAP::ROM_00] = const_cast<u8*>(cartridge.getROM());
	m_memoryMap[(int)MEMORY_MAP::ROM_NN] = const_cast<u8*>(cartridge.getROM());
	m_memoryMap[(int)MEMORY_MAP::VRAM] = nullptr;
	m_memoryMap[(int)MEMORY_MAP::ERAM] = cartridge.getRAM();
	m_memoryMap[(int)MEMORY_MAP::RAM_0] = m_RAM;
	m_memoryMap[(int)MEMORY_MAP::RAM_1] = m_RAM + (4 * 1024);
	m_memoryMap[(int)MEMORY_MAP::ECHO_RAM] = m_RAM;
	m_memoryMap[(int)MEMORY_MAP::OAM] = nullptr;
	m_memoryMap[(int)MEMORY_MAP::UNUSED] = nullptr;
	m_memoryMap[(int)MEMORY_MAP::IO] = nullptr;
	m_memoryMap[(int)MEMORY_MAP::IER] = nullptr;
}

u8 MMU::read8(u16 address)
{
	if (address >= 0x0000 && address < 0x4000) {
		return read_memory(MEMORY_MAP::ROM_00, address, 0x0000);
	}
	else if (address >= 0x4000 && address < 0x8000) {
		return read_memory(MEMORY_MAP::ROM_NN, address, 0x4000);
	}
	else if (address >= 0x8000 && address < 0xA000) {
		return read_memory(MEMORY_MAP::VRAM, address, 0x8000);
	}
	else if (address >= 0xA000 && address < 0xC000) {
		return read_memory(MEMORY_MAP::ERAM, address, 0xA000);
	}
	else if (address >= 0xC000 && address < 0xD000) {
		return read_memory(MEMORY_MAP::RAM_0, address, 0xC000);
	}
	else if (address >= 0xD000 && address < 0xE000) {
		return read_memory(MEMORY_MAP::RAM_1, address, 0xD000);
	}
	else if (address >= 0xE000 && address < 0xFE00) {
		return read_memory(MEMORY_MAP::ECHO_RAM, address, 0xE000);
	}
	else if (address >= 0xFE00 && address < 0xFEA0) {
		return read_memory(MEMORY_MAP::OAM, address, 0xFE00);
	}
	else if (address >= 0xFEA0 && address < 0xFF00) {
		return read_memory(MEMORY_MAP::UNUSED, address, 0xFEA0);
	}
	else if (address >= 0xFF00 && address < 0xFF80) {
		return read_memory(MEMORY_MAP::IO, address, 0xFF00);
	}
	else if (address >= 0xFF80 && address < 0xFFFF) {
		return read_memory(MEMORY_MAP::HRAM, address, 0xFF80);
	}
	else if (address == 0xFFFF) {
		return read_memory(MEMORY_MAP::IER, address, 0xFFFF);
	}
	else {
		return 0; //can't happen
	}
}

u16 MMU::read16(u16 address)
{
	return (read8(address + 1) << 8) | read8(address);
}

void MMU::write8(u16 address, u8 value)
{
	if (address >= 0x0000 && address < 0x4000) {
		write_memory(MEMORY_MAP::ROM_00, address, 0x0000, value);
	}
	else if (address >= 0x4000 && address < 0x8000) {
		write_memory(MEMORY_MAP::ROM_NN, address, 0x4000, value);
	}
	else if (address >= 0x8000 && address < 0xA000) {
		write_memory(MEMORY_MAP::VRAM, address, 0x8000, value);
	}
	else if (address >= 0xA000 && address < 0xC000) {
		write_memory(MEMORY_MAP::ERAM, address, 0xA000, value);
	}
	else if (address >= 0xC000 && address < 0xD000) {
		write_memory(MEMORY_MAP::RAM_0, address, 0xC000, value);
	}
	else if (address >= 0xD000 && address < 0xE000) {
		write_memory(MEMORY_MAP::RAM_1, address, 0xD000, value);
	}
	else if (address >= 0xE000 && address < 0xFE00) {
		write_memory(MEMORY_MAP::ECHO_RAM, address, 0xE000, value);
	}
	else if (address >= 0xFE00 && address < 0xFEA0) {
		write_memory(MEMORY_MAP::OAM, address, 0xFE00, value);
	}
	else if (address >= 0xFEA0 && address < 0xFF00) {
		write_memory(MEMORY_MAP::UNUSED, address, 0xFEA0, value);
	}
	else if (address >= 0xFF00 && address < 0xFF80) {
		write_memory(MEMORY_MAP::IO, address, 0xFF00, value);
	}
	else if (address >= 0xFF80 && address < 0xFFFF) {
		write_memory(MEMORY_MAP::HRAM, address, 0xFF80, value);
	}
	else if (address == 0xFFFF) {
		write_memory(MEMORY_MAP::IER, address, 0xFFFF, value);
	}
}

u8 MMU::read_memory(MEMORY_MAP map, u16 address, u16 offset)
{
	if (check_map(map, address, offset)) {
		return *( m_memoryMap[(int)map] + (address - offset) );
	}
	else {
		return 0;
	}
}

void MMU::write_memory(MEMORY_MAP map, u16 address, u16 offset, u8 value)
{
	if (check_map(map, address, offset, true)) {
		*(m_memoryMap[(int)map] + (address - offset)) = value;
	}
}

bool MMU::check_map(MEMORY_MAP map, u16 address, u16 offset, bool write)
{
#ifdef MEMORY_LOG
	std::cout << fmt::format("MEMORY {} ({} - {:#x} {:#x})", write ? "WRITE" : "READ", mapToString(map), address, offset) << std::endl;
#endif
#ifdef MEMORY_DEBUG
	u8* basePtr = m_memoryMap[(int)map];
	if (basePtr == nullptr) {
		mem_access_error("nothing is mapped", map, address, offset);
		return false;
	}
	if (map == MEMORY_MAP::UNUSED) {
		mem_access_error("mapping is forbidden!", map, address, offset);
		return false;
	}
	if(map == MEMORY_MAP::ECHO_RAM) {
		mem_access_error("shouldn't use ECHO RAM", map, address, offset);
		return false;
	}
	if (write && (map == MEMORY_MAP::ROM_00 || map == MEMORY_MAP::ROM_NN)) {
		mem_access_error("READ ONLY!", map, address, offset);
		return false;
	}
#endif
	return true;
}

#ifdef MEMORY_DEBUG

void MMU::mem_access_error(const std::string& msg, MEMORY_MAP map, u16 address, u16 offset)
{
	std::cout << fmt::format("MEMORY ACCESS ERROR ({} - {:#x} {:#x}) : {}", mapToString(map), address, offset, msg) << std::endl;
}

#endif

#if defined(MEMORY_DEBUG) || defined(MEMORY_LOG)

std::string MMU::mapToString(MEMORY_MAP map)
{
	switch (map) {
	case MEMORY_MAP::ROM_00: return "ROM 00";
	case MEMORY_MAP::ROM_NN: return "ROM NN (D)";
	case MEMORY_MAP::VRAM: return "VRAM";
	case MEMORY_MAP::ERAM: return "ERAM (D)";
	case MEMORY_MAP::RAM_0: return "RAM 0";
	case MEMORY_MAP::RAM_1: return "RAM 1";
	case MEMORY_MAP::ECHO_RAM: return "ECHO RAM";
	case MEMORY_MAP::OAM: return "OAM";
	case MEMORY_MAP::UNUSED: return "UNUSED";
	case MEMORY_MAP::IO: return "IO";
	case MEMORY_MAP::IER: return "IER";
	default: return ""; //cant't happen
	}
}

#endif
