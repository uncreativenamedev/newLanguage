#include "dosHeaderWindowsX64.h"

int writeDOSHeader(int returnValue, FILE* fileWrite) {
	fileWrite = fopen("compiler_rmc_w64.exe", "wb");
	if (fileWrite == NULL)
		returnValue = ERROR_WRITE_COMPILER_WINDOWS_X64_OPEN_EXECUTABLE_FILE;
	else {
		struct DosHeaderWindowsX64 dosHeaderWindowsX64;
		dosHeaderWindowsX64.magic = UINT16_C(0b01011010'01001101);

	}
}