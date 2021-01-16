#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "ray.h"
#include "color.h"
#include "material.h"

class scene;

/**
 * @brief An abstract base class for all 3d objects in the scene
 */
class object3d
{
public:
    /**
     * Virtual destructor
     */
    virtual ~object3d()
    {
    }

    /**
     * Determines whether the ray intersects the object3d
     * @param r The ray to evaluate
     * @return True if the ray intersects the object, otherwise False
     */
    virtual bool intersects(const ray &r) const = 0;

    /**
     * Finds the "distance" from the source to intersection
     * @param r The ray to evaluate
     * @return The parameter of the ray for which evaluating the equation coincides with the object
     */
    virtual double intersectDistance(const ray &r) const = 0;

    /**
     * Finds the color of the object3d at the point of intersection with the ray
     * @param r The ray to evaluate
     * PRECONDITION: The ray must intersect the object
     */
    virtual color getColor(const ray &r) const = 0;

    /**
     * Overloaded stream insertion operator for object3d
     * @param out The reference to the ostream to insert the object in
     * @param o The object3d to insert
     * @return A reference to the ostream argument to allow chaining
     * 
     */
    friend ostream &operator<<(ostream &out, const object3d &o)
    {
        o.print(out);
        return out;
    }

    /**
     * Prints the current object to the ostream argument
     * @param out A reference to the ostream to print the object with
     */
    virtual void print(ostream &out) const = 0;

    /**
     * Finds the unit normal vector of the object3d at the point of intersection with the ray
     * @param r The ray to evaluate
     * PRECONDITION: The ray must intersect the object
     * POSTCONDITION: The magnitude of the vector3d object is 1 (it is a unit vector)
     */
    virtual vector3d normal(const ray &r) const = 0;

    /**
     * @return The material of the object3d
     */
    virtual material getMaterial() const
    {
        return material();
    }
};

#endif //OBJECT3D_H