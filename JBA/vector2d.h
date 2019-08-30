#ifndef JBAVECTOR2D_H
#define JBAVECTOR2D_H

#include "vector3d.h"
#include <QDebug>

namespace jba {

class Vector2D
{
public:
    Vector2D(){}
    Vector2D(float x, float y)
    {
        mData[0] = x;
        mData[1] = y;
    }
    Vector2D(float xy)
    {
        mData[0] = xy;
        mData[1] = xy;
    }


    const Vector2D& operator =(const Vector2D &otherVector)
    {
        mData[0] = otherVector.GetX();
        mData[1] = otherVector.GetY();
        return *this;
    }
    Vector2D operator +(const Vector2D &otherVector) const
    {
        return Vector2D(mData[0] + otherVector.GetX(), mData[1] + otherVector.GetY());
    }

    Vector2D operator -(const Vector2D &otherVector) const
    {
        return Vector2D(mData[0] - otherVector.GetX(), mData[1] - otherVector.GetY());

    }

    float operator *(const Vector2D &otherVector) const
    {
        return (mData[0] * otherVector.GetX()) + (mData[1] * otherVector.GetX());
    }

    Vector2D operator *(float constant) const
    {
        return Vector2D(mData[0] * constant, mData[1] * constant);
    }
    Vector3D operator ^ (const Vector2D& otherVector) const
    {
        float i, j, k;

        i = mData[1] * 0 - 0 * otherVector.GetY();
        j = mData[0] * 0 - 0 * otherVector.GetX();
        k = mData[0] * otherVector.GetY() - mData[1] * otherVector.GetX();

        return Vector3D(i,j,k);
    }

    float& operator[](unsigned int index) { return mData[index]; }
    float operator[](unsigned int index) const { return mData[index]; }

    float GetX() const { return mData[0]; }
    float GetY() const { return mData[1]; }

    void SetX(float value) { mData[0] = value; }
    void SetY(float value) { mData[1] = value; }

    Vector3D BarycentricCoordinates(const Vector2D &p1, const Vector2D &p2, const Vector2D &p3)
    {
        Vector2D p12 = p2 - p1;

        Vector2D p13 = p3 - p1;
        Vector3D n = p12 ^ p13;
        float areal_123 = n.length(); // dobbelt areal
        Vector3D baryc; // til retur. Husk
        // u
        Vector2D p = p2 - *this;
        Vector2D q = p3 - *this;
        n = p ^ q;
        baryc.setX(n.z()/areal_123);
        // v
        p = p3 - *this;
        q = p1 - *this;
        n = p ^ q;
        baryc.setY(n.z()/areal_123);
        // w
        p = p1 - *this;
        q = p2 - *this;
        n = p ^ q;
        baryc.setZ(n.z()/areal_123);
        return baryc;
    }

    friend QDebug operator<<(QDebug debug, const Vector2D& otherVector)
    {
        return debug << "(" << otherVector.GetX() << ", " << otherVector.GetY() << ")";
    }

private:

    std::array<float, 2> mData{};

};
}

#endif // VECTOR2D_H
