#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "component.h"
#include "gltypes.h"
#include <string>

/**
 * The Mesh component contains information about a object read from a file and how it should be drawn.
 * You need to use a ResourceFactory to create a Mesh component or load in a valid QJsonObject.
 */
struct Mesh : public Component
{

    /**
     * Default constructor.
     */
    Mesh() = default;

    /**
     * A constructor taking in a QJsonObject.
     * @param Json - QJsonObject. Creates a Mesh component with the data in the QJsonObject. If the QJsonObject is not valid the component is constructed with default values.
     */
    Mesh(QJsonObject Json);

    /**
     * Makes a QJsonObject containing the component data.
     * @return Returns a QJsonObject
     */
    QJsonObject toJson() override;
    /**
     * Overrides the data in the component with the data in the QJsonObject.
     * The QJsonObject needs to be in a valid Json format. Otherwise nothing is overridden.
     * @param Json - QJsonObject
     */
    void fromJson(QJsonObject Json) override;

    /// Vertex Array Object. Which ID this Mesh has. Used to locate the Vertex data on the GPU.
    GLuint VAO_{0};

    /// The number of vertices in the Mesh.
    GLuint verticeCount_{0};

    /// The number of indices in the Mesh.
    GLuint indiceCount_{0};

    /// The way the mesh should be drawn with glDrawArray or glDrawElements.
    GLenum drawType_{0};

    /// Controls whether the Mesh should be visible or not.
    bool isVisible_{true};

    /// Controls whether the Mesh should be affected by Frustum Calling or not.
    bool isAffectedByFrustum_{true};

    /// The relative filepath of the Mesh. Assumes the location is Assets/Meshes.
    std::string filepath_ = "";

};

#endif // MESHCOMPONENT_H
