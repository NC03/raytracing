#include "checkeredSphere.h"

checkeredSphere::checkeredSphere(vector3d pos, double r, vector3d n, vector3d s, double width, double height, color c1, color c2) : sphere(pos, r), north(n.normalize()), start((s - n * (s.dot(n) / n.magnitude())).normalize()), width(width), height(height), c1(c1), c2(c2)
{
}

color checkeredSphere::getColor(const ray &r)
{
    vector3d point = r.eval(intersectDistance(r));
    vector3d spherical = point - getPosition();
    double z = spherical.dot(north);
    double x = spherical.dot(start);
    double y = spherical.dot(north.cross(start));

    double phi = asin(z / getRadius());
    double theta = asin(y / cos(phi) / getRadius());

    if (x < 0)
    {
        theta = 180 - theta;
    }

    bool even = (static_cast<int>(theta / width) + static_cast<int>(phi / height)) % 2 == 0;
    // bool even = (static_cast<int>(phi / height) % 2) == 0;
    if (even)
    {
        return c1;
    }
    else
    {
        return c2;
    }
}
