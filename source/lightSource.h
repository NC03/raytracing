#include "ray.h"
#include "color.h"
#include "object3d.h"
#include "vector3d.h"

#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

class lightSource //: public object3d
{
public:
    virtual ~lightSource()
    {
    }
    virtual double intensityValue() = 0;
    virtual color getColor() = 0;
    virtual double distance(vector3d r) = 0;
};

#endif //LIGHTSOURCE_H