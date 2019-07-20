#include "vector2d.h"
#include "vector3d.h"
#include <cmath>

namespace gsl
{
    Vector2D::Vector2D(GLfloat x_in, GLfloat y_in) : x{x_in}, y{y_in}
    {

    }

    Vector2D::Vector2D(const int v) : x{static_cast<GLfloat>(v)}, y{static_cast<GLfloat>(v)}
    {

    }

    Vector2D::Vector2D(const double v) : x{static_cast<GLfloat>(v)}, y{static_cast<GLfloat>(v)}
    {

    }

    const Vector2D& Vector2D::operator=(const Vector2D &rhs)
    {
        x = rhs.getX();
        y = rhs.getY();

        return *this;
    }

    Vector2D Vector2D::operator+(const Vector2D &rhs) const
    {
        return {x + rhs.getX(), y + rhs.getY()};
    }

    Vector2D Vector2D::operator-(const Vector2D &rhs) const
    {
        return {x - rhs.getX(), y - rhs.getY()};
    }

    Vector2D& Vector2D::operator+=(const Vector2D &rhs)
    {
        x += rhs.getX();
        y += rhs.getY();

        return *this;
    }

    Vector2D& Vector2D::operator-=(const Vector2D &rhs)
    {
        x -= rhs.getX();
        y -= rhs.getY();

        return *this;
    }

    Vector2D Vector2D::operator-() const
    {
        return {-x, -y};
    }

    Vector2D Vector2D::operator*(float lhs) const
    {
        return {x * lhs, y * lhs};
    }

    GLfloat Vector2D::length() const
    {
        return std::sqrt(std::pow(x, 2.f) + std::pow(y, 2.f));
    }

    void Vector2D::normalize()
    {
        GLfloat l = length();

        if (l > 0.f)
        {
            x = (x / l);
            y = (y / l);
        }
    }

    Vector2D Vector2D::normalized()
    {
        Vector2D normalized;
        GLfloat l = length();

        if (l > 0.f)
        {
            normalized.setX(x / l);
            normalized.setY(y / l);
        }

        return normalized;
    }

    GLfloat Vector2D::cross(const Vector2D &v1, const Vector2D &v2)
    {
        return std::abs((v1.getX() * v2.getY()) - (v1.getY() * v2.getX()));
    }

    GLfloat Vector2D::dot(const Vector2D  &v1, const Vector2D  &v2)
    {
        return ((v1.getX() * v2.getX()) + (v1.getY() * v2.getY()));
    }

    GLfloat Vector2D::getX() const
    {
        return x;
    }

    void Vector2D::setX(const GLfloat &value)
    {
        x = value;
    }

    GLfloat Vector2D::getY() const
    {
        return y;
    }

    void Vector2D::setY(const GLfloat &value)
    {
        y = value;
    }
} //namespace
