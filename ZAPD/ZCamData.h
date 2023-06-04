#pragma once

#include "ZResource.h"
#include "ZVector.h"


class ZCollisionHeader;

class CameraPositionData
{
public:
    int16_t x, y, z;

    CameraPositionData(const std::vector<uint8_t>& rawData, uint32_t rawDataIndex);
};

class CameraDataEntry
{
public:
    int16_t cameraSType;
    int16_t numData;
    segptr_t cameraPosDataSeg;
};

class ZCamData : public ZResource
{
public:

    std::vector<CameraDataEntry> entries;
    std::vector<ZVector> points;
    ZCollisionHeader* collisionParent = nullptr;
    uint32_t numCams;
    uint32_t upperCameraBoundary;
    uint32_t cameraPosDataOffset;

    ZCamData(ZFile* nParent);
    ZCamData(ZFile* nParent, ZCollisionHeader* collisionParent);

    ~ZCamData();

    void ParseXML(tinyxml2::XMLElement* reader) override;

    void ParseRawData() override;
	void DeclareReferences(const std::string& prefix) override;

	std::string GetBodySourceCode() const override;
	std::string GetDefaultName(const std::string& prefix) const override;

	std::string GetSourceTypeName() const override;
	ZResourceType GetResourceType() const override;

	size_t GetRawDataSize() const override;
};
