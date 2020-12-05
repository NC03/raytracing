#include "sphere.h"

sphere::sphere(vector3d center, double radius) : center(center), radius(radius)
{
}
double sphere::getRadius() const
{
    return radius;
}
vector3d sphere::getPosition() const
{
    return center;
}
ostream &operator<<(ostream &out, const sphere &s)
{
    return out << "{radius:" + to_string(s.radius) + ",position: " << s.getPosition() << "}";
}
