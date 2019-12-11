#ifndef VERTEX_H
#define VERTEX_H

#include "GSL/vector2d.h"
#include "GSL/vector3d.h"

/**
 * The class represents a Vertice (Vertex) in the world. It contains the position, a normal and a UV coordinate.
 */
class Vertex
{
public:
    /**
     * Default constructor.
     */
    Vertex() = default;

    /**
     * A constructor taking in the position and the normal using floats.
     * @param x - float.
     * @param y - float.
     * @param z - float.
     * @param r - float.
     * @param g - float.
     * @param b - float.
     */
    Vertex(float x, float y, float z, float r, float g, float b);

    /**
     * A constructor taking in the position, the normal and the UVs with gsl::Vector3D and gsl::Vector2D.
     * @param a - gsl::Vector3D
     * @param b - gsl::Vector3D
     * @param c - gsl::Vector2D
     */
    Vertex(gsl::Vector3D a, gsl::Vector3D b, gsl::Vector2D c);

    /**
     * Default deconstructor.
     */
    ~Vertex() = default;

    /**
     * Overloaded ostream operator which writes all vertex data on an open textfile stream.
     */
    friend std::ostream& operator<< (std::ostream&, const Vertex&);

    /**
     * Overloaded ostream operator which reads all vertex data from an open textfile stream.
     */
    friend std::istream& operator>> (std::istream&, Vertex&);

    gsl::Vector3D xyz_ = gsl::Vector3D(0);
    gsl::Vector3D normal_ = gsl::Vector3D(0);
    gsl::Vector2D uv_ = gsl::Vector2D(0);
};

#endif // VERTEX_H
