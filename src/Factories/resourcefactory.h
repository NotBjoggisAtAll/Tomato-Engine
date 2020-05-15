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
#include <optional>

/**
 * Responsible for making Mesh and Collision components and setting up VAO's for them.
 */
class ResourceFactory : public QOpenGLFunctions_4_1_Core
{
public:

    /**
     * Singleton class.
     * @return A instance of the class.
     */
    static ResourceFactory* get();

    /**
     * Creates a Mesh component from the given file.
     * Then stores it in a map for later use.
     * If the file is a txt or a obj file a AABB collision is also made and stored for the given file.
     * If the given file already is loaded a copy of it is returned instead of making a new one.
     * @param file - std::string. Assumes the location is Assets/Meshes.
     * @return A Mesh component.
     */
    Mesh loadMesh(std::string file);

    /**
     * Creates a Mesh component that simply is drawn with lines.
     * Used to show AABB collision and to show the BSplineCurve.
     * Does not store this Mesh component for later use.
     * @param vertices - std::vector< Vertex >. All the vertices of the given object.
     * @param indices - std::vector < unsigned int > . All the indices of the given object.
     * @return A Mesh component.
     */
    Mesh createLines(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    /**
     * Creates a Mesh component that simply is drawn with lines.
     * Used to show AABB collision and to show the BSplineCurve.
     * Does not store this Mesh component for later use.
     * @param verticesAndIndices - std::pair< std::vector< Vertex >, std::vector< unsigned int >>. All the vertices and indices of the given object.
     * @return A Mesh component.
     */
    Mesh createLines(std::pair<std::vector<Vertex>,std::vector<unsigned int>> verticesAndIndices);

    /**
     * Gets the Collision of the given file.
     * The given file needs to be a .txt or a .obj file AND the Mesh component needs to be stored in the map.
     * If it can't find the given mesh a empty Collision component is returned.
     * @param file
     * @return
     */
    Collision getCollision(std::string file);

    /**
     * Creates the frustum of a camera. Draws it as lines.
     * @return A Mesh component.
     */
    Mesh getCameraFrustum();

private:
    /**
     * Default Constructor. Since this is a singleton class the constructor is private.
     */
    ResourceFactory() = default;

    /**
     * This function is called if the Mesh doesn't exist in the map.
     * Used the member variable file_ to determine which type of Mesh to create.
     * Calls other member funtions depending on what Mesh type.
     * @return A Mesh component. The component is received from the other member functions.
     */
    Mesh createMesh();

    /**
     * Creates an Axis and calls other member functions to set it up properly.
     * Is called if the file_ is 'axis'.
     * @return A Mesh Component.
     */
    Mesh createAxis();

    /**
     * Creates a Mesh and calls other member functions to set it up properly.
     * Is called if the file_ is a .TXT or a .OBJ file.
     * @return A Mesh Component.
     */
    Mesh createObject();


    /**
     * Creates a Skybox and calls other member functions to set it up properly.
     * Is called if the file_ is 'skybox'.
     * @return A Mesh Component.
     */
    Mesh createSkybox();

    /**
     * Creates a Sphere and calls other member functions to set it up properly.
     * Is called if the file_ is 'sphere'.
     * @return A Mesh Component.
     */
    Mesh createSphere();

    /**
     * Creates a Plane and calls other member functions to set it up properly.
     * Is called if the file_ is 'plane'.
     * @return A Mesh Component.
     */
    Mesh createPlane();

    /**
     * Generates and store the collision of the Mesh currently being made.
     */
    void createCollision();

    /**
     * Generates and binds VAO and a VBO for the given Mesh.
     * Sends the vertex data to the GPU.
     * @return The VAO.
     */
    unsigned int openGLVertexBuffers();

    /**
     * Generates and binds a EAB for the given Mesh. This should only be ran if the Mesh has indices.
     */
    void openGLIndexBuffer();

    /**
     * Tries to read a TXT file. Assumes the location is Assets/Meshes.
     * Uses the member variable file_ as the file to read.
     * Fills the vertex and index vectors with data if the file is read correctly.
     */
    void readTXTFile();

    /**
     * Tries to read a OBJ file. Assumes the location is Assets/Meshes.
     * Uses the member variable file_ as the file to read.
     * Fills the vertex and index vectors with data if the file is read correctly.
     */
    void readOBJFile();

    /// Used to store all Mesh components when loaded from getMesh.
    std::unordered_map<std::string, Mesh> meshUMap_;

    /// Used to store all Collision components when created from getMesh. (Only if the Mesh is read from a .txt or a .obj)
    std::unordered_map<std::string, Collision> collisionUMap_;

    /// The filepath of the given Mesh to load. Used locally in functions instead of sending it around as a parameter.
    std::string file_ = "";

    /// All the vertices of the given Mesh to load. Used locally in functions instead of sending it around as a parameter.
    std::vector<Vertex> vertices_;

    /// All the indices of the given Mesh to load. Used locally in functions instead of sending it around as a parameter.
    std::vector<unsigned int> indices_;

    /// The singleton instance pointer.
    static ResourceFactory* instance_;
};

#endif // RESOURCEFACTORY_H
