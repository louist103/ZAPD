#include "BitConverter.h"

int8_t ToInt8BE(const uint8_t* data, int32_t offset)
{
	return (uint8_t)data[offset + 0];
}

int8_t ToInt8BE(const std::vector<uint8_t>& data, int32_t offset)
{
	return (uint8_t)data[offset + 0];
}

uint8_t ToUInt8BE(const uint8_t* data, int32_t offset)
{
	return (uint8_t)data[offset + 0];
}

uint8_t ToUInt8BE(const std::vector<uint8_t>& data, int32_t offset)
{
	return (uint8_t)data[offset + 0];
}

int16_t ToInt16BE(const uint8_t* data, int32_t offset)
{
	return ((uint16_t)data[offset + 0] << 8) + (uint16_t)data[offset + 1];
}

int16_t ToInt16BE(const std::vector<uint8_t>& data, int32_t offset)
{
	return ((uint16_t)data[offset + 0] << 8) + (uint16_t)data[offset + 1];
}

uint16_t ToUInt16BE(const uint8_t* data, int32_t offset)
{
	return ((uint16_t)data[offset + 0] << 8) + (uint16_t)data[offset + 1];
}

uint16_t ToUInt16BE(const std::vector<uint8_t>& data, int32_t offset)
{
	return ((uint16_t)data[offset + 0] << 8) + (uint16_t)data[offset + 1];
}

int32_t ToInt32BE(const uint8_t* data, int32_t offset)
{
	return ((uint32_t)data[offset + 0] << 24) + ((uint32_t)data[offset + 1] << 16) +
	       ((uint32_t)data[offset + 2] << 8) + (uint32_t)data[offset + 3];
}

int32_t ToInt32BE(const std::vector<uint8_t>& data, int32_t offset)
{
	return ((uint32_t)data[offset + 0] << 24) + ((uint32_t)data[offset + 1] << 16) +
	       ((uint32_t)data[offset + 2] << 8) + (uint32_t)data[offset + 3];
}

uint32_t ToUInt32BE(const uint8_t* data, int32_t offset)
{
	return ((uint32_t)data[offset + 0] << 24) + ((uint32_t)data[offset + 1] << 16) +
	       ((uint32_t)data[offset + 2] << 8) + (uint32_t)data[offset + 3];
}

uint32_t ToUInt32BE(const std::vector<uint8_t>& data, int32_t offset)
{
	return ((uint32_t)data[offset + 0] << 24) + ((uint32_t)data[offset + 1] << 16) +
	       ((uint32_t)data[offset + 2] << 8) + (uint32_t)data[offset + 3];
}

int64_t ToInt64BE(const uint8_t* data, int32_t offset)
{
	return ((uint64_t)data[offset + 0] << 56) + ((uint64_t)data[offset + 1] << 48) +
	       ((uint64_t)data[offset + 2] << 40) + ((uint64_t)data[offset + 3] << 32) +
	       ((uint64_t)data[offset + 4] << 24) + ((uint64_t)data[offset + 5] << 16) +
	       ((uint64_t)data[offset + 6] << 8) + ((uint64_t)data[offset + 7]);
}

int64_t ToInt64BE(const std::vector<uint8_t>& data, int32_t offset)
{
	return ((uint64_t)data[offset + 0] << 56) + ((uint64_t)data[offset + 1] << 48) +
	       ((uint64_t)data[offset + 2] << 40) + ((uint64_t)data[offset + 3] << 32) +
	       ((uint64_t)data[offset + 4] << 24) + ((uint64_t)data[offset + 5] << 16) +
	       ((uint64_t)data[offset + 6] << 8) + ((uint64_t)data[offset + 7]);
}

uint64_t ToUInt64BE(const uint8_t* data, int32_t offset)
{
	return ((uint64_t)data[offset + 0] << 56) + ((uint64_t)data[offset + 1] << 48) +
	       ((uint64_t)data[offset + 2] << 40) + ((uint64_t)data[offset + 3] << 32) +
	       ((uint64_t)data[offset + 4] << 24) + ((uint64_t)data[offset + 5] << 16) +
	       ((uint64_t)data[offset + 6] << 8) + ((uint64_t)data[offset + 7]);
}

uint64_t ToUInt64BE(const std::vector<uint8_t>& data, int32_t offset)
{
	return ((uint64_t)data[offset + 0] << 56) + ((uint64_t)data[offset + 1] << 48) +
	       ((uint64_t)data[offset + 2] << 40) + ((uint64_t)data[offset + 3] << 32) +
	       ((uint64_t)data[offset + 4] << 24) + ((uint64_t)data[offset + 5] << 16) +
	       ((uint64_t)data[offset + 6] << 8) + ((uint64_t)data[offset + 7]);
}

float ToFloatBE(const uint8_t* data, int32_t offset)
{
	float value;
	uint32_t floatData = ((uint32_t)data[offset + 0] << 24) + ((uint32_t)data[offset + 1] << 16) +
	                     ((uint32_t)data[offset + 2] << 8) + (uint32_t)data[offset + 3];
	static_assert(sizeof(uint32_t) == sizeof(float), "expected 32-bit float");
	std::memcpy(&value, &floatData, sizeof(value));
	return value;
}

float ToFloatBE(const std::vector<uint8_t>& data, int32_t offset)
{
	float value;
	uint32_t floatData = ((uint32_t)data[offset + 0] << 24) + ((uint32_t)data[offset + 1] << 16) +
	                     ((uint32_t)data[offset + 2] << 8) + (uint32_t)data[offset + 3];
	static_assert(sizeof(uint32_t) == sizeof(float), "expected 32-bit float");
	std::memcpy(&value, &floatData, sizeof(value));
	return value;
}

double ToDoubleBE(const uint8_t* data, int32_t offset)
{
	double value;
	uint64_t floatData = ((uint64_t)data[offset + 0] << 56) + ((uint64_t)data[offset + 1] << 48) +
	                     ((uint64_t)data[offset + 2] << 40) + ((uint64_t)data[offset + 3] << 32) +
	                     ((uint64_t)data[offset + 4] << 24) + ((uint64_t)data[offset + 5] << 16) +
	                     ((uint64_t)data[offset + 6] << 8) + ((uint64_t)data[offset + 7]);
	static_assert(sizeof(uint64_t) == sizeof(double), "expected 64-bit double");
	// Checks if the float format on the platform the ZAPD binary is running on supports the
	// same float format as the object file.
	static_assert(std::numeric_limits<float>::is_iec559, "expected IEC559 floats on host machine");
	std::memcpy(&value, &floatData, sizeof(value));
	return value;
}

double ToDoubleBE(const std::vector<uint8_t>& data, int32_t offset)
{
	double value;
	uint64_t floatData = ((uint64_t)data[offset + 0] << 56) + ((uint64_t)data[offset + 1] << 48) +
	                     ((uint64_t)data[offset + 2] << 40) + ((uint64_t)data[offset + 3] << 32) +
	                     ((uint64_t)data[offset + 4] << 24) + ((uint64_t)data[offset + 5] << 16) +
	                     ((uint64_t)data[offset + 6] << 8) + ((uint64_t)data[offset + 7]);
	static_assert(sizeof(uint64_t) == sizeof(double), "expected 64-bit double");
	// Checks if the float format on the platform the ZAPD binary is running on supports the
	// same float format as the object file.
	static_assert(std::numeric_limits<double>::is_iec559,
	              "expected IEC559 doubles on host machine");
	std::memcpy(&value, &floatData, sizeof(value));
	return value;
}