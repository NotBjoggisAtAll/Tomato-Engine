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
    static ResourceFactory* instance();

    MeshComponent *createMeshComponent(unsigned int EntityID, std::string filePath);
    TransformComponent *createTransformComponent(unsigned int EntityID);
    MaterialComponent *createMaterialComponent(unsigned int EntityID, Shader *Shader);

    std::vector<MeshComponent>& getMeshComponents();
    std::vector<TransformComponent>& getTransformComponents();
    std::vector<MaterialComponent>& getMaterialComponents();

private:
    std::vector<MeshComponent> mMeshComponents;
    std::vector<TransformComponent> mTransformComponents;
    std::vector<MaterialComponent> mMaterialComponents;



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
