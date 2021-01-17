#ifndef CHECKEREDSPHERE_H
#define CHECKEREDSPHERE_H

#include <iostream>
#include <cmath>

#include "sphere.h"

/**
 * @brief NOT DOCUMENTED
 */
class checkeredSphere : public sphere
{
public:
    checkeredSphere(vector3d pos, double r, vector3d n, vector3d s, double width = 2 * M_PI / 10, double height = M_PI / 10, color c1 = color(255, 255, 255), color c2 = color(0, 0, 0));

    using sphere::getColor;
    virtual color getColor(const ray &r) const;

private:
    vector3d north, start;
    double width, height;
    color c1, c2;
};

#endif //CHECKEREDSPHERE_H