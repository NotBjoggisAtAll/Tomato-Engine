#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include <QOpenGLFunctions_4_1_Core>
#include "Components/allcomponents.h"
#include <map>
#include <vector>
#include "vertex.h"
#include <optional>

enum class MeshType{
    Billboard,
    XYZ,
    Cube,
    Sphere,
    OBJ,
    TXT
};

class ResourceFactory : public QOpenGLFunctions_4_1_Core
{
public:
    ResourceFactory();

    MeshComponent* createMeshComponent(unsigned int EntityID, std::string filePath, std::vector<MeshComponent> &mMeshComponents);

private:

    std::map<std::string, unsigned int> mMeshComponentMap; //string = filepath, unsigned int = Index in vector

    void readOBJFile(std::string filename);
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    void openGLVertexBuffers(std::vector<MeshComponent> &mMeshComponents);
    void openGLIndexBuffer(std::vector<MeshComponent> &mMeshComponents);


    void createPlane(std::vector<MeshComponent> &mMeshComponents);
    void createSphere(std::vector<MeshComponent> &mMeshComponents);
    void createAxis(std::vector<MeshComponent> &mMeshComponents);
    void createSkybox(std::vector<MeshComponent> &mMeshComponents);
    void createObject(std::vector<MeshComponent> &mMeshComponents, std::string filePath);
    void readTXTFile(std::string filename);
};

#endif // RESOURCEFACTORY_H
