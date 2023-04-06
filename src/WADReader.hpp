#include "WADTypes.hpp"

class WADReader
{
public:
    WADReader();

public:
    uint16_t Read2Bytes(const uint8_t *data, int offset);
    uint32_t Read4Bytes(const uint8_t *data, int offset);

public:
    Header ReadHeader(const uint8_t *data, int offset);

public:
    ~WADReader();
};
