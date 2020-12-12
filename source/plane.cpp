#include "plane.h"

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

vector3d plane::getNormal()
{
    return (u.cross(v)).normalize();
}
bool plane::intersects(const ray &r)
{
    return intersectDistance(r) >= 0;
}
double plane::intersectDistance(const ray &r)
{
    vector3d normal = getNormal();
    double t = (getPoint().dot(normal) - r.getStart().dot(normal)) / (r.getDir().dot(normal));
    return t;
}
ray plane::reflectedRay(const ray &r)
{
    vector3d pos = r.eval(intersectDistance(r));
    vector3d norm = getNormal();
    vector3d reflect = -2 * r.getDir().dot(norm) * norm + r.getDir();
    return ray(pos, reflect);
}
color plane::getColor(const ray &r)
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
