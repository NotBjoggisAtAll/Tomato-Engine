#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include <QOpenGLFunctions_4_1_Core>
#include <map>
#include <vector>
#include "vertex.h"
#include <utility>
#include "Components/mesh.h"
#include "Components/collision.h"

class Mesh;
class Collision;
class ResourceFactory : public QOpenGLFunctions_4_1_Core
{
public:

    static ResourceFactory* instance();
    std::pair<Mesh, Collision> loadMesh(const std::string &filePath);

    Mesh createLine(const std::string &filePath, std::vector<Vertex> vertices, std::vector<unsigned int> indices);

private:
    ResourceFactory() = default;

    void createCollision();
    //Used to check if the mesh is already loaded from file
    std::map<std::string, std::pair<Mesh, Collision>> mMeshMap; //string - filepath, Mesh - Meshdata, Collision - CollisionData
    std::map<std::string, std::pair<Mesh, Collision>>::iterator currentIt{};

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
    void readTerrainFile(std::string filename);

    static ResourceFactory* instance_;

    void calculateIndices(int TilesX, int TilesZ);
    void calculateNormals();
};

#endif // RESOURCEFACTORY_H
