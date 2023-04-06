#include "fstream"

#include "WADReader.hpp"
#include "WADTypes.hpp"

class WADLoader
{
public:
    std::ifstream file;
    std::string path;

public:
    WADReader reader;

public:
    WADLoader(const std::string &path);
    WADLoader();

public:
    void LoadWAD(const std::string &path);

public:
    ~WADLoader();
};
