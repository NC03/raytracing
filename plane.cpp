#include "plane.h"

ostream &operator<<(ostream &out, const plane &p)
{
    return out << p.point << " + u" << p.u << " + v" << p.v;
}
plane::plane(vector3d point, vector3d u, vector3d v) : point(point), u(u.normalize()), v((v - u.normalize() * (u.dot(v) / u.magnitude())).normalize())
{
    // cout << this->u << this->u.magnitude() << this->v << this->v.magnitude() << this->u.dot(this->v) << endl;//testing implementation of gramm-schmidt orthonormalization
}

vector3d plane::getPoint() const
{
    return point;
}
vector3d plane::getVector1() const
{
    return u;
}
vector3d plane::getVector2() const
{
    return v;
}

vector3d plane::getNormal()
{
    return (u.cross(v)).normalize();
}
