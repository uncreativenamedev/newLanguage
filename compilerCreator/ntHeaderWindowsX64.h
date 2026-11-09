#pragma once
#include "includeUniversal.h"

struct ImageFileHeaderWindowsX64 {
	uint16_t machine;
	uint16_t numberOfSections;
	uint32_t timeDateStamp;
	uint32_t pointerToSymbolTable;
	uint32_t numberOfSymbols;
	uint16_t sizeOfOptionalHeader;
	uint16_t characteristics;
};

struct ImageNTHeader64 {
	uint32_t signature;
	struct ImageFileHeaderWindowsX64 imageFileHeaderWindowsX64;

};

int writeNTHeaderWindowsX64(int returnValue, FILE** fileWrite);
