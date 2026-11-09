#include "dosHeaderWindowsX64.h"

int writeDosHeaderwINDOWSx64(int returnValue, FILE** fileWrite) {
	size_t numDataWritten = UINTMAX_C(0);
	*fileWrite = fopen("compiler_rmc_w64.exe", "wb");
	if (*fileWrite == NULL)
		returnValue = ERROR_WRITE_COMPILER_WINDOWS_X64_OPEN_EXECUTABLE_FILE;
	else {
		struct DosHeaderWindowsX64 dosHeaderWindowsX64;
		dosHeaderWindowsX64.magic = UINT16_C(0b01011010'01001101);
		dosHeaderWindowsX64.cblp = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.cp = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.crlc = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.cparhdr = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.minalloc = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.maxalloc = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.ss = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.sp = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.csum = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.ip = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.cs = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.lfarlc = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.ovno = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.res[0] = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.res[1] = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.res[2] = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.res[3] = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.oemid = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.oeminfo = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.res2[0] = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.res2[1] = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.res2[2] = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.res2[3] = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.res2[4] = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.res2[5] = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.res2[6] = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.res2[7] = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.res2[8] = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.res2[9] = UINT16_C(0b00000000'00000000);
		dosHeaderWindowsX64.lfanew = UINT32_C(0b10000000'00000000'00000000'00000000);
		numDataWritten = fwrite((void*)&dosHeaderWindowsX64, sizeof(struct DosHeaderWindowsX64), 1, *fileWrite);
		if (numDataWritten != UINTMAX_C(1)) {
			returnValue = ERROR_WRITE_DOS_HEADER_WINDOWS_X64_WRITE;
			fclose(*fileWrite);
		}
	}
	return returnValue;
}
