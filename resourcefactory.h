#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include <QOpenGLFunctions_4_1_Core>
#include <vector>
#include "vertex.h"
#include <utility>
#include "Components/mesh.h"
#include "Components/collision.h"
#include "Components/sound.h"
#include "Components/vertexdata.h"
#include <unordered_map>
#include <optional>

class ResourceFactory : public QOpenGLFunctions_4_1_Core
{
public:

    static ResourceFactory* get();
    Mesh loadMesh(std::string file);
    Mesh createLines(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    Mesh createLines(std::pair<std::vector<Vertex>,std::vector<unsigned int>> verticesAndIndices);
    Collision getCollision(std::string file);

    Mesh getCameraFrustum();

    VertexData getLastTerrainImported() const;

    /**
     * Returns the vertex data of the previous meshloaded with the function loadMesh()
     * If vertices_ and indices_ are both empty a empty optional is returned.
     * @return Returns VertexData or nothing, depending on when the function is called.
     */
    std::optional<VertexData> getVertexData();
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

    VertexData lastTerrainImported;

};

#endif // RESOURCEFACTORY_H
