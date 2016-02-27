#pragma once

#include <string>
#include <fstream>
#include "utils.h"

class Cartridge
{
public:
	Cartridge();
	~Cartridge();

	std::string toString();

	bool load(const std::string& filePath);
	const u8* getROM() const { return m_ROM; }
	u8* getRAM() { return m_RAM; }

	int getRAMSizeKB() const;
	int getROMSizeKB() const;
	std::string getTypeStr() const;

	static const int HEADER_SIZE{ 336 };

private:
	u8* m_ROM{ nullptr };
	u8* m_RAM{ nullptr };

	u16 m_entryPoint[2]{ 0x0000 };
	u8 m_nintendoLogo[48]{ 0x00 };
	char m_title[17]{ '\0' };
	char m_manufacturerCode[5]{ '\0' };
	bool m_flagCGB{ false };
	char m_newLicenseeCode[3]{ '\0' };
	bool m_flagSGB{ false };
	u8 m_type{ 0x00 };
	u8 m_sizeROM{ 0x00 };
	u8 m_sizeRAM{ 0x00 };
	u8 m_destinationCode{ 0x00 };
	u8 m_oldLicenseeCode{ 0x00 };
	u8 m_maskROMVersionNb{ 0x00 };
	u8 m_headerChecksum{ 0x00 };
	u16 m_globalChecksum{ 0x0000 };

	void parseHeader(std::ifstream& file);
	void loadROM(std::ifstream& file);

	u8 read8(std::ifstream& file);
	u16 read16(std::ifstream& file);
	void readBytes(std::ifstream& file, u8* buffer, int size);
	void readChars(std::ifstream& file, char* buffer, int size);
};
