#pragma once

#include <memory>
#include <string>
#include <vector>

#include "WADTypes.h"

class WADReader
{
public:
    std::unique_ptr<uint8_t[]> buffer;

public:
    std::vector<Directory> directory;
    Header header;

public:
    WADReader(std::string path);

public:
    uint16_t read2Bytes(int offset);
    uint32_t read4Bytes(int offset);

public:
    void readHeader();
    void readDirectory();

public:
    Thing readThingData(int offset);
    LineDef readLineDefData(int offset);
    //SideDef readSideDefData(int offset);
    Vertex readVertexData(int offset);
    Seg readSegData(int offset);
    SSector readSSectorData(int offset);
    Node readNodeData(int offset);

public:
    uint32_t getLumpIndex(std::string lumpName);
};
