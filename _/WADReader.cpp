#include <cstring>

#include "WADReader.hpp"
//#include "WADTypes.hpp"

WADReader::WADReader() {

}

int16_t WADReader::Read2Bytes(const int8_t *data, int offset)
{
    int16_t value;
    std::memcpy(&value, data + offset, sizeof(int16_t));
    return value;
}

int32_t WADReader::Read4Bytes(const int8_t *data, int offset)
{
    int32_t value;
    std::memcpy(&value, data + offset, sizeof(int32_t));
    return value;
}

Header WADReader::ReadHeader(const int8_t *data)
{
    Header header;

    std::memcpy(&header, data, sizeof(Header));

    for (int i = 0; i < 4; i++)
    {
        header.WADType[i] = data[i];
    }

    header.DirectoryOffset = Read4Bytes(data, 8);
    header.DirectoryCount = Read4Bytes(data, 4);

    return header;
}

WADReader::~WADReader() {}
