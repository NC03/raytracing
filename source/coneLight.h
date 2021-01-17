#ifndef CONELIGHT_H
#define CONELIGHT_H

#include <iostream>

#include "color.h"
#include "vector3d.h"
#include "lightSource.h"

/**
 * @brief NOT DOCUMENTED
 */
class coneLight : public lightSource
{
    coneLight(vector3d r, vector3d dir, double angle, double i);

    virtual double intensityValue(const ray &r) = 0;
    virtual color getColor() = 0;

    virtual vector3d getPosition();
    virtual void print(ostream &out) const;

private:
    vector3d position, direction;
    double angle, intensity;
};

#endif //CONELIGHT_H
