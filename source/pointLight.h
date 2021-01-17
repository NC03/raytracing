#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <iostream>

#include "lightSource.h"
#include "color.h"
#include "vector3d.h"

/**
 * @brief Not Documented
 */
class pointLight : public lightSource
{
public:
    pointLight(vector3d r, double i);

    virtual double intensityValue(const ray& r);
    virtual double intensityValue();
    virtual color getColor();
    virtual vector3d getPosition();
    virtual void print(ostream& out) const;

private:
    vector3d position;
    double intensity;
};

#endif //POINTLIGHT_H