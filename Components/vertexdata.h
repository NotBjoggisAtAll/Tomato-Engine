#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <vector>
#include "vertex.h"

struct VertexData
{
    VertexData();

    std::vector<Vertex> vertices_;
    std::vector<unsigned int> indices_;
};

#endif // VERTEXDATA_H
