#include "WADLoader.hpp"
//#include "WADTypes.hpp"

WADLoader::WADLoader(const std::string &path) {
    this->LoadWAD(path);
}

WADLoader::WADLoader() {}

void WADLoader::LoadWAD(const std::string &path) {
    this->file.open(path, std::ios::in | std::ios::binary);
}

WADLoader::~WADLoader() {}