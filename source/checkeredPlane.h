#ifndef CHECKEREDPLANE_H
#define CHECKEREDPLANE_H

#include <cmath>

#include "plane.h"

/**
 * @brief NOT DOCUMENTED
 */
class checkeredPlane : public plane
{
public:
    checkeredPlane(vector3d pos, vector3d u, vector3d v, double width = 5, double height = 5, color c1 = color(255, 255, 255), color c2 = color(0, 0, 0));

    using plane::getColor;
    virtual color getColor(const ray &r) const;

private:
    double width, height;
    color c1, c2;
};

#endif //CHECKEREDPLANE_H