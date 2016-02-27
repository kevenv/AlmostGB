#include "Cartridge.h"

#include <cstring>
#include "libs/cppformat/format.h"

Cartridge::Cartridge()
{

}

Cartridge::~Cartridge()
{
	if (m_buffer) {
		delete[] m_buffer;
		m_buffer = nullptr;
	}
}

bool Cartridge::load(const std::string& filePath)
{
	const std::string fullPath = "../roms/" + filePath;
	std::ifstream file(fullPath.c_str(), std::ifstream::binary);
	if (!file) {
		return false;
	}

	parseHeader(file);
	loadROM(file);
	
	return true;
}

void Cartridge::parseHeader(std::ifstream& file)
{
	//skip bootloader bytes
	char tmp[256];
	file.read(tmp, 256);

	//parse header
	m_entryPoint[0] = read16(file);
	m_entryPoint[1] = read16(file);
	readBytes(file, m_nintendoLogo, 48);
	readChars(file, m_title, 16);
	memcpy(m_manufacturerCode, m_title + 11, 4);
	m_manufacturerCode[4] = '\0';
	m_flagCGB = m_title[15] == 0xC0 ? true : false;
	readChars(file, m_newLicenseeCode, 2);
	m_flagSGB = read8(file) == 0x03 ? true : false;
	m_type = read8(file);
	m_sizeROM = read8(file);
	m_sizeRAM = read8(file);
	m_destinationCode = read8(file);
	m_oldLicenseeCode = read8(file);
	m_maskROMVersionNb = read8(file);
	m_headerChecksum = read8(file);
	m_globalChecksum = read16(file);

	//rewind
	file.seekg(0, file.beg);
}

void Cartridge::loadROM(std::ifstream& file)
{
	const int size = getROMSizeKB() * 1024;
	m_buffer = new u8[size];
	file.read((char*)m_buffer, size);
}

u8 Cartridge::read8(std::ifstream& file)
{
	u8 tmp[1];
	file.read((char*)tmp, 1);
	u8 value = tmp[0];
	return value;
}

u16 Cartridge::read16(std::ifstream& file)
{
	u8 tmp[2];
	file.read((char*)tmp, 2);
	u16 value = (tmp[1] << 8) | (tmp[0] << 0);
	return value;
}

void Cartridge::readBytes(std::ifstream& file, u8* buffer, int size)
{
	file.read((char*)buffer, size);
}

void Cartridge::readChars(std::ifstream& file, char* buffer, int size)
{
	file.read((char*)buffer, size);
	buffer[size] = '\0';
}

std::string Cartridge::toString()
{
	std::string str;

	str += fmt::format("Entry point: {:#x} {:#x}\n", m_entryPoint[0], m_entryPoint[1]);
	str += fmt::format("Title: [{}]\n", m_title);

	str += fmt::format("Type: {:#x} ({})\n", m_type, getTypeStr());
	str += fmt::format("CGB: {}\n", m_flagCGB);
	str += fmt::format("CGB: {}\n", m_flagSGB);
	str += fmt::format("Size ROM: {} ({} KB - {} banks)\n", m_sizeROM, getROMSizeKB(), getROMSizeKB()/16);
	str += fmt::format("Size RAM: {} ({} KB)\n", m_sizeRAM, getRAMSizeKB());
	
	str += fmt::format("Manufacturer code: [{}]\n", m_manufacturerCode);
	if (m_oldLicenseeCode == 0x33) {
		str += fmt::format("New Licensee code: [{}]\n", m_newLicenseeCode);
	}
	else {
		str += fmt::format("Old Licensee Code: {:#x}\n", m_oldLicenseeCode);
	}
	str += fmt::format("Destination Code: {:#x} ", m_destinationCode);
	if (m_destinationCode == 0x00) {
		str += "(JAPAN)\n";
	}
	else {
		str += "(OTHER)\n";
	}

	str += fmt::format("Mask ROM Version: {}\n", m_maskROMVersionNb);
	
	str += fmt::format("Header checksum: {:#x}\n", m_headerChecksum);
	str += fmt::format("Global checksum: {:#x}\n", m_globalChecksum);

	return str;
}

int Cartridge::getRAMSizeKB() const
{
	switch (m_sizeRAM) {
	case 0x00: return 0;
	case 0x01: return 2;
	case 0x02: return 8;
	case 0x03: return 32;
	}
}

int Cartridge::getROMSizeKB() const
{
	return 32 << m_sizeROM;
}

std::string Cartridge::getTypeStr() const
{
	switch (m_type) {
	case 0x00: return "ROM ONLY";
	case 0x01: return "MBC1";
	case 0x02: return "MBC1+RAM";
	case 0x03: return "MBC1+RAM+BATTERY";
	case 0x05: return "MBC2";
	case 0x06: return "MBC2+RAM";
	case 0x08: return "ROM+RAM";
	case 0x09: return "ROM+RAM+BATTERY";
	default: return "Unimplemented type";
	}
}
