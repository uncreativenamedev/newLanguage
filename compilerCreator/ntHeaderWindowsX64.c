#include "ntHeaderWindowsX64.h"

int writeNTHeaderWindowsX64(int returnValue, FILE** fileWrite) {
	struct ImageNTHeader64 imageNTHeader64;
	imageNTHeader64.signature = UINT32_C(0b00000000'00000000'01000101'01010000);
	return returnValue;
}
