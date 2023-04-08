#include "WADLoader.hpp"
// #include "WADTypes.hpp"

#include <unistd.h>
#include <filesystem>

WADLoader::WADLoader(std::string &path)
{
    this->LoadWAD(path);
}

WADLoader::WADLoader() {}

void WADLoader::LoadWAD(std::string &path)
{
    this->file.open(path, std::ios::in | std::ios::binary);
    this->path = path;

    WADReader reader;
    this->reader = reader;
}

WADLoader::~WADLoader() {}