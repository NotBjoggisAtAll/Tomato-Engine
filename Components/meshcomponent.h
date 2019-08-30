#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "basecomponent.h"
#include <vector>
#include "vertex.h"
#include "gltypes.h"
#include "Managers/filemanager.h"
struct MeshComponent : public BaseComponent
{
    MeshComponent(std::string FileName)
    {
        auto[vertices,indices] = FileManager::GetInstance()->ReadFile(QString::fromStdString(FileName));
        mVertices = vertices;
        mIndices = indices;
    }
    std::vector<Vertex> mVertices;   //This is usually not needed after object is made
    std::vector<GLuint> mIndices;    //This is usually not needed after object is made
};

#endif // MESHCOMPONENT_H
