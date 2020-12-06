#include "plane.h"

#ifndef CHECKEREDPLANE_H
#define CHECKEREDPLANE_H

class checkeredPlane : public plane
{
public:
    checkeredPlane(vector3d pos, vector3d u, vector3d v, double width = 5, double height = 5, color c1 = color(255, 255, 255), color c2 = color(0, 0, 0)) : plane(pos, u, v), width(width), height(height), c1(c1), c2(c2)
    {
    }

    virtual color getColor(const ray &r)
    {
        vector3d point = r.eval(intersectDistance(r));
        vector3d planar = point - getPoint();
        double x = planar.dot(getVector1()) / getVector1().magnitude();
        double y = planar.dot(getVector2()) / getVector2().magnitude();
        bool even = (static_cast<int>(x / width) + static_cast<int>(y / height)) % 2 == 0;
        if (even)
        {
            return c1;
        }
        else
        {
            return c2;
        }
    }

private:
    double width, height;
    color c1, c2;
};

#endif //CHECKEREDPLANE_H