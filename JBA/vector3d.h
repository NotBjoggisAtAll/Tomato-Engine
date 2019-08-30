#ifndef JBAVECTOR3D_H
#define JBAVECTOR3D_H

#include <ostream>
#include <sstream>
#include "cmath"
#include <QDebug>
namespace jba {

class Vector3D
{
public:

    Vector3D()
    {
        for (auto& i : m_Data)
            i=0;
    }

    Vector3D(float xIn, float yIn, float zIn)
    {
        m_Data[0] = xIn;
        m_Data[1] = yIn;
        m_Data[2] = zIn;
    }
    Vector3D(float xyzIn)
    {
        for (auto& i : m_Data)
            i=xyzIn;
    }

    Vector3D cross(const Vector3D &otherVector){ return *this ^ otherVector;}

    static Vector3D cross(const Vector3D &vec1, const Vector3D &vec2){ return vec1 ^ vec2;}


    float dot(const Vector3D &otherVector){return *this * otherVector;}

    void normalize()
    {
        float len = length();
        if(length() == 0.0f)
            return;
        for(auto& i : m_Data)
            i /= len;
    }
    float length() const {return std::sqrt(*this * *this);}

    // Returns a pointer to the first value in data
    float *constData() const { return (float*)&m_Data[0]; }

    const Vector3D& operator = (const Vector3D& otherVector)
    {
        m_Data[0] = otherVector.x();
        m_Data[1] = otherVector.y();
        m_Data[2] = otherVector.z();
        return *this;
    }

    Vector3D operator + (const Vector3D& otherVector)const { return Vector3D(x() + otherVector.x(), y() + otherVector.y(), z() + otherVector.z()); }
    void operator +=(const Vector3D &otherVector) { *this = Vector3D(x()+otherVector.x(),y()+otherVector.y(),z()+otherVector.z()); }
    Vector3D operator - (const Vector3D& otherVector) const { return Vector3D(x()-otherVector.x(), y()-otherVector.y(), z()-otherVector.z()); }
    Vector3D operator -() const {return Vector3D(-x(),-y(),-z());}

    float operator * (const Vector3D& otherVector) const { return (x() * otherVector.x()) + (y() * otherVector.y()) + (z() * otherVector.z()); }
    Vector3D operator * (float constant) const { return Vector3D(x()*constant, y()*constant, z()*constant); }

    Vector3D operator ^ (const Vector3D& otherVector) const
    {
        float i, j, k;

        i = y()*otherVector.z() - z()*otherVector.y();
        j = z()*otherVector.x() - x()*otherVector.z();
        k = x()*otherVector.y() - y()*otherVector.x();

        return Vector3D(i,j,k);
    }

    float& operator[](unsigned int index) { return m_Data[index]; }
    float operator[](unsigned int index) const { return m_Data[index]; }

    friend QDebug operator<<(QDebug debug, const Vector3D& otherVector) {return debug << "(" << otherVector.x() << ", " << otherVector.y() <<  ", " << otherVector.z() << ")";}
    //TODO Overload read/write to file
    // Overload stream operators << and >>. Let the vector look like (1.0, 2.0, 3.0) when stored
    // on a text file.

    float x() const {return m_Data[0];}
    void setX(float value) { m_Data[0] = value; }

    float y() const {return m_Data[1];}
    void setY(float value) {m_Data[1] = value;}

    float z() const {return m_Data[2];}
    void setZ(float value) {m_Data[2] = value;}

    std::array<float, 3> getData() const { return m_Data; }
    void setData(const std::array<float, 3> &data) { m_Data = data; }

private:

    std::array<float, 3> m_Data = {{0,0,0}};
};
}

#endif // VECTOR3D_H
