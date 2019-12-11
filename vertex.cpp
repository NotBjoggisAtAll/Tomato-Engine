#include "vertex.h"

Vertex::Vertex(float x, float y, float z, float r, float g, float b)
{
    xyz_.setX(x);
    xyz_.setY(y);
    xyz_.setZ(z);

    normal_.setX(r);
    normal_.setY(g);
    normal_.setZ(b);
}

Vertex::Vertex(gsl::Vector3D a, gsl::Vector3D b , gsl::Vector2D c)
{
    xyz_ = a;
    normal_ = b;
    uv_ = c;
}

std::ostream& operator<< (std::ostream& os, const Vertex& v) {
    os << std::fixed;
    os << "(" << v.xyz_.getX() << ", " << v.xyz_.getY() << ", " << v.xyz_.getZ() << ") ";
    os << "(" << v.normal_.getX() << ", " << v.normal_.getY() << ", " << v.normal_.getZ() << ") ";
    os << "(" << v.uv_.getX() << ", " << v.uv_.getY() << ") ";
    return os;
}

std::istream& operator>> (std::istream& is, Vertex& v) {
    // needs 4 temps to get commas and parenthesis
    char temp, temp2, temp3, temp4;
    is >> temp >> v.xyz_.x >> temp2 >> v.xyz_.y >> temp3 >> v.xyz_.z >> temp4;
    is >> temp >> v.normal_.x >> temp2 >> v.normal_.y >> temp3 >> v.normal_.z >> temp4;
    is >> temp >> v.uv_.x >> temp2 >> v.uv_.y >> temp3;
    return is;
}
