#pragma once

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
    WADLoader(std::string &path);
    WADLoader();

public:
    void LoadWAD(std::string &path);

public:
    ~WADLoader();
};
