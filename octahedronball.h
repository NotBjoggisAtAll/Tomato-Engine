#ifndef OCTAHEDRONBALL_H
#define OCTAHEDRONBALL_H

#include "vector3d.h"
#include "gltypes.h"

class Vertex;

class OctahedronBall{
public:
   OctahedronBall(int n=0);
   ~OctahedronBall();


   std::vector<Vertex> mVertices;   //This is usually not needed after object is made
   std::vector<GLuint> mIndices;    //This is usually not needed after object is made

   GLint mRecursions;
private:
   GLint mIndex;               //Used in recursion to build vertices


   void makeTriangle(const gsl::Vector3D &v1, const gsl::Vector3D &v2, const gsl::Vector3D &v3);
   void subDivide(const gsl::Vector3D &a, const gsl::Vector3D &b, const gsl::Vector3D &c, GLint n);
   void makeUnitOctahedron();
};

#endif // OCTAHEDRONBALL_H
