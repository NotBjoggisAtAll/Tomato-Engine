#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include <QOpenGLFunctions_4_1_Core>
#include "Components/allcomponents.h"
#include <map>
#include <vector>
#include "vertex.h"

class ResourceFactory : public QOpenGLFunctions_4_1_Core
{
public:
    ResourceFactory() = default;

    Mesh loadMesh(std::string filePath);

private:

    //Used to check if the mesh is already loaded from file
    std::map<std::string, Mesh> mMeshMap; //string - filepath, Mesh - Meshdata
    std::map<std::string, Mesh>::iterator currentIt{};

    void readOBJFile(std::string filename);
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    void openGLVertexBuffers();
    void openGLIndexBuffer();

    void createPlane();
    void createSphere();
    void createAxis();
    void createSkybox();
    void createObject(std::string filePath);
    void readTXTFile(std::string filename);

};

#endif // RESOURCEFACTORY_H
