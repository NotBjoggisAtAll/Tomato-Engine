#include "vector3d.h"
#include "math_constants.h"
#include "gsl_math.h"
#include <cmath>

namespace gsl
{

    Vector3D::Vector3D(GLfloat x_in, GLfloat y_in, GLfloat z_in) : x{x_in}, y{y_in}, z{z_in}
    {

    }


    Vector3D::Vector3D(const int v) : x{static_cast<float>(v)}, y{static_cast<float>(v)}, z{static_cast<float>(v)}
    {

    }


    Vector3D::Vector3D(const double v) : x{static_cast<float>(v)}, y{static_cast<float>(v)}, z{static_cast<float>(v)}
    {

    }


    const Vector3D& Vector3D::operator=(const Vector3D &rhs)
    {
        x = rhs.getX();
        y = rhs.getY();
        z = rhs.getZ();

        return *this;
    }


    Vector3D Vector3D::operator+(const Vector3D &rhs) const
    {
        return {x + rhs.getX(), y + rhs.getY(), z + rhs.getZ()};
    }


    Vector3D Vector3D::operator-(const Vector3D &rhs) const
    {
        return {x - rhs.getX(), y - rhs.getY(), z - rhs.getZ()};
    }


    Vector3D& Vector3D::operator+=(const Vector3D &rhs)
    {
        x += rhs.getX();
        y += rhs.getY();
        z += rhs.getZ();

        return *this;
    }


    Vector3D& Vector3D::operator-=(const Vector3D &rhs)
    {
        x -= rhs.getX();
        y -= rhs.getY();
        z -= rhs.getZ();

        return *this;
    }


    Vector3D Vector3D::operator-() const
    {
        return {-x, -y, -z};
    }


    Vector3D Vector3D::operator*(GLfloat rhs) const
    {
        return {x * rhs, y * rhs, z * rhs};
    }


    Vector3D Vector3D::operator^(const Vector3D &rhs) const
        {
            return {y * rhs.getZ() - z * rhs.getY(), z * rhs.getX() - x * rhs.getZ(), x * rhs.getY() - y * rhs.getX()};
    }


    GLfloat Vector3D::length() const
    {
        return std::sqrt(std::pow(x, 2.f) + std::pow(y, 2.f) + std::pow(z, 2.f));
    }


    void Vector3D::normalize()
    {
        GLfloat l = length();

        if (l > 0.f)
        {
            x = x / l;
            y = y / l;
            z = z / l;
        }
    }


    Vector3D Vector3D::normalized()
    {
        Vector3D normalized;
        GLfloat l = length();

        if (l > 0.f)
        {
            normalized.setX(x / l);
            normalized.setY(y / l);
            normalized.setZ(z / l);
        }

        return normalized;
    }


    Vector3D Vector3D::cross(const Vector3D &v1, const Vector3D &v2)
    {
        return {((v1.getY() * v2.getZ()) - (v1.getZ() * v2.getY())), ((v1.getZ() * v2.getX()) - (v1.getX() * v2.getZ())), ((v1.getX() * v2.getY()) - (v1.getY() * v2.getX()))};
    }


    GLfloat Vector3D::dot(const Vector3D &v1, const Vector3D &v2)
    {
        return ((v1.getX() * v2.getX()) + (v1.getY() * v2.getY()) + (v1.getZ() * v2.getZ()));
    }


    void Vector3D::rotateX(GLfloat angle)
    {
        Vector3D dir;
        angle = gsl::deg2rad(angle);

        dir.setX(x);
        dir.setY((y * std::cos(angle)) + (z * (-std::sin(angle))));
        dir.setZ((y * std::sin(angle)) + (z * std::cos(angle)));

        x = dir.getX();
        y = dir.getY();
        z = dir.getZ();
    }


    void Vector3D::rotateY(GLfloat angle)
    {
        Vector3D dir;
        angle = gsl::deg2rad(angle);

        dir.setX((x * std::cos(angle)) + (z * std::sin(angle)));
        dir.setY(y);
        dir.setZ((x * (-std::sin(angle))) + (z * std::cos(angle)));

        x = dir.getX();
        y = dir.getY();
        z = dir.getZ();
    }


    void Vector3D::rotateZ(GLfloat angle)
    {
        Vector3D dir;
        angle = gsl::deg2rad(angle);

        dir.setX((x * std::cos(angle)) + (y * (-std::sin(angle))));
        dir.setY((x * std::sin(angle)) + (y * std::cos(angle)));
        dir.setZ(z);

        x = dir.getX();
        y = dir.getY();
        z = dir.getZ();
    }

    GLfloat *Vector3D::xP()
    {
        return &x;
    }

    GLfloat *Vector3D::yP()
    {
        return &y;
    }

    GLfloat *Vector3D::zP()
    {
        return &z;
    }


    GLfloat Vector3D::getX() const
    {
        return x;
    }


    void Vector3D::setX(const GLfloat &value)
    {
        x = value;
    }


    GLfloat Vector3D::getY() const
    {
        return y;
    }


    void Vector3D::setY(const GLfloat &value)
    {
        y = value;
    }


    GLfloat Vector3D::getZ() const
    {
        return z;
    }


    void Vector3D::setZ(const GLfloat &value)
    {
        z = value;
    }

} //namespace
