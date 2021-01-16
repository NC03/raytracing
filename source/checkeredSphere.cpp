#include "checkeredSphere.h"

/**
 * Constructor for checkeredSphere object
 * 
 * @param pos The vector3d position vector of the center of the sphere
 * @param r The radius of the sphere
 * @param n The vector pointing in the "north" direction of the sphere
 * @param s The vector pointing in the "start" direction of the sphere. Must be linearly independent from the "north" vector.
 * @param width The width of the tile in the longitude direction
 * @param height The height of the tile in the latitude direction
 * @param c1 The color of one of the tiles of the sphere
 * @param c2 The color of one of the tiles of the sphere
 * 
 */
checkeredSphere::checkeredSphere(vector3d pos, double r, vector3d n, vector3d s, double width, double height, color c1, color c2) : sphere(pos, r), north(n.normalize()), start((s - n * (s.dot(n) / n.magnitude())).normalize()), width(width), height(height), c1(c1), c2(c2)
{
}

color checkeredSphere::getColor(const ray &r) const
{
    vector3d point = r.eval(intersectDistance(r));
    vector3d spherical = point - getPosition();
    double z = spherical.dot(north);
    double x = spherical.dot(start);
    double y = spherical.dot(north.cross(start));

    double phi = asin(z / getRadius());
    double theta = atan(y / x);

    if (x < 0)
    {
        theta += M_PI;
    }
    while (theta < 0)
    {
        theta += 2 * M_PI;
    }
    while (theta > 2 * M_PI)
    {
        theta -= 2 * M_PI;
    }
    bool even = (static_cast<int>(floor(theta / width)) + static_cast<int>(floor(phi / height)) + 4) % 2 == 0;
    if (even)
    {
        return c1;
    }
    else
    {
        return c2;
    }
}
