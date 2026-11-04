#include "settings.h"

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
		if (returnValue == ERROR_NONE)
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