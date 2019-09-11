#include "innpch.h"
#include "octahedronball.h"
#include "vertex.h"
OctahedronBall::OctahedronBall(GLint n) : mRecursions{n}, mIndex{0}
{
    makeUnitOctahedron();
}

OctahedronBall::~OctahedronBall()
{
}

void OctahedronBall::makeTriangle(const gsl::Vector3D &v1, const gsl::Vector3D &v2, const gsl::Vector3D &v3)
{
    mVertices.push_back(Vertex(v1, v1, gsl::Vector2D(0.f, 0.f)));
    mVertices.push_back(Vertex(v2, v2, gsl::Vector2D(1.f, 0.f)));
    mVertices.push_back(Vertex(v3, v3, gsl::Vector2D(0.5f, 1.f)));

}

void OctahedronBall::subDivide(const gsl::Vector3D &a, const gsl::Vector3D &b, const gsl::Vector3D &c, GLint n)
{
    if (n > 0)
    {
        gsl::Vector3D v1 = a + b;
        v1.normalize();

        gsl::Vector3D v2 = a + c;
        v2.normalize();

        gsl::Vector3D v3 = c + b;
        v3.normalize();

        subDivide(a, v1, v2, n-1);
        subDivide(c, v2, v3, n-1);
        subDivide(b, v3, v1, n-1);
        subDivide(v3, v2, v1, n-1);
    }
    else
    {
        makeTriangle(a, b, c);
    }
}

void OctahedronBall::makeUnitOctahedron()
{
    gsl::Vector3D v0(0.f, 0.f, 1.f);
    gsl::Vector3D v1(1.f, 0.f, 0.f);
    gsl::Vector3D v2(0.f, 1.f, 0.f);
    gsl::Vector3D v3(-1.f, 0.f, 0.f);
    gsl::Vector3D v4(0.f, -1.f, 0.f);
    gsl::Vector3D v5(0.f, 0.f, -1.f);

    subDivide(v0, v1, v2, mRecursions);
    subDivide(v0, v2, v3, mRecursions);
    subDivide(v0, v3, v4, mRecursions);
    subDivide(v0, v4, v1, mRecursions);
    subDivide(v5, v2, v1, mRecursions);
    subDivide(v5, v3, v2, mRecursions);
    subDivide(v5, v4, v3, mRecursions);
    subDivide(v5, v1, v4, mRecursions);
}
