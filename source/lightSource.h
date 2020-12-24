#include "ray.h"
#include "color.h"
#include "object3d.h"

#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

class lightSource : public object3d
{
public:
    virtual ~lightSource()
    {
    }
    virtual double intensityValue() = 0;
    virtual color color() = 0;
    
};

#endif //LIGHTSOURCE_H