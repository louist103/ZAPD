#pragma once

#include <limits>
#include <stdint.h>
#include <vector>

class BitConverter
{
public:
	int8_t ToInt8BE(const uint8_t* data, int32_t offset);

	int8_t ToInt8BE(const std::vector<uint8_t>& data, int32_t offset);

	uint8_t ToUInt8BE(const uint8_t* data, int32_t offset);

	uint8_t ToUInt8BE(const std::vector<uint8_t>& data, int32_t offset);

	int16_t ToInt16BE(const uint8_t* data, int32_t offset);

	int16_t ToInt16BE(const std::vector<uint8_t>& data, int32_t offset);

	uint16_t ToUInt16BE(const uint8_t* data, int32_t offset);

	uint16_t ToUInt16BE(const std::vector<uint8_t>& data, int32_t offset);

	int32_t ToInt32BE(const uint8_t* data, int32_t offset);

	int32_t ToInt32BE(const std::vector<uint8_t>& data, int32_t offset);

	uint32_t ToUInt32BE(const uint8_t* data, int32_t offset);

	uint32_t ToUInt32BE(const std::vector<uint8_t>& data, int32_t offset);

	int64_t ToInt64BE(const uint8_t* data, int32_t offset);

	int64_t ToInt64BE(const std::vector<uint8_t>& data, int32_t offset);

	uint64_t ToUInt64BE(const uint8_t* data, int32_t offset);

	uint64_t ToUInt64BE(const std::vector<uint8_t>& data, int32_t offset);

	float ToFloatBE(const uint8_t* data, int32_t offset);

	float ToFloatBE(const std::vector<uint8_t>& data, int32_t offset);

	double ToDoubleBE(const uint8_t* data, int32_t offset);

	double ToDoubleBE(const std::vector<uint8_t>& data, int32_t offset);
};
