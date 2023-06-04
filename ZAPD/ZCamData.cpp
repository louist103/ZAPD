#include "ZCamData.h"
#include <cassert>
#include "Globals.h"
#include "Utils/BitConverter.h"
#include "Utils/StringHelper.h"
#include "WarningHandler.h"

REGISTER_ZFILENODE(CamData, ZCamData);

ZCamData::ZCamData(ZFile* nParent) : ZResource(nParent)
{
	RegisterOptionalAttribute("Count");
}

ZCamData::ZCamData(ZFile* nParent, ZCollisionHeader* colParent)
	: ZResource(nParent), collisionParent(colParent)
{
}

ZCamData::~ZCamData()
{
}

void ZCamData::ParseXML(tinyxml2::XMLElement* reader)
{
	ZResource::ParseXML(reader);
}

void ZCamData::ParseRawData()
{
	const auto& rawData = parent->GetRawData();
	bool isSharpOcarina = false;
	offset_t cameraPosDataSeg = rawDataIndex;
	uint32_t cameraPosDataSegEnd = rawDataIndex;
	uint32_t numDataTotal;

	// if (numCams == 0) // Either it came from an XML with no count given or
	{
		size_t temp = rawDataIndex;
		do
		{
			temp += 0x08;
		} while (rawData[temp] == 0x00 && rawData[temp + 0x4] == 2);
		upperCameraBoundary = temp;
		numCams = (upperCameraBoundary - rawDataIndex) / 8;
	}

	assert(numCams < 10000);

	for (size_t i = 0; i < numCams; i++)
	{
		CameraDataEntry entry;

		entry.cameraSType =
			BitConverter::ToInt16BE(rawData, rawDataIndex + (entries.size() * 8) + 0);
		entry.numData = BitConverter::ToInt16BE(rawData, rawDataIndex + (entries.size() * 8) + 2);
		entry.cameraPosDataSeg =
			BitConverter::ToInt32BE(rawData, rawDataIndex + (entries.size() * 8) + 4);

		if (entry.cameraPosDataSeg != 0 && GETSEGNUM(entry.cameraPosDataSeg) != SEGMENT_SCENE)
		{
			cameraPosDataSeg = rawDataIndex + (entries.size() * 8);
			break;
		}

		if (rawDataIndex > GETSEGOFFSET(entry.cameraPosDataSeg))
		{
			if (entry.cameraPosDataSeg != 0 &&
			    cameraPosDataSeg > GETSEGOFFSET(entry.cameraPosDataSeg))
				cameraPosDataSeg = GETSEGOFFSET(entry.cameraPosDataSeg);
		}
		else
		{
			// Sharp Ocarina will place the cam data after the list as opposed to the original maps
			// which have it before.
			isSharpOcarina = true;
			cameraPosDataSeg = rawDataIndex + (numCams * 0x8);
			if (cameraPosDataSegEnd < GETSEGOFFSET(entry.cameraPosDataSeg))
				cameraPosDataSegEnd = GETSEGOFFSET(entry.cameraPosDataSeg);
		}

		entries.emplace_back(entry);
	}

	cameraPosDataOffset = GETSEGOFFSET(cameraPosDataSeg);

	if (!isSharpOcarina)
		numDataTotal = (rawDataIndex - cameraPosDataOffset) / 0x6;
	else
		numDataTotal = ((cameraPosDataSegEnd - cameraPosDataSeg) + 18) / 0x6;

	if (numDataTotal > 0)
	{
		// positionData.reserve(numDataTotal);
		points.reserve(numDataTotal);
		for (uint32_t i = 0; i < numDataTotal; i++)
		{
			ZVector vec(parent);
			vec.ExtractFromBinary(cameraPosDataOffset + (i * 6), ZScalarType::ZSCALAR_S16, 3);
			points.emplace_back(vec);
		}
	}
}

void ZCamData::DeclareReferences(const std::string& prefix)
{
	std::string declaration = "";
	std::string auxName = name;

	if (name == "")
		auxName = GetDefaultName(prefix);

	declaration = GetBodySourceCode();

	parent->AddDeclarationArray(rawDataIndex, DeclarationAlignment::Align4, GetRawDataSize(),
	                            GetSourceTypeName(), auxName.c_str(), entries.size(), declaration);

	declaration.clear();

	for (const auto& e : points)
	{
		declaration += StringHelper::Sprintf("\t{%s},\n", e.GetBodySourceCode().c_str());
	}

	parent->AddDeclarationArray(cameraPosDataOffset, DeclarationAlignment::Align4,
	                            points[0].GetRawDataSize() * points.size(), "Vec3s",
	                            StringHelper::Sprintf("%sCamPosData", auxName.c_str()),
	                            points.size(), declaration);
}

std::string ZCamData::GetBodySourceCode() const
{
	std::string body;

	// Trivially Copyable so no need to use references
	for (const auto e : entries)
	{
		std::string ptrString;
		char camSegLine[2048];

		if (e.cameraPosDataSeg != 0)
		{
			uint32_t index = (GETSEGOFFSET(e.cameraPosDataSeg) - cameraPosDataOffset) / 0x6;
			snprintf(camSegLine, 2048, "&%sCamPosData[%i]", GetName().c_str(), index);
		}
		else
			snprintf(camSegLine, 2048, "NULL");

		body +=
			StringHelper::Sprintf("\t{0x%04X, %d, %s},\n", e.cameraSType, e.numData, camSegLine);
	}
	return body;
}

std::string ZCamData::GetDefaultName(const std::string& prefix) const
{
	return StringHelper::Sprintf("%sCamData_%06X", prefix.c_str(), rawDataIndex);
}

ZResourceType ZCamData::GetResourceType() const
{
	return ZResourceType::CamData;
}

size_t ZCamData::GetRawDataSize() const
{
	return entries.size() * 8;
}

std::string ZCamData::GetSourceTypeName() const
{
	return "CamData";
}

CameraPositionData::CameraPositionData(const std::vector<uint8_t>& rawData, uint32_t rawDataIndex)
{
	x = BitConverter::ToInt16BE(rawData, rawDataIndex + 0);
	y = BitConverter::ToInt16BE(rawData, rawDataIndex + 2);
	z = BitConverter::ToInt16BE(rawData, rawDataIndex + 4);
}
