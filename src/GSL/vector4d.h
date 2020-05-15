#ifndef VECTOR4D_H
#define VECTOR4D_H

#include "gltypes.h"
#include <cmath>
#include <iostream>
#include <cassert>

namespace gsl
{

class Vector3D;

class Vector4D
{
public:
    //Constructors
    Vector4D(GLfloat x_in = 0.f, GLfloat y_in = 0.f, GLfloat z_in = 0.f, GLfloat w_in = 0.f);
    Vector4D(Vector3D vec3_in, GLfloat w_in);
    Vector4D(const Vector3D &vec3_in);
    Vector4D(const int v);
    Vector4D(const double v);

    // divide x, y, z on w
    void clipInvNormalize();
    void clipNormalize();

    //Operators:
    const Vector4D& operator=(const Vector4D &rhs);     // v = v
    Vector4D operator+(const Vector4D &rhs) const;      // v + v
    Vector4D operator-(const Vector4D &rhs) const;      // v - v
    Vector4D& operator+=(const Vector4D &rhs);          // v += v
    Vector4D& operator-=(const Vector4D &rhs);          // v -= v
    Vector4D operator-() const;                     // -v
    Vector4D operator*(GLfloat rhs) const;          // v * f
    //Vec4 operator*(Matrix4x4 q) const;        // v * m

    GLfloat& operator[](const int index)
    {
        assert(index <4 && index >=0);

        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        }
        return x;   //to silence compiler warnings
    }

    //Functions:
    GLfloat length();
    Vector3D toVector3D();
    void normalize();
    Vector4D normalized();
    static GLfloat dot(const Vector4D &v1, const Vector4D &v2);

    void rotateX(GLfloat angle);
    void rotateY(GLfloat angle);
    void rotateZ(GLfloat angle);

    //Getters and setters
    GLfloat getX() const;
    void setX(const GLfloat &value);

    GLfloat getY() const;
    void setY(const GLfloat &value);

    GLfloat getZ() const;
    void setZ(const GLfloat &value);

    GLfloat getW() const;
    void setW(const GLfloat &value);

    Vector3D getXYZ() const;

    //Friend functions
    friend std::ostream& operator<<(std::ostream &output, const Vector4D &rhs )
    {
        output << "X = " << rhs.x << ", Y = " << rhs.y <<
                  ", Z = " << rhs.z << ", W = " << rhs.w;
        return output;
    }

    //        private:
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
};

} //namespace

#endif // VECTOR4D_H
