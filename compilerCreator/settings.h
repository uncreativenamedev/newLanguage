#pragma once
#include "includeUniversal.h"

struct CompilerCreatorSettings {
	uint8_t compilerCreatorOperation;
	uint8_t operatingSystem;
	uint8_t assemblyType;
};

int readSettings(int returnValue, struct CompilerCreatorSettings* compilerCreatorSettings);

int writeSettingsFile(int returnValue, struct CompilerCreatorSettings* compilerCreatorSettings);