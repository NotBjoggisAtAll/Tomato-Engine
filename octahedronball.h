#ifndef OCTAHEDRONBALL_H
#define OCTAHEDRONBALL_H

#include "GSL/vector3d.h"
#include "gltypes.h"

class Vertex;

/**
 * This class is made to create a ball.
 */
class OctahedronBall
{
public:
    /**
    * Default constructor.
    * Takes in the number of recursion the ball should be made with.
    * @param n - int. Recursions.
    */
    OctahedronBall(int n=0);

    /**
     * Default deconstructor.
     */
    ~OctahedronBall() = default;

    /// The vertices of the ball.
    std::vector<Vertex> vertices_;

    /// The indices of the ball.
    std::vector<GLuint> indices_;

private:
    /// The number of recursions.
    GLint recursions_ = 0;

    /**
     * Function for helping making the ball.
     * @param v1
     * @param v2
     * @param v3
     */
    void makeTriangle(const gsl::Vector3D &v1, const gsl::Vector3D &v2, const gsl::Vector3D &v3);

    /**
     * Function for helping making the ball.
     * @param a
     * @param b
     * @param c
     * @param n
     */
    void subDivide(const gsl::Vector3D &a, const gsl::Vector3D &b, const gsl::Vector3D &c, GLint n);
    /**
     * Function for helping making the ball.
     */
    void makeUnitOctahedron();
};

#endif // OCTAHEDRONBALL_H
