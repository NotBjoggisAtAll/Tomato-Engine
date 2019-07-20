#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "gltypes.h"
#include <cmath>
#include <iostream>

namespace gsl
{

class Vector2D
{
public:
    //Constructors
    Vector2D(GLfloat x_in = 0.f, GLfloat y_in = 0.f);
    Vector2D(const int v);
    Vector2D(const double v);

    //Operators
    Vector2D operator+(const Vector2D &rhs) const;      // v + v
    Vector2D operator-(const Vector2D &rhs) const;      // v - v
    Vector2D& operator+=(const Vector2D &rhs);          // v += v
    Vector2D& operator-=(const Vector2D &rhs);          // v -= v
    Vector2D operator-() const;                     // -v
    Vector2D operator*(GLfloat lhs) const;          // v * f
    const Vector2D& operator =(const Vector2D &rhs);    // v = v

    //Functions
    GLfloat length() const;
    void normalize();
    Vector2D normalized();
    static GLfloat cross(const Vector2D &v1, const Vector2D &v2);
    static GLfloat dot(const Vector2D &v1, const Vector2D &v2);

    //Getters and setters
    GLfloat getX() const;
    void setX(const GLfloat &value);

    GLfloat getY() const;
    void setY(const GLfloat &value);

    //Friend functions
    friend std::ostream& operator<<(std::ostream &output, const Vector2D &rhs)
    {
        output << "(" << rhs.x << "," << rhs.y << ")";
        return output;
    }

    GLfloat x;
    GLfloat y;
};

} //namespace

#endif // VECTOR2D_H
