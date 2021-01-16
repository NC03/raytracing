#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "ray.h"
#include "color.h"
#include "object3d.h"
#include "vector3d.h"

class lightSource //: public object3d
{
public:
    virtual ~lightSource()
    {
    }
    virtual double intensityValue() = 0;
    virtual color getColor() = 0;
    double distance(vector3d r)
    {
        return (getPosition() - r).magnitude();
    }
    virtual vector3d getPosition() = 0;

    static double attenuate(double distance)
    {
        double a = 1;
        double b = 0;
        double c = 0;
        return 1.0 / (a + b * distance + c * pow(distance, 2));
    }
};

#endif //LIGHTSOURCE_H