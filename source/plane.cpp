#include "plane.h"
#include "scene.h"

ostream &operator<<(ostream &out, const plane &p)
{
    return out << p.point << " + u" << p.u << " + v" << p.v;
}
plane::plane(vector3d point, vector3d u, vector3d v, color c) : point(point), u(u.normalize()), v((v - u.normalize() * (u.dot(v) / u.magnitude())).normalize()), objColor(c)
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

vector3d plane::normal(const ray &r) const
{
    return normal();
}
vector3d plane::normal() const
{
    return (u.cross(v)).normalize();
}
bool plane::intersects(const ray &r) const
{
    return intersectDistance(r) >= 0;
}
double plane::intersectDistance(const ray &r) const
{
    vector3d n = normal();
    double t = (getPoint().dot(n) - r.getStart().dot(n)) / (r.getDir().dot(n));
    return t;
}
color plane::getColor(const ray &r) const
{
    return getColor();
}
color plane::getColor() const
{
    return objColor;
}
void plane::print(ostream &out) const
{
    out << point << " + u" << u << " + v" << v;
}