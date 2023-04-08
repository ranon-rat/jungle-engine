#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "WADReader.h"

WADReader::WADReader(std::string path)
{
    std::cout << "INFO: Loading WAD file: " << path << std::endl;

    std::ifstream file;
    file.open(path, std::ios::binary);

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();

    this->buffer = std::unique_ptr<uint8_t[]>(new uint8_t[size]);
    file.seekg(0, std::ios::beg);

    file.read((char *)this->buffer.get(), size);
    file.close();

    std::cout << "INFO: WAD file loaded: " << path << std::endl;

    this->readHeader();
    this->readDirectory();
}

uint16_t WADReader::read2Bytes(int offset)
{
    uint16_t value;
    std::memcpy(&value, this->buffer.get() + offset, sizeof(uint16_t));

    return value;
}

uint32_t WADReader::read4Bytes(int offset)
{
    uint32_t value;
    std::memcpy(&value, this->buffer.get() + offset, sizeof(uint32_t));

    return value;
}

void WADReader::readHeader()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        this->header.type[i] = this->buffer[i];
    }

    this->header.infoTableOffset = this->read4Bytes(8);
    this->header.numLumps = this->read4Bytes(4);
}

void WADReader::readDirectory()
{
    std::cout << this->header.infoTableOffset << std::endl;
    std::cout << this->header.numLumps << std::endl;

    for (uint32_t i = 0; i < this->header.numLumps; i++)
    {
        uint32_t offset = this->header.infoTableOffset + i * 16;

        Directory directory;

        directory.LumpOffset = this->read4Bytes(offset);
        directory.LumpSize = this->read4Bytes(offset + 4);

        for (uint8_t j = 0; j < 8; j++)
        {
            directory.LumpName[j] = this->buffer[offset + 8 + j];
        }

        this->directory.push_back(directory);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Thing WADReader::readThingData(int offset)
{
    return {
        .x = this->read2Bytes(offset),
        .y = this->read2Bytes(offset + 2),
        .angle = this->read2Bytes(offset + 4),
        .type = this->read2Bytes(offset + 6),
        .flags = this->read2Bytes(offset + 8),
    };
}

LineDef WADReader::readLineDefData(int offset)
{
    return {
        .startVertex = this->read2Bytes(offset),
        .endVertex = this->read2Bytes(offset + 2),
        .flags = this->read2Bytes(offset + 4),
        .specialType = this->read2Bytes(offset + 6),
        .sectorTag = this->read2Bytes(offset + 8),
        .frontSideDef = this->read2Bytes(offset + 10),
        .backSideDef = this->read2Bytes(offset + 12),
    }; 
}

/*SideDef WADReader::readSideDefData(int offset)
{
    return {
        .xOffset = this->read2Bytes(offset),
        .yOffset = this->read2Bytes(offset + 2),
        .upperTexture = this->read2Bytes(offset + 4),
        .lowerTexture = this->read2Bytes(offset + 6),
        .middleTexture = this->read2Bytes(offset + 8),
        .sector = this->read2Bytes(offset + 10),
    };
}*/

Vertex WADReader::readVertexData(int offset)
{
    return {
        .x = this->read2Bytes(offset),
        .y = this->read2Bytes(offset + 2),
    };
}

Seg WADReader::readSegData(int offset)
{
    return {
        .startVertex = this->read2Bytes(offset),
        .endVertex = this->read2Bytes(offset + 2),
        .angle = this->read2Bytes(offset + 4),
        .lineDef = this->read2Bytes(offset + 6),
        .direction = this->read2Bytes(offset + 8),
        .offset = this->read2Bytes(offset + 10),
    };
}

SSector WADReader::readSSectorData(int offset)
{
    return {
        .segCount = this->read2Bytes(offset),
        .firstSeg = this->read2Bytes(offset + 2),
    };
}

Node WADReader::readNodeData(int offset)
{
    Node node;

    node.x = this->read2Bytes(offset);
    node.y = this->read2Bytes(offset + 2);

    node.dx = this->read2Bytes(offset + 4);
    node.dy = this->read2Bytes(offset + 6);

    for (uint8_t i = 0; i < 4; i++)
    {
        node.rightBoundingBox[i] = this->read2Bytes(offset + 8 + i * 2);
        node.leftBoundingBox[i] = this->read2Bytes(offset + 16 + i * 2);
    }

    node.rightChild = this->read2Bytes(offset + 24);
    node.leftChild = this->read2Bytes(offset + 26);

    return node;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

uint32_t WADReader::getLumpIndex(std::string lumpName)
{
    for (uint32_t i = 0; i < this->header.numLumps; i++)
    {
        if (this->directory[i].LumpName == lumpName)
        {
            return i;
        }
    }

    return -1;
}
