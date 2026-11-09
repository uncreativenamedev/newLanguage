#include "includeUniversal.h"
#include "settings.h"
#include "dosHeaderWindowsX64.h"
#include "dosStubWindowsX64.h"
#include "ntHeaderWindowsX64.h"

int writeCompilerWindowsX64(int returnValue) {
	FILE* fileWrite = NULL;
	returnValue = writeDosHeaderwINDOWSx64(returnValue, &fileWrite);
	if (returnValue == ERROR_NONE)
		returnValue = writeDosStubWindowsX64(returnValue, &fileWrite);
	if (returnValue == ERROR_NONE)
		returnValue = writeNTHeaderWindowsX64(returnValue, &fileWrite);
	if (returnValue == ERROR_NONE)
		fclose(fileWrite);
	return returnValue;
}

int writeCompilerLinuxX64(int returnValue) {
	return returnValue;
}

int writeCompilerMacARM64(int returnValue) {
	return returnValue;
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
		if (compilerCreatorSettings.compilerCreatorOperation == UINT8_C(COMPILER_CREATOR_OPERATION_WRITE_SETTING_FILE))
			returnValue = writeSettingsFile(returnValue, &compilerCreatorSettings);
		else if (compilerCreatorSettings.compilerCreatorOperation == UINT8_C(COMPILER_CREATOR_OPERATION_WRITE_COMPILER))
			returnValue = writeCompiler(returnValue, &compilerCreatorSettings);
	}
	return returnValue;
}
