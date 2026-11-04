#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define COMPILER_CREATOR_OPERATION_WRITE_SETTING_FILE 0b00000000
#define COMPILER_CREATOR_OPERATION_WRITE_COMPILER     0b00000001

#define OPERATING_SYSTEM_WINDOWS 0b00000000
#define OPERATING_SYSTEM_LINUX   0b00000001
#define OPERATING_SYSTEM_MAC     0b00000010 

#define ASSEMBLY_TYPE_WINDOWS_X64 0b00000000
#define ASSEMBLY_TYPE_LINUX_X64   0b00000001
#define ASSEMBLY_TYPE_MAC_ARM64   0b00000010

#define ERROR_NONE 0b00000000'00000000'00000000'00000000 //align these later
#define ERROR_READ_SETTINGS_OPEN_FILE 0b00000000'00000000'00000000'00000001
#define ERROR_READ_SETTINGS_READ_FILE 0b00000000'00000000'00000000'00000010
#define ERROR_WRITE_SETTINGS_OPEN_FILE 0b00000000'00000000'00000000'00000011
#define ERROR_WRITE_SETTINGS_WRITE_FILE 0b00000000'00000000'00000000'00000100
#define ERROR_WRITE_COMPILER_WINDOWS_X64_OPEN_EXECUTABLE_FILE 0b00000000'00000000'00000000'00000101

struct CompilerCreatorSettings {
	uint8_t compilerCreatorOperation;
	uint8_t operatingSystem;
	uint8_t assemblyType;
};

struct DosHeaderWindowsX64 {
	uint16_t magic;
	uint16_t cblp;
	uint16_t cp;
	uint16_t crlc;
	uint16_t cparhdr;
	uint16_t minalloc;
	uint16_t maxalloc;
	uint16_t ss;
	uint16_t sp;
	uint16_t csum;
	uint16_t ip;
	uint16_t cs;
	uint16_t lfarlc;
	uint16_t ovno;
	uint16_t res[4];
	uint16_t oemid;
	uint16_t oeminfo;
	uint16_t res2[10];
	uint32_t lfanew;
};

int readSettings(int returnValue, struct CompilerCreatorSettings* compilerCreatorSettings) {
	size_t numDataRead = UINTMAX_C(0);
	FILE* fileRead = NULL;
	fileRead = fopen("compilerCreatorSetting.txt", "rb"); //assumes the file is written in utf8 without bom and contains only ascii characters
	if (fileRead == NULL)
		returnValue = ERROR_READ_SETTINGS_OPEN_FILE;
	else {
		numDataRead = fread((void*)&compilerCreatorSettings->compilerCreatorOperation, sizeof(uint8_t), 1, fileRead);
		if (numDataRead != UINTMAX_C(1))
			returnValue = ERROR_READ_SETTINGS_READ_FILE;
		if (returnValue == ERROR_NONE) {
			compilerCreatorSettings->compilerCreatorOperation -= UINT8_C(48);
			numDataRead = fread((void*)&compilerCreatorSettings->operatingSystem, sizeof(uint8_t), 1, fileRead);
			if (numDataRead != UINTMAX_C(1))
				returnValue = ERROR_READ_SETTINGS_READ_FILE;
		}
		if (returnValue == ERROR_NONE) {
			compilerCreatorSettings->operatingSystem -= UINT8_C(48);
			numDataRead = fread((void*)&compilerCreatorSettings->assemblyType, sizeof(uint8_t), 1, fileRead);
			if (numDataRead != UINTMAX_C(1))
				returnValue = ERROR_READ_SETTINGS_READ_FILE;
		}
		if(returnValue == ERROR_NONE)
			compilerCreatorSettings->assemblyType -= UINT8_C(48);
		fclose(fileRead);
	}
	return returnValue;
}

int writeSettingsFile(int returnValue, struct CompilerCreatorSettings* compilerCreatorSettings) {
	size_t numDataWritten = UINTMAX_C(0);
	FILE* fileWrite = NULL;
	fileWrite = fopen("compilerSetting.bin", "wb");
	if (fileWrite == NULL)
		returnValue = ERROR_WRITE_SETTINGS_OPEN_FILE;
	else {
		numDataWritten = fwrite((void*)&compilerCreatorSettings->operatingSystem, sizeof(uint8_t), 1, fileWrite);
		if (numDataWritten != UINTMAX_C(1))
			returnValue = ERROR_WRITE_SETTINGS_WRITE_FILE;
		if (returnValue != ERROR_NONE) {
			numDataWritten = fwrite((void*)&compilerCreatorSettings->assemblyType, sizeof(uint8_t), 1, fileWrite);
			if (numDataWritten != UINTMAX_C(1))
				returnValue = ERROR_WRITE_SETTINGS_WRITE_FILE;
		}
		fclose(fileWrite);
	}
	return returnValue;
}

int writeDOSHeader(int returnValue, FILE* fileWrite) {
	fileWrite = fopen("compiler_rmc_w64.exe", "wb");
	if (fileWrite == NULL)
		returnValue = ERROR_WRITE_COMPILER_WINDOWS_X64_OPEN_EXECUTABLE_FILE;
	else {

	}
}

int writeCompilerWindowsX64(int returnValue) {
	FILE* fileWrite = NULL;
}

int writeCompilerLinuxX64(int returnValue) {

}

int writeCompilerMacARM64(int returnValue) {

}

int writeCompiler(int returnValue, struct CompilerCreatorSettings* compilerCreatorSettings) {
	if (compilerCreatorSettings->operatingSystem == OPERATING_SYSTEM_WINDOWS) {
		if (compilerCreatorSettings->assemblyType == ASSEMBLY_TYPE_WINDOWS_X64)
			returnValue = writeCompilerWindowsX64(returnValue);
	}
	else if (compilerCreatorSettings->operatingSystem == OPERATING_SYSTEM_LINUX) {
		if (compilerCreatorSettings->assemblyType == ASSEMBLY_TYPE_LINUX_X64)
			returnValue = writeCompilerLinuxX64(returnValue);
	}
	else if (compilerCreatorSettings->operatingSystem == OPERATING_SYSTEM_MAC) {
		if (compilerCreatorSettings->assemblyType == ASSEMBLY_TYPE_MAC_ARM64)
			returnValue = writeCompilerMacARM64(returnValue);
	}
	return returnValue;
}

int main(int argc, char** argv) {
	int returnValue = ERROR_NONE;
	struct CompilerCreatorSettings compilerCreatorSettings;
	returnValue = readSettings(returnValue, &compilerCreatorSettings);
	if (returnValue == ERROR_NONE) {
		if (compilerCreatorSettings.compilerCreatorOperation == (uint8_t)COMPILER_CREATOR_OPERATION_WRITE_SETTING_FILE)
			returnValue = writeSettingsFile(returnValue, &compilerCreatorSettings);
		else if (compilerCreatorSettings.compilerCreatorOperation == (uint8_t)COMPILER_CREATOR_OPERATION_WRITE_COMPILER)
			returnValue = writeCompiler(returnValue, &compilerCreatorSettings);
	}
	return returnValue;
}
