#include <cstring>

#include "WADReader.hpp"
//#include "WADTypes.hpp"

WADReader::WADReader() {}

uint16_t WADReader::Read2Bytes(const uint8_t *data, int offset)
{
    uint16_t value;
    std::memcpy(&value, data + offset, sizeof(uint16_t));
    return value;
}

uint32_t WADReader::Read4Bytes(const uint8_t *data, int offset)
{
    uint32_t value;
    std::memcpy(&value, data + offset, sizeof(uint32_t));
    return value;
}

Header WADReader::ReadHeader(const uint8_t *data, int offset)
{
    Header header;
    return header;
}

WADReader::~WADReader() {}
