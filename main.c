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
	FILE* fileRead = NULL;
	fileRead = fopen("compilerCreatorSetting.txt", "rb"); //assumes the file is written in utf8 without bom and contains only ascii characters
	if (fileRead == NULL)
		returnValue = 0;
	else {
		returnValue = fread((void*)&compilerCreatorSettings->compilerCreatorOperation, sizeof(uint8_t), 1, fileRead);
		if (returnValue) {
			compilerCreatorSettings->compilerCreatorOperation -= UINT8_C(48);
			returnValue = fread((void*)&compilerCreatorSettings->operatingSystem, sizeof(uint8_t), 1, fileRead);
		}
		if (returnValue) {
			compilerCreatorSettings->operatingSystem -= UINT8_C(48);
			returnValue = fread((void*)&compilerCreatorSettings->assemblyType, sizeof(uint8_t), 1, fileRead);
		}
		if(returnValue)
			compilerCreatorSettings->assemblyType -= UINT8_C(48);
		fclose(fileRead);
	}
	return returnValue;
}

int writeSettingsFile(int returnValue, struct CompilerCreatorSettings* compilerCreatorSettings) {
	FILE* fileWrite = NULL;
	fileWrite = fopen("compilerSetting.bin", "wb");
	if (fileWrite == NULL)
		returnValue = 0;
	else {
		returnValue = fwrite((void*)&compilerCreatorSettings->operatingSystem, sizeof(uint8_t), 1, fileWrite);
		if(returnValue)
			returnValue = fwrite((void*)&compilerCreatorSettings->assemblyType, sizeof(uint8_t), 1, fileWrite);
		fclose(fileWrite);
	}
	return returnValue;
}

int writeDOSHeader(int returnValue, FILE* fileWrite) {

}

int writeCompilerWindowsX64(int returnValue) {

}

int writeCompiler(int returnValue, struct CompilerCreatorSettings* compilerCreatorSettings) {
	
	return returnValue;
}

int main(int argc, char** argv) {
	int returnValue = 1; //in this program, 0 == error, anything else is valid
	struct CompilerCreatorSettings compilerCreatorSettings;
	returnValue = readSettings(returnValue, &compilerCreatorSettings);
	if (returnValue) {
		if (compilerCreatorSettings.compilerCreatorOperation == (uint8_t)COMPILER_CREATOR_OPERATION_WRITE_SETTING_FILE)
			returnValue = writeSettingsFile(returnValue, &compilerCreatorSettings);
		else if (compilerCreatorSettings.compilerCreatorOperation == (uint8_t)COMPILER_CREATOR_OPERATION_WRITE_COMPILER)
			returnValue = writeCompiler(returnValue, &compilerCreatorSettings);
	}
	return returnValue;
}
