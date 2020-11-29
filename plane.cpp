#include "plane.h"

ostream &operator<<(ostream &out, const plane &p)
{
    return out << p.point << " + u" << p.u << " + v" << p.v;
}
plane::plane(vector3d point, vector3d u, vector3d v) : point(point), u(u.normalize()), v(v.normalize())
{
}
