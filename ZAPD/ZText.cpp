#include "ZText.h"

#include "Globals.h"
#include "Utils/BitConverter.h"
#include "Utils/File.h"
#include "Utils/Path.h"
#include "Utils/StringHelper.h"
#include "ZFile.h"

#include <array>
#include <unordered_map>

REGISTER_ZFILENODE(Text, ZText);

const std::map<const TextBoxType, const char* const> TextboxTypes{
	{TextBoxType::BLACK, "TEXTBOX_TYPE_BLACK"},
	{TextBoxType::WOODEN, "TEXTBOX_TYPE_WOODEN"},
	{TextBoxType::BLUE, "TEXTBOX_TYPE_BLUE"},
	{TextBoxType::OCA, "TEXTBOX_TYPE_OCARINA"},
	{TextBoxType::NONE_BOTTOM, "TEXTBOX_TYPE_NONE_BOTTOM"},
	{TextBoxType::NONE_NO_SHADOW, "TEXTBOX_TYPE_NONE_NO_SHADOW"},
	{TextBoxType::CREDITS, "TEXTBOX_TYPE_CREDITS"}};

const std::array<const char* const, 4> TextBoxPositions{
	"TEXTBOX_POSITION_VARIABLE",
	"TEXTBOX_POSITION_TOP",
	"TEXTBOX_POSITION_BOTTOM",
	"TEXTBOX_POSITION_MIDDLE",
};

const std::array<const char* const, 8> TextBoxColors{
	"DEFAULT", "RED", "ADJUSTABLE", "BLUE", "LIGHTBLUE", "PURPLE", "YELLOW", "BLACK",
};

const std::array<const char* const, 7> HighScores{
	"HS_HORSE_ARCHERY", "HS_POE_POINTS", "HS_LARGEST_FISH", "HS_HORSE_RACE",
	"HS_MARATHON",      "HS_DAMPE_RACE", "HS_DAMPE_RACE",  // TODO
};

const std::array<const char* const, 45> SpecialChars{
	"‾",        "À",         "î",      "Â",
	"Ä",        "Ç",         "È",      "É",
	"Ê",        "Ë",         "Ï",      "Ô",
	"Ö",        "Ù",         "Û",      "Ü",
	"ß",        "à",         "á",      "â",
	"ä",        "ç",         "è",      "é",
	"ê",        "ë",         "ï",      "ô",
	"ö",        "ù",         "û",      "ü",
	"[A]",      "[B]",       "[C]",    "[L]",
	"[R]",      "[Z]",       "[C-Up]", "[C-Down]",
	"[C-Left]", "[C-Right]", "▼",      "[Control-Pad]",
	"[D-Pad]",
};

typedef enum
{
	NEWLINE = 1,
	END,
	BOX_BREAK = 4,
	COLOR,
	SHIFT,
	TEXTID,
	QUICKTEXT_ENABLE,
	QUICKTEXT_DISABLE,
	PERSISTENT,
	EVENT,
	BOX_BREAK_DELAYED,
	AWAIT_BUTTON_PRESS,
	FADE,
	NAME,
	OCARINA,
	FADE2,
	SFX,
	ITEM_ICON,
	TEXT_SPEED,
	BACKGROUND,
	MARATHON_TIME,
	RACE_TIME,
	POINTS,
	TOKENS,
	UNSKIPPABLE,
	TWO_CHOICE,
	THREE_CHOICE,
	FISH_INFO,
	HIGHSCORE,
	TIME,
} ControlCodes;

ZText::ZText(ZFile* nParent) : ZResource(nParent)
{
	RegisterRequiredAttribute("CodeOffset");
	RegisterOptionalAttribute("LangOffset", "0");
}

void ZText::ParseRawData()
{
	ZResource::ParseRawData();

	const auto& rawData = parent->GetRawData();
	uintptr_t currentPtr = StringHelper::StrToL(registeredAttributes.at("CodeOffset").value, 16);
	uintptr_t langPtr = currentPtr;
	bool isPalLang = false;

	if (StringHelper::StrToL(registeredAttributes.at("LangOffset").value, 16) != 0)
	{
		langPtr = StringHelper::StrToL(registeredAttributes.at("LangOffset").value, 16);

		if (langPtr != currentPtr)
			isPalLang = true;
	}

	std::vector<uint8_t> codeData;
	messages.reserve(0x843);

	codeData = File::ReadAllBytes((Globals::Instance->baseRomPath.string() + "code"));

	while (true)
	{
		MessageEntry msgEntry;
		msgEntry.id = BitConverter::ToInt16BE(codeData, currentPtr + 0);
		msgEntry.textboxType = (TextBoxType)((codeData[currentPtr + 2] & 0xF0) >> 4);
		msgEntry.textboxYPos = (TextBoxPosition)(codeData[currentPtr + 2] & 0x0F);

		if (isPalLang)
		{
			msgEntry.segmentId = (codeData[langPtr + 0]);
			msgEntry.msgOffset = BitConverter::ToInt32BE(codeData, langPtr + 0) & 0x00FFFFFF;
		}
		else
		{
			msgEntry.segmentId = (codeData[langPtr + 4]);
			msgEntry.msgOffset = BitConverter::ToInt32BE(codeData, langPtr + 4) & 0x00FFFFFF;
		}

		uint32_t msgPtr = msgEntry.msgOffset;

		unsigned char c = rawData[msgPtr];
		unsigned int extra = 0;
		bool stop = false;

		while ((c != '\0' && !stop) || extra > 0)
		{
			msgEntry.msg += c;
			msgPtr++;

			if (extra == 0)
			{
				if (c == 0x05 || c == 0x13 || c == 0x0E || c == 0x0C || c == 0x1E || c == 0x06 ||
				    c == 0x14)
				{
					extra = 1;
				}
				else if (c == 0x07)
				{
					extra = 2;
					stop = true;
				}
				else if (c == 0x12 || c == 0x11)
				{
					extra = 2;
				}
				else if (c == 0x15)
				{
					extra = 3;
				}
			}
			else
			{
				extra--;
			}

			c = rawData[msgPtr];
		}

		messages.push_back(msgEntry);

		if (msgEntry.id == 0xFFFC || msgEntry.id == 0xFFFF)
			break;

		currentPtr += 8;

		if (isPalLang)
			langPtr += 4;
		else
			langPtr += 8;
	}

	int bp2 = 0;
}

/*
DEFINE_MESSAGE(0x0001, TEXTBOX_TYPE_BLUE, TEXTBOX_POS_MIDDLE,
UNSKIPPABLE  ITEM_ICON("\x2D")  QUICKTEXT_ENABLE "You borrowed a " COLOR(RED) "Pocket Egg"
COLOR(DEFAULT) "!" QUICKTEXT_DISABLE "\n" "A Pocket Cucco will hatch from\n" "it overnight. Be sure
to give it\n" "back when you are done with it."
,
UNSKIPPABLE  ITEM_ICON("\x2D")  QUICKTEXT_ENABLE "Du hast ein " COLOR(RED) "Ei " COLOR(DEFAULT)
"ausgeliehen!" QUICKTEXT_DISABLE "\n" "Bald wird Kiki ausschl�pfen.\n" "Gib es zur�ck, wenn Du\n"
"es nicht mehr ben�tigst!"
,
UNSKIPPABLE  ITEM_ICON("\x2D")  QUICKTEXT_ENABLE "Vous obtenez un " COLOR(RED) "Oeuf de \n"
"Poche" COLOR(DEFAULT) "!" QUICKTEXT_DISABLE " Une Cocotte appara�tra\n"
"demain matin. Allez la rendre\n"
"une fois utilis�e."
)*/

void ZText::GetOneArgString(std::string& output, const std::string& message, size_t index)
{
	output += StringHelper::Sprintf("\\x%02X\") ", message[index + 1]);
}

void ZText::GetTwoArgString(std::string& output, const std::string& message, size_t index)
{
	output += StringHelper::Sprintf("\\x%02X\\x%02X\") ", (unsigned char)message[index + 1],
	                                (unsigned char)message[index + 2]);
}

bool ZText::IsCharControlChar(unsigned char c)
{
	switch (c)
	{
	case ControlCodes::NEWLINE:
	case ControlCodes::END:
	case ControlCodes::BOX_BREAK:
	case ControlCodes::COLOR:
	case ControlCodes::SHIFT:
	case ControlCodes::TEXTID:
	case ControlCodes::QUICKTEXT_ENABLE:
	case ControlCodes::QUICKTEXT_DISABLE:
	case ControlCodes::PERSISTENT:
	case ControlCodes::EVENT:
	case ControlCodes::BOX_BREAK_DELAYED:
	case ControlCodes::AWAIT_BUTTON_PRESS:
	case ControlCodes::FADE:
	case ControlCodes::NAME:
	case ControlCodes::OCARINA:
	case ControlCodes::FADE2:
	case ControlCodes::SFX:
	case ControlCodes::ITEM_ICON:
	case ControlCodes::TEXT_SPEED:
	case ControlCodes::BACKGROUND:
	case ControlCodes::MARATHON_TIME:
	case ControlCodes::RACE_TIME:
	case ControlCodes::POINTS:
	case ControlCodes::TOKENS:
	case ControlCodes::UNSKIPPABLE:
	case ControlCodes::TWO_CHOICE:
	case ControlCodes::THREE_CHOICE:
	case ControlCodes::FISH_INFO:
	case ControlCodes::HIGHSCORE:
	case ControlCodes::TIME:
		return true;
	default:
		return false;
	}
}

std::string ZText::GetBodySourceCode() const
{
	std::string output;
	bool quoteIsOpen = false;

	for (const auto& message : messages)
	{
		// Message header
		output += StringHelper::Sprintf("\nDEFINE_MESSAGE(0x%04X, %s, %s, \n", message.id,
		                                TextboxTypes.at(message.textboxType),
		                                TextBoxPositions[message.textboxYPos]);
		for (size_t i = 0; i < message.msg.size(); i++)
		{
			switch (message.msg[i])
			{
			case ControlCodes::NEWLINE:
				output += "\n";
				break;
			case ControlCodes::END:
				output += "\n)\n";
				break;
			case ControlCodes::BOX_BREAK:
				output += "\nBOX_BREAK\n";
				break;
			case ControlCodes::COLOR:
				output +=
					StringHelper::Sprintf(" COLOR(%s) ", TextBoxColors[message.msg[++i] - 0x40]);
				break;
			case ControlCodes::SHIFT:
				output += " SHIFT(\"";
				ZText::GetOneArgString(output, message.msg, i);
				i++;
				break;
			case ControlCodes::TEXTID:
				output += " TEXTID(\"";
				ZText::GetTwoArgString(output, message.msg, i);
				i += 2;
				break;
			case ControlCodes::QUICKTEXT_ENABLE:
				output += "QUICKTEXT_ENABLE ";
				break;
			case ControlCodes::QUICKTEXT_DISABLE:
				output += "QUICKTEXT_DISABLE ";
				break;
			case ControlCodes::PERSISTENT:
				output += "PERSISTENT ";
				break;
			case ControlCodes::EVENT:
				output += "EVENT";
				break;
			case ControlCodes::BOX_BREAK_DELAYED:
				output += "BOX_BREAK_DELAYED(\"";
				ZText::GetOneArgString(output, message.msg, i);
				i++;
				break;
			case ControlCodes::AWAIT_BUTTON_PRESS:
				break;  // Not used?
			case ControlCodes::FADE:
				output += "FADE(\"";
				ZText::GetOneArgString(output, message.msg, i);
				i++;
				break;
			case ControlCodes::NAME:
				output += "NAME ";
				break;
			case ControlCodes::OCARINA:
				output += "OCARINA ";
				break;
			case ControlCodes::FADE2:
				break;  // Not used?
			case ControlCodes::SFX:
				output += "SFX(\"";
				ZText::GetTwoArgString(output, message.msg, i);
				i += 2;
				break;
			case ControlCodes::ITEM_ICON:
				output += " ITEM_ICON(\"";
				ZText::GetOneArgString(output, message.msg, i);
				i++;
				break;
			case ControlCodes::TEXT_SPEED:
				output += " TEXT_SPEED(\"";
				ZText::GetOneArgString(output, message.msg, i);
				i++;
				break;
			case ControlCodes::BACKGROUND:
			{
				char a1 = message.msg[++i];
				char a2 = message.msg[++i];
				char a3 = message.msg[++i];
				output += StringHelper::Sprintf(" BACKGROUND\"\\x02X\", \"\\x02X\", \\x02X\") ", a1,
				                                a2, a3);
				break;
			}
			case ControlCodes::MARATHON_TIME:
				output += "MARATHON_TIME ";
				break;
			case ControlCodes::RACE_TIME:
				output += "RACE_TIME ";
				break;
			case ControlCodes::POINTS:
				output += "POINTS ";
				break;
			case ControlCodes::TOKENS:
				output += "TOKENS ";
				break;
			case ControlCodes::UNSKIPPABLE:
				output += "UNSKIPPABLE ";
				break;
			case ControlCodes::TWO_CHOICE:
				output += "TWO_CHOICE ";
				break;
			case ControlCodes::THREE_CHOICE:
				output += "THREE_CHOICE";
				break;
			case ControlCodes::FISH_INFO:
				output += "FISH_INFO ";
				break;
			case ControlCodes::HIGHSCORE:
				output += StringHelper::Sprintf(" HIGHSCORE(%s) ", HighScores[message.msg[++i]]);
				break;
			case ControlCodes::TIME:
				output += "TIME ";
				break;
			default:
				if (!quoteIsOpen)
				{
					output += "\"";
					quoteIsOpen = true;
				}

				if ((unsigned char)message.msg[i] >= 0x7F && (unsigned char)message.msg[i] <= 0xAB)
				{
					output += SpecialChars[(unsigned char)message.msg[i] - 0x7F];
				}
				else
				{
					switch (message.msg[i])
					{
					case '\"':
						output += "\\\"";
						break;
					case '\\':
						output += "\\\\";
						break;
						[[likely]] default : output += message.msg[i];
					}
				}

				if ((i != message.msg.size()) && (IsCharControlChar(message.msg[i + 1])))
				{
					output += "\"";
					quoteIsOpen = false;
				}
			}
		}
	}

	return output;
}

std::string ZText::GetSourceTypeName() const
{
	return "u8";
}

size_t ZText::GetRawDataSize() const
{
	return 1;
}

ZResourceType ZText::GetResourceType() const
{
	return ZResourceType::Text;
}
