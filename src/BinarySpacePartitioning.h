#pragma once

#include <vector>

#include "Engine.h"
#include "Player.h"
#include "WAD/WADTypes.h"

//0x8000
#define SUB_SECTOR_IDENTIFIER 32768

class BinarySpacePartitioning
{
public:
    std::vector<Seg> *segs;
    std::vector<SSector> *sSectors;
    std::vector<Node> *nodes;
    Player *player;
public:
    int rootNodeId;

public:
    BinarySpacePartitioning(Engine *engine);

public:
    bool addSegmentToFov(Vertex &vertex1, Vertex &vertex2, int &x_1, int &x_2);
    int angleToX(float angle);

public:
    bool onBackSide(Node *node);

public:
    void renderSubSector(int subSectorId);
    void renderNode(int nodeId);

public:
    void update();
};
