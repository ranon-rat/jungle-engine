#pragma once
#include "WADTypes.hpp"

class WADReader
{
public:
    WADReader();

public:
    int16_t Read2Bytes(const int8_t *data, int offset);
    int32_t Read4Bytes(const int8_t *data, int offset);

public:
    Header ReadHeader(const int8_t *data);

public:
    ~WADReader();
};
