#include "checkeredPlane.h"

checkeredPlane::checkeredPlane(vector3d pos, vector3d u, vector3d v, double width, double height, color c1, color c2) : plane(pos, u, v), width(width), height(height), c1(c1), c2(c2)
{
}

color checkeredPlane::getColor(const ray &r) const
{
    vector3d point = r.eval(intersectDistance(r));
    vector3d planar = point - getPoint();
    double x = planar.dot(getVector1()) / getVector1().magnitude();
    double y = planar.dot(getVector2()) / getVector2().magnitude();
    bool even = (static_cast<int>(floor(x / width)) + static_cast<int>(floor(y / height)) + 4) % 2 == 0;
    if (even)
    {
        return c1;
    }
    else
    {
        return c2;
    }
}
