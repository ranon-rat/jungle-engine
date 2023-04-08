#pragma once

#include <cstdint>

enum EMAPLUMPSINDEX
{
    Name,
    THINGS,
    LINEDEFS,
    SIDEDDEFS,
    VERTEXES,
    SEAGS,
    SSECTORS,
    NODES,
    SECTORS,
    REJECT,
    BLOCKMAP,
    COUNT
};


struct Header
{
    uint32_t numLumps;
    uint32_t infoTableOffset;
    char type[4];
};

struct Directory
{
    uint32_t LumpOffset;
    uint32_t LumpSize;
    char LumpName[7];   
};

struct Thing
{
    int16_t x;
    int16_t y;
    int16_t angle;
    int16_t type;
    int16_t flags;
};

struct LineDef
{
    int16_t startVertex;
    int16_t endVertex;
    int16_t flags;
    int16_t specialType;
    int16_t sectorTag;
    int16_t frontSideDef;
    int16_t backSideDef;
};

struct SideDef
{
    int16_t x;
    int16_t y;
    char upperTexture[8];
    char lowerTexture[8];
    char middleTexture[8];
    int16_t sector;
};

struct Vertex
{
    int16_t x;
    int16_t y;
};

struct Seg
{
    int16_t startVertex;
    int16_t endVertex;
    int16_t angle;
    int16_t lineDef;
    int16_t direction;
    int16_t offset;
};

struct SSector
{
    int16_t segCount;
    int16_t firstSeg;
};

struct Node
{
    int16_t x;
    int16_t y;
    int16_t dx;
    int16_t dy;
    int16_t rightBoundingBox[4];
    int16_t leftBoundingBox[4];
    int16_t rightChild;
    int16_t leftChild;
};
