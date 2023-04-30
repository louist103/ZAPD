#pragma once

#include "ZResource.h"
#include "tinyxml2.h"

typedef enum : uint8_t
{
	/*  0 */ BLACK,
	/*  1 */ WOODEN,
	/*  2 */ BLUE,
	/*  3 */ OCA,
	/*  4 */ NONE_BOTTOM,
	/*  5 */ NONE_NO_SHADOW,
	/* 11 */ CREDITS = 11
} TextBoxType;

typedef enum : uint8_t
{
	/* 0 */ VARIABLE,
	/* 1 */ TOP,
	/* 2 */ BOTTOM,
	/* 3 */ MIDDLE
} TextBoxPosition;

class MessageEntry
{
public:
	uint16_t id;
	TextBoxType textboxType;
	TextBoxPosition textboxYPos;
	uint32_t segmentId;
	uint32_t msgOffset;
	std::string msg;
};

class ZText : public ZResource
{
public:
	std::vector<MessageEntry> messages;

	ZText(ZFile* nParent);

	void ParseRawData() override;

	std::string GetSourceTypeName() const override;
	ZResourceType GetResourceType() const override;
	std::string GetBodySourceCode() const override;

	size_t GetRawDataSize() const override;

private:
	static void GetOneArgString(std::string& output, const std::string& message, size_t index);
	static void GetTwoArgString(std::string& output, const std::string& message, size_t index);
	static bool IsCharControlChar(unsigned char c);
};
