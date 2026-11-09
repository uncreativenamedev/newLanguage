#pragma once
#include "includeUniversal.h"

union Data {
	uint8_t u8[8];
	uint16_t u16[4];
	uint32_t u32[2];
	uint64_t u64;
};
