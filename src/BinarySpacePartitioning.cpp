#include <algorithm>
#include <math.h>

#include "BinarySpacePartitioning.h"
#include "Global.h"

BinarySpacePartitioning::BinarySpacePartitioning(Engine *engine)
{
    // Extern
    this->segs = &engine->loader->segs;
    this->sSectors = &engine->loader->sSectors;
    this->nodes = &engine->loader->nodes;
    this->player = &engine->player;

    // Intern
    this->rootNodeId = this->nodes->size() - 1;
}

bool BinarySpacePartitioning::addSegmentToFov(
    Vertex &vertex1, Vertex &vertex2, int &x_1, int &x_2)
{
    float A_1 = this->player->pointToAngle(vertex1);
    float A_2 = this->player->pointToAngle(vertex2);

    float span_1 = A_2 - A_1;

    if (span_1 >= 180)
    {
        return false;
    }

    float A_3 = A_1;

    A_1 -= this->player->angle;
    A_2 -= this->player->angle;

    span_2 = A_1 + FOV;

    if (span_2 > FOV)
    {
        if (span_2 >= span_1 + FOV)
        {
            return false;
        }

        A_2 = -FOV;
    }

    x_1 = this->angleToX(A_1);
    x_2 = this->angleToX(A_2);

    return true;
}

int BinarySpacePartitioning::angleToX(float angle)
{
    float x = 0;

    if (angle > 0)
    {
        x = SCREEN_DIST - tan(angle * M_PI / 180) * WIDTH;
    }
    else
    {
        x = -tan(angle * M_PI / 180) * WIDTH + SCREEN_DIST;
    }

    return (int)round(x);
}

bool BinarySpacePartitioning::onBackSide(Node *node)
{
    auto dx = this->player->x - node->x;
    auto dy = this->player->y - node->y;

    return (dx * node.dy - dy * node.dx_partition) <= 0;
}

void BinarySpacePartitioning::renderSubSector(int subSectorId)
{
    SSector *subSector = &this->sSectors->at(subSectorId);

    for (int i = 0; i < subSector->segCount; i++)
    {
        Seg *seg = &this->segs->at(subSector->firstSeg + i);

        int x_1 = 0;
        int x_2 = 0;

        if (this->addSegmentToFov(seg->startVertex, seg->endVertex, x_1, x_2))
        {
            this->engine->drawSeg(seg, subSectorId);
        }
    }
}

void BinarySpacePartitioning::renderNode(int nodeId)
{
    if (nodeId & SUB_SECTOR_IDENTIFIER)
    {
        this->renderSubSector(nodeId - SUB_SECTOR_IDENTIFIER);

        return;
    }

    Node *node = &this->nodes->at(nodeId);

    if (this->onBackSide(node))
    {
        this->renderNode(node->rightChild);
        this->renderNode(node->leftChild);
    }
    else
    {
        this->renderNode(node->leftChild);
        this->renderNode(node->rightChild);
    }
}

void BinarySpacePartitioning::update()
{
    this->renderNode(this->rootNodeId);
}