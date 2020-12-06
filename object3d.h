#include "ray.h"
#include "color.h"

#ifndef OBJECT3D_H
#define OBJECT3D_H

class object3d
{
public:
    virtual ~object3d(){
        
    }
    virtual bool intersects(const ray &r) = 0;
    virtual double intersectDistance(const ray &r) = 0;
    virtual ray reflectedRay(const ray &r) = 0;
    virtual color getColor(const ray &r) = 0;
};

#endif //OBJECT3D_H