#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "gltypes.h"
#include <cmath>
#include <iostream>
#include <QDebug>
#include <QVector3D>

namespace gsl
{

class Vector3D
{
public:
    //Constructors
    Vector3D(GLfloat x_in = 0.f, GLfloat y_in = 0.f, GLfloat z_in = 0.f);
    Vector3D(const int v);
    Vector3D(const double v);

    //Operators
    const Vector3D& operator=(const Vector3D &rhs);     // v = v
    Vector3D operator+(const Vector3D &rhs) const;      // v + v
    Vector3D operator-(const Vector3D &rhs) const;      // v - v
    Vector3D& operator+=(const Vector3D &rhs);          // v += v
    Vector3D& operator-=(const Vector3D &rhs);          // v -= v
    Vector3D operator-() const;                     // -v
    Vector3D operator*(GLfloat rhs) const;          // v * f
    Vector3D operator^(const Vector3D& rhs) const; // v x v  - cross product

    //Functions
    GLfloat length() const;
    void normalize();
    Vector3D normalized();
    static Vector3D cross(const Vector3D &v1, const Vector3D &v2);
    static GLfloat dot(const Vector3D &v1, const Vector3D &v2);

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

    GLfloat *xP();
    GLfloat *yP();
    GLfloat *zP();


    //Friend functions
    friend std::ostream& operator<<(std::ostream &output, const Vector3D &rhs )
    {
        output << "X = " << rhs.x << ", Y = " << rhs.y << ", Z = " << rhs.z;
        return output;
    }

    //OEF: Adding these again to be able to debug easier. cout does not print until program is finished!
    friend QDebug operator<<(QDebug out, const Vector3D &rhs)
    {
        out << "(" << rhs.x << "," << rhs.y << "," << rhs.z << ")";
        return  out;
    }        //    QVector3D getQVector() const;   //for use with qDebug()

    QVector3D getQVector() const
    {
        return QVector3D(x, y, z);
    }   //for use with qDebug()

    //private:  //Making these public to avoid having to do things like setY(getY()+3) etc.
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

} //namespace

#endif // VECTOR3D_H
