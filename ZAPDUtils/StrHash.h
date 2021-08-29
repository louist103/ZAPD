#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint32_t strhash;

static strhash CRC32B(unsigned char* message, int32_t size);
constexpr static strhash CRC32BCT(const char* message, int32_t size);
