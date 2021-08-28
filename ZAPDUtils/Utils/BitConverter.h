#pragma once

#include <limits>
#include <stdint.h>
#include <vector>

class BitConverter
{
public:
	static int8_t ToInt8BE(const uint8_t* data, int32_t offset);
	static int8_t ToInt8BE(const std::vector<uint8_t>& data, int32_t offset);
	static uint8_t ToUInt8BE(const uint8_t* data, int32_t offset);
	static uint8_t ToUInt8BE(const std::vector<uint8_t>& data, int32_t offset);
	static int16_t ToInt16BE(const uint8_t* data, int32_t offset);
	static int16_t ToInt16BE(const std::vector<uint8_t>& data, int32_t offset);
	static uint16_t ToUInt16BE(const uint8_t* data, int32_t offset);
	static uint16_t ToUInt16BE(const std::vector<uint8_t>& data, int32_t offset);
	static int32_t ToInt32BE(const uint8_t* data, int32_t offset);
	static int32_t ToInt32BE(const std::vector<uint8_t>& data, int32_t offset);
	static uint32_t ToUInt32BE(const uint8_t* data, int32_t offset);
	static uint32_t ToUInt32BE(const std::vector<uint8_t>& data, int32_t offset);
	static int64_t ToInt64BE(const uint8_t* data, int32_t offset);
	static int64_t ToInt64BE(const std::vector<uint8_t>& data, int32_t offset);
	static uint64_t ToUInt64BE(const uint8_t* data, int32_t offset);
	static uint64_t ToUInt64BE(const std::vector<uint8_t>& data, int32_t offset);
	static float ToFloatBE(const uint8_t* data, int32_t offset);
	static float ToFloatBE(const std::vector<uint8_t>& data, int32_t offset);
	static double ToDoubleBE(const uint8_t* data, int32_t offset);
	static double ToDoubleBE(const std::vector<uint8_t>& data, int32_t offset);
};  // namespace BitConverter
