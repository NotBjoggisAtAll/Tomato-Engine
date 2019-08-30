#ifndef JBAVECTOR4D_H
#define JBAVECTOR4D_H

#include <array>
#include <QDebug>
#include "vector3d.h"
namespace jba {

class Vector4D {
public:
    Vector4D()
    {
        for (unsigned int i = 0; i < 4; ++i)
        {
            mData[i] = 0;
        }
    }

    Vector4D(float xIn, float yIn, float zIn, float wIn)
    {
        setX(xIn);
        setY(yIn);
        setZ(zIn);
        setW(wIn);
    }

    Vector4D(Vector3D otherVector, float wIn=0.f)
    {
        setX(otherVector.x());
        setY(otherVector.y());
        setZ(otherVector.z());
        setW(wIn);
    }

    Vector3D ToVector3D() const { return Vector3D(getX(), getY(), getZ()); }

    Vector4D operator*(float constant) { return Vector4D(getX() * constant, getY() * constant, getZ() * constant, getW() * constant); }

    friend QDebug operator<<(QDebug d, const Vector4D& v)
    {
        return d << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ", " << v.getW() << ")";
    }

    float& operator[](unsigned int index) { return mData[index]; }
    float operator[](unsigned int index) const { return mData[index]; }


    float getX() const { return mData[0]; }
    float getY() const { return mData[1]; }
    float getZ() const { return mData[2]; }
    float getW() const { return mData[3]; }

    void setX(float value){ mData[0] = value; }
    void setY(float value){ mData[1] = value; }
    void setZ(float value){ mData[2] = value; }
    void setW(float value){ mData[3] = value; }

    std::array<float, 4> getData() const { return mData; }

    void setData(const std::array<float, 4> &value){ mData = value; }

private:
    std::array<float, 4> mData;

};
}


#endif // VECTOR4D_H
