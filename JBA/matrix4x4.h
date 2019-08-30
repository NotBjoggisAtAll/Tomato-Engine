#ifndef JBAMATRIX4X4_H
#define JBAMATRIX4X4_H

#include <array>
#include "vector4d.h"
#include "vector3d.h"
#include <QtMath>
#include <cmath>
#include <QDebug>

namespace jba {

class Matrix4x4
{

public:

    Matrix4x4() { setToIdentity(); }
    Matrix4x4(const Matrix4x4& otherMatrix) { *this = otherMatrix; }
    Matrix4x4(Matrix4x4& otherMatrix) { *this = otherMatrix; }

    void setToIdentity()
    {
        mData[0] = Vector4D(1,0,0,0);
        mData[1] = Vector4D(0,1,0,0);
        mData[2] = Vector4D(0,0,1,0);
        mData[3] = Vector4D(0,0,0,1);
    }

    Vector4D getRow(unsigned int index) const { return mData[index]; }

    Vector4D getColumn(unsigned int index) const
    {
        Vector4D VectorToReturn;

        for (unsigned int i = 0; i < 4; ++i)
        {
            VectorToReturn[i] = mData[i][index];
        }
        return VectorToReturn;
    }

    void setRow(unsigned int index, const Vector4D& otherVector) { mData[index] = otherVector; }

    void setColumn(unsigned int index, const Vector4D& otherVector)
    {
        for (unsigned int i = 0; i < 4; ++i)
        {
            mData[i][index] = otherVector[i];
        }
    }

    // Returns a pointer to the first value in data
    float *constData() const { return (float*)&mData[0]; }

    const Matrix4x4& operator=(const Matrix4x4& otherMatrix)
    {
        for (unsigned int i = 0; i < 4; ++i)
        {
            setRow(i, otherMatrix.getRow(i));
        }

        return *this;
    }

    Matrix4x4 operator *(float constant)
    {
        Matrix4x4 MatrixToReturn;
        for (unsigned int  i = 0; i < 4; ++i)
        {
            MatrixToReturn.mData[i] = mData[i] * constant;
        }
        return MatrixToReturn;
    }

    Vector4D operator *(const Vector4D& vector)
    {
        Vector4D VectorToReturn;
        float f;
        for (unsigned int i = 0; i < 4; ++i)
        {
            f = 0;
            for (unsigned int j = 0; j < 4; ++j)
            {
                f +=  mData[i][j] * vector[j];
            }
            VectorToReturn[i] = f;
        }
        return VectorToReturn;
    }

    Matrix4x4 operator *(Matrix4x4& otherMatrix)
    {
        Matrix4x4 MatrixToReturn;
        Vector4D vector;
        float f;
        for (unsigned int i = 0; i < 4; ++i)
        {
            for (unsigned int j = 0; j < 4; ++j)
            {
                f = 0;
                for (unsigned int k = 0; k < 4; ++k)
                {
                    f += mData[i][k] * otherMatrix.getColumn(j)[k];
                }
                vector[j] = f;
            }
            MatrixToReturn.setRow(i, vector);
        }
        return MatrixToReturn;
    }

    friend QDebug operator<<(QDebug debug, const Matrix4x4& matrix)
    {
        debug << " ";
        for (unsigned int i = 0; i < 4; ++i)
        {
            debug << matrix.mData[i] << "\n ";
        }
        return debug;
    }

    static Matrix4x4 transpose(const Matrix4x4& matrix)
    {
        Matrix4x4 MatrixToReturn;
        Vector4D vector;
        for (unsigned int i = 0; i < 4; ++i)
        {
            vector = matrix.getRow(i);
            MatrixToReturn.setColumn(i, vector);
        }
        return MatrixToReturn;
    }

    void translate(const float &x, const float &y, const float &z) { translate(Vector3D(x,y,z)); }
    void translate(const Vector3D &vector)
    {
        Matrix4x4 matrix;
        Vector4D v(vector, 1);

        matrix.setColumn(3, v);

        *this =  *this * matrix;
    }

    void rotate(float angle, float x, float y, float z) { rotate(angle, Vector3D(x,y,z)); }
    void rotate(float angle, const Vector3D& vector)
    {
        Vector4D v4d(vector, 1);
        Matrix4x4 m;

        if(vector.x() == 1.0f)
        {
            m.setRow(0, Vector4D(1, 0, 0, 0));
            m.setRow(1, Vector4D(0, std::cos(qDegreesToRadians(angle)), -std::sin(qDegreesToRadians(angle)), 0));
            m.setRow(2, Vector4D(0, std::sin(qDegreesToRadians(angle)),  std::cos(qDegreesToRadians(angle)), 0));
            m.setRow(3, Vector4D(0, 0, 0, 1));
        }
        else if(vector.y() == 1.0f)
        {
            m.setRow(0, Vector4D(std::cos(qDegreesToRadians(angle)), 0, std::sin(qDegreesToRadians(angle)), 0));
            m.setRow(1, Vector4D(0, 1, 0, 0));
            m.setRow(2, Vector4D(-std::sin(qDegreesToRadians(angle)), 0,std::cos(qDegreesToRadians(angle)), 0));
            m.setRow(3, Vector4D(0, 0, 0, 1));
        }
        else if(vector.z() == 1.0f)
        {
            m.setRow(0, Vector4D(std::cos(qDegreesToRadians(angle)), -std::sin(qDegreesToRadians(angle)), 0, 0));
            m.setRow(1, Vector4D(std::sin(qDegreesToRadians(angle)),  std::cos(qDegreesToRadians(angle)), 0, 0));
            m.setRow(2, Vector4D(0, 0, 1, 0));
            m.setRow(3, Vector4D(0, 0, 0, 1));
        }
        *this = *this * m;
    }

    void rotate(const Vector3D &vector)
    {
        Vector4D v4d(vector, 1);
        Matrix4x4 m;

        float xRad = qDegreesToRadians(vector.x());
        float yRad = qDegreesToRadians(vector.y());
        float zRad = qDegreesToRadians(vector.z());

        if(vector.x() > 0 || vector.x() < 0)
        {
            m.setRow(0, Vector4D(1, 0, 0, 0));
            m.setRow(1, Vector4D(0, std::cos(xRad), -std::sin(xRad), 0));
            m.setRow(2, Vector4D(0, std::sin(xRad),  std::cos(xRad), 0));
            m.setRow(3, Vector4D(0, 0, 0, 1));
        }
        else if(vector.y() > 0 || vector.y() < 0)
        {
            m.setRow(0, Vector4D(std::cos(yRad), 0, std::sin(yRad), 0));
            m.setRow(1, Vector4D(0, 1, 0, 0));
            m.setRow(2, Vector4D(-std::sin(yRad), 0,std::cos(yRad), 0));
            m.setRow(3, Vector4D(0, 0, 0, 1));
        }
        else if(vector.z() > 0 || vector.y() < 0)
        {
            m.setRow(0, Vector4D(std::cos(zRad), -std::sin(zRad), 0, 0));
            m.setRow(1, Vector4D(std::sin(zRad),  std::cos(zRad), 0, 0));
            m.setRow(2, Vector4D(0, 0, 1, 0));
            m.setRow(3, Vector4D(0, 0, 0, 1));
        }
        *this = *this * m;
    }


    void scale(const float &xyz) { scale(Vector3D(xyz)); }
    void scale(const float &x, const float &y, const float &z) { scale(Vector3D(x,y,z)); }
    void scale(const Vector3D &vector)
    {
        Matrix4x4 scaleMatrix;

        scaleMatrix.mData[0].setX(vector.x());
        scaleMatrix.mData[1].setY(vector.y());
        scaleMatrix.mData[2].setZ(vector.z());
        scaleMatrix.mData[3].setW(1);

        *this = *this * scaleMatrix;
    }

    void lookAt(const Vector3D &eye, const Vector3D &at, const Vector3D &up)
    {
        Vector3D v = up; //Camera Relative Up Vector
        v.normalize();

        Vector3D n = eye - at; //Direction Vector
        n.normalize();

        Vector3D u = v ^ n; //Right Vector
        u.normalize();

        v = n ^ u;
        v.normalize();

        Vector4D rU(u);
        Vector4D rV(v);
        Vector4D rN(n);

        setRow(0,rU);
        setRow(1,rV);
        setRow(2,rN);
        setRow(3, Vector4D(0,0,0,1));

        translate(-eye);
    }

    void perspective(float fov, float aspect, float n, float f)
    {
        float D2R = 3.14f / 180.0f;
        float yScale = 1.0f / std::tan(D2R * fov / 2);
        float xScale = yScale / aspect;
        float nearmfar = n - f;

        setRow(0, Vector4D(xScale,0,0,0));
        setRow(1, Vector4D(0,yScale,0,0));
        setRow(2, Vector4D(0,0,((f + n)/ nearmfar), -1));
        setRow(3, Vector4D(0,0, 2*f*n / nearmfar, 0));

    }

    void LU()
    {
        for (unsigned int k=0; k<3; k++)
        {
            // pivot(k); //LAG PIVOT
            // Ved radoperasjoner skal vi oppnå 0-ere under diagonalelementet
            // i alle rader nedenfor (altså kolonne k
            // Vi subtraherer et multiplum av k-te
            // rad fra radene nedenfor, nuller ut kolonner fra venstre
            for (unsigned int i=k+1; i<4; i++)
            {
                // Skal mult med denne og deretter trekke fra rad i
                // denne skal bli null og vi kan lagre faktoren her
                mData[i][k] = mData[i][k]/mData[k][k];
                for (unsigned int j=k+1; j<4; j++)
                {
                    // kolonnene til høyre for den som blir nullet ut
                    mData[i][j] = mData[i][j] - mData[i][k]*mData[k][j];
                }
            }
        }
    }

    Vector4D solve(Vector4D &b)
    {
        Vector4D x;
        for (unsigned int k=0; k<4; k++)
            for (unsigned int i=k+1; i<4; i++)
                b[i] = b[i]-mData[i][k]*b[k];
        for (unsigned int i=4-1; i>0; i--) {
            x[i] = b[i];
            for (unsigned int j=i+1; j<4; j++)
                x[i] = x[i] - mData[i][j]*x[j];
            x[i] = x[i]/mData[i][i];
        }
        return x;
    }

    Matrix4x4 inverseq(const double m[16], double invOut[16])
    {
        double inv[16], det;
        int i;

        inv[0] = m[5]  * m[10] * m[15] -
                m[5]  * m[11] * m[14] -
                m[9]  * m[6]  * m[15] +
                m[9]  * m[7]  * m[14] +
                m[13] * m[6]  * m[11] -
                m[13] * m[7]  * m[10];

        inv[4] = -m[4]  * m[10] * m[15] +
                m[4]  * m[11] * m[14] +
                m[8]  * m[6]  * m[15] -
                m[8]  * m[7]  * m[14] -
                m[12] * m[6]  * m[11] +
                m[12] * m[7]  * m[10];

        inv[8] = m[4]  * m[9] * m[15] -
                m[4]  * m[11] * m[13] -
                m[8]  * m[5] * m[15] +
                m[8]  * m[7] * m[13] +
                m[12] * m[5] * m[11] -
                m[12] * m[7] * m[9];

        inv[12] = -m[4]  * m[9] * m[14] +
                m[4]  * m[10] * m[13] +
                m[8]  * m[5] * m[14] -
                m[8]  * m[6] * m[13] -
                m[12] * m[5] * m[10] +
                m[12] * m[6] * m[9];

        inv[1] = -m[1]  * m[10] * m[15] +
                m[1]  * m[11] * m[14] +
                m[9]  * m[2] * m[15] -
                m[9]  * m[3] * m[14] -
                m[13] * m[2] * m[11] +
                m[13] * m[3] * m[10];

        inv[5] = m[0]  * m[10] * m[15] -
                m[0]  * m[11] * m[14] -
                m[8]  * m[2] * m[15] +
                m[8]  * m[3] * m[14] +
                m[12] * m[2] * m[11] -
                m[12] * m[3] * m[10];

        inv[9] = -m[0]  * m[9] * m[15] +
                m[0]  * m[11] * m[13] +
                m[8]  * m[1] * m[15] -
                m[8]  * m[3] * m[13] -
                m[12] * m[1] * m[11] +
                m[12] * m[3] * m[9];

        inv[13] = m[0]  * m[9] * m[14] -
                m[0]  * m[10] * m[13] -
                m[8]  * m[1] * m[14] +
                m[8]  * m[2] * m[13] +
                m[12] * m[1] * m[10] -
                m[12] * m[2] * m[9];

        inv[2] = m[1]  * m[6] * m[15] -
                m[1]  * m[7] * m[14] -
                m[5]  * m[2] * m[15] +
                m[5]  * m[3] * m[14] +
                m[13] * m[2] * m[7] -
                m[13] * m[3] * m[6];

        inv[6] = -m[0]  * m[6] * m[15] +
                m[0]  * m[7] * m[14] +
                m[4]  * m[2] * m[15] -
                m[4]  * m[3] * m[14] -
                m[12] * m[2] * m[7] +
                m[12] * m[3] * m[6];

        inv[10] = m[0]  * m[5] * m[15] -
                m[0]  * m[7] * m[13] -
                m[4]  * m[1] * m[15] +
                m[4]  * m[3] * m[13] +
                m[12] * m[1] * m[7] -
                m[12] * m[3] * m[5];

        inv[14] = -m[0]  * m[5] * m[14] +
                m[0]  * m[6] * m[13] +
                m[4]  * m[1] * m[14] -
                m[4]  * m[2] * m[13] -
                m[12] * m[1] * m[6] +
                m[12] * m[2] * m[5];

        inv[3] = -m[1] * m[6] * m[11] +
                m[1] * m[7] * m[10] +
                m[5] * m[2] * m[11] -
                m[5] * m[3] * m[10] -
                m[9] * m[2] * m[7] +
                m[9] * m[3] * m[6];

        inv[7] = m[0] * m[6] * m[11] -
                m[0] * m[7] * m[10] -
                m[4] * m[2] * m[11] +
                m[4] * m[3] * m[10] +
                m[8] * m[2] * m[7] -
                m[8] * m[3] * m[6];

        inv[11] = -m[0] * m[5] * m[11] +
                m[0] * m[7] * m[9] +
                m[4] * m[1] * m[11] -
                m[4] * m[3] * m[9] -
                m[8] * m[1] * m[7] +
                m[8] * m[3] * m[5];

        inv[15] = m[0] * m[5] * m[10] -
                m[0] * m[6] * m[9] -
                m[4] * m[1] * m[10] +
                m[4] * m[2] * m[9] +
                m[8] * m[1] * m[6] -
                m[8] * m[2] * m[5];

        det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

        if (det == 0)

            det = 1.0 / det;

        for (i = 0; i < 16; i++)
            invOut[i] = inv[i] * det;

    }

private:
    std::array<Vector4D, 4> mData;
};
}

#endif // MATRIX4X4_H
