#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>

#include "vector3d.h"
#include "color.h"
#include "ray.h"
#include "object3d.h"

/**
 * @brief 3d spheres
 */
class sphere : public object3d
{
public:
    sphere(vector3d center, double radius, color c = color(255, 0, 0));
    
    double getRadius() const;
    vector3d getPosition() const;
    friend ostream &operator<<(ostream &out, const sphere &s);
    color getColor() const;

    virtual bool intersects(const ray &r) const;
    virtual double intersectDistance(const ray &r) const;
    virtual vector3d normal(const ray& r) const;
    virtual color getColor(const ray &r) const;
    virtual void print(ostream &out) const;

private:
    vector3d center;
    double radius;
    color objColor;
};

#endif //SPHERE_H