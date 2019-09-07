#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include <QOpenGLFunctions_4_1_Core>
#include "Components/meshcomponent.h"
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
    static ResourceFactory* instance();

    MeshComponent *createMeshComponent(std::string filePath);
    std::vector<MeshComponent> GetComponents() const;
private:
    std::vector<MeshComponent> mMeshComponents;
    ResourceFactory();
    std::map<std::string, unsigned int> mMeshComponentMap;

    void readOBJFile(std::string filename);
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
    void openGLVertexBuffers();
    void openGLIndexBuffer();

    static ResourceFactory* mInstance;

    void createAxis();
    void createObject(std::string filePath);
    void readTXTFile(std::string filename);
};

#endif // RESOURCEFACTORY_H
