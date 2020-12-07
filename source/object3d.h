#include "ray.h"
#include "color.h"

#ifndef OBJECT3D_H
#define OBJECT3D_H

class object3d
{
public:
    virtual ~object3d(){
        
    }
    /**
     * Determines whether the ray intersects the object3d
     * @return True if the ray intersects the object, otherwise False
     */
    virtual bool intersects(const ray &r) = 0;
    /**
     * Finds the "distance" from the source to intersection
     * @return The parameter of the ray for which evaluating the equation coincides with the object
     */
    virtual double intersectDistance(const ray &r) = 0;
    /**
     * Finds the ray that exits with the same angle as the incoming ray
     * PRECONDITION: The ray must intersect the object
     */
    virtual ray reflectedRay(const ray &r) = 0;
    /**
     * Finds the color of the object3d at the point of intersection with the ray
     * PRECONDITION: The ray must intersect the object
     */
    virtual color getColor(const ray &r) = 0;
};

#endif //OBJECT3D_H