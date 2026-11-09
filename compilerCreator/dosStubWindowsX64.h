#pragma once
#include "includeUniversal.h"
#include "data.h"

struct DosStubWindowsX64 {
	union Data value[8]; //64 bytes
};

int writeDosStubWindowsX64(int returnValue, FILE** fileWrite);
