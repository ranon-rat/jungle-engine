#pragma once

#include <string>
#include <vector>

#include "WADReader.h"

class WADLoader
{
public:
    WADReader reader;

public:
    std::vector<Thing> things;
    std::vector<LineDef> lineDefs;
    //std::vector<SideDef> sideDefs;
    std::vector<Vertex> vertexes;
    std::vector<Seg> segs;
    std::vector<SSector> sSectors;
    std::vector<Node> nodes;

public:
    int mapIndex;

public:
    WADLoader(std::string path);

public:
    void getThings();
    void getLineDefs();
    //void getSideDefs();
    void getVertexes();
    void getSegs();
    void getSSectors();
    void getNodes();
};
