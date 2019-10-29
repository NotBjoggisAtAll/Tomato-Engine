#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include <QOpenGLFunctions_4_1_Core>
#include <vector>
#include "vertex.h"
#include <utility>
#include "Components/mesh.h"
#include "Components/collision.h"
#include "Components/sound.h"
#include <unordered_map>

class ResourceFactory : public QOpenGLFunctions_4_1_Core
{
public:

    static ResourceFactory* get();
    Mesh loadMesh(std::string file);
    Mesh createCollisionbox(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    Collision getCollision(std::string file);

private:
    ResourceFactory() = default;

    std::unordered_map<std::string, Mesh> meshUMap_;
    std::unordered_map<std::string, Collision> collisionUMap_;
    std::unordered_map<std::string, Sound> soundArray_;

    std::string file_ = "";

    Mesh createMesh();

    Mesh createAxis();
    Mesh createObject();
    Mesh createSkybox();
    Mesh createSphere();
    Mesh createPlane();
    void createCollision();

    unsigned int openGLVertexBuffers();
    void openGLIndexBuffer();

    void readTXTFile();
    void readOBJFile();
    void readTerrainFile();

    void calculateTerrainIndices(int TilesX, int TilesZ);
    void calculateTerrainNormals();

    std::vector<Vertex> vertices_;
    std::vector<unsigned int> indices_;
    static ResourceFactory* instance_;

};

#endif // RESOURCEFACTORY_H
