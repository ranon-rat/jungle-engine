#include <cmath>
#include <iostream>
#include <string>

#include "WADLoader.h"
#include "WADReader.h"
#include "WADTypes.h"


WADLoader::WADLoader(std::string path) : reader(WADReader(path))
{
    this->mapIndex = this->reader.getLumpIndex("E1M1");

    this->getThings();
    this->getLineDefs();
    this->getVertexes();
    this->getSegs();
    this->getSSectors();
    this->getNodes();
}


void WADLoader::getThings()
{
    uint32_t thingIndex = this->mapIndex + EMAPLUMPSINDEX::THINGS;
    uint8_t numBytes = 10;

    Directory lumpInfo = this->reader.directory[thingIndex];
    int count = static_cast<int>(lumpInfo.LumpSize / numBytes);

    for (int i = 0; i < count; i++)
    {
        this->things.push_back(
            this->reader.readThingData(lumpInfo.LumpOffset + i * numBytes)
        );
    }

}

void WADLoader::getLineDefs()
{
    uint32_t lineDefIndex = this->mapIndex + EMAPLUMPSINDEX::LINEDEFS;
    uint8_t numBytes = 14;

    Directory lumpInfo = this->reader.directory[lineDefIndex];
    int count = static_cast<int>(lumpInfo.LumpSize / numBytes);

    for (int i = 0; i < count; i++)
    {
        this->lineDefs.push_back(
            this->reader.readLineDefData(lumpInfo.LumpOffset + i * numBytes)
        );
    }
}

void WADLoader::getVertexes()
{
    uint32_t vertexIndex = this->mapIndex + EMAPLUMPSINDEX::VERTEXES;
    uint8_t numBytes = 4;

    Directory lumpInfo = this->reader.directory[vertexIndex];
    int count = static_cast<int>(lumpInfo.LumpSize / numBytes);

    for (int i = 0; i < count; i++)
    {
        this->vertexes.push_back(
            this->reader.readVertexData(lumpInfo.LumpOffset + i * numBytes)
        );
    }
}

void WADLoader::getSegs()
{
    uint32_t segIndex = this->mapIndex + EMAPLUMPSINDEX::SEAGS;
    uint8_t numBytes = 12;

    Directory lumpInfo = this->reader.directory[segIndex];
    int count = static_cast<int>(lumpInfo.LumpSize / numBytes);

    for (int i = 0; i < count; i++)
    {
        this->segs.push_back(
            this->reader.readSegData(lumpInfo.LumpOffset + i * numBytes)
        );
    }
}

void WADLoader::getSSectors()
{
    uint32_t sSectorIndex = this->mapIndex + EMAPLUMPSINDEX::SSECTORS;
    uint8_t numBytes = 4;

    Directory lumpInfo = this->reader.directory[sSectorIndex];
    int count = static_cast<int>(lumpInfo.LumpSize / numBytes);

    for (int i = 0; i < count; i++)
    {
        this->sSectors.push_back(
            this->reader.readSSectorData(lumpInfo.LumpOffset + i * numBytes)
        );
    }
}

void WADLoader::getNodes()
{
    uint32_t nodeIndex = this->mapIndex + EMAPLUMPSINDEX::NODES;
    uint8_t numBytes = 28;

    Directory lumpInfo = this->reader.directory[nodeIndex];
    int count = static_cast<int>(lumpInfo.LumpSize / numBytes);

    for (int i = 0; i < count; i++)
    {
        this->nodes.push_back(
            this->reader.readNodeData(lumpInfo.LumpOffset + i * numBytes)
        );
    }
}
