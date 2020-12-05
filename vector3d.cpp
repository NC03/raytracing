#include "vector3d.h"

vector3d::vector3d(double x, double y, double z) : x(x), y(y), z(z)
{
}

double vector3d::getX() const
{
    return x;
}
double vector3d::getY() const
{
    return y;
}
double vector3d::getZ() const
{
    return z;
}

vector3d vector3d::operator+(const vector3d &other) const
{
    return vector3d(x + other.x, y + other.y, z + other.z);
}
vector3d vector3d::operator-(const vector3d &other) const
{
    return vector3d(x - other.x, y - other.y, z - other.z);
}
vector3d vector3d::operator*(double scalar) const
{
    return vector3d(x * scalar, y * scalar, z * scalar);
}
double vector3d::dot(const vector3d &other) const
{
    return x * other.x + y * other.y + z * other.z;
}
vector3d vector3d::cross(const vector3d &other) const
{
    return vector3d(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

ostream &operator<<(ostream &out, const vector3d &vec)
{
    string str = "[" + to_string(vec.x) + "," + to_string(vec.y) + "," + to_string(vec.z) + "]";
    return out << str;
}

vector3d vector3d::normalize() const
{
    return operator*(1 / magnitude());
}
double vector3d::magnitude() const
{
    return sqrt(x * x + y * y + z * z);
}
bool vector3d::operator==(const vector3d &vec)
{
    return (x == vec.x) && (y == vec.y) && (z == vec.z);
}
vector3d operator*(double scalar, const vector3d &vec)
{
    return vector3d(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}