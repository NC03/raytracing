#include <iostream>

#include "vector3d.h"
#include "color.h"
#include "ray.h"
#include "object3d.h"

#ifndef SPHERE_H
#define SPHERE_H

class sphere : public object3d
{
public:
    sphere(vector3d center, double radius, color c = color(255, 0, 0));
    virtual ~sphere(){
        
    }

    double getRadius() const;
    vector3d getPosition() const;
    friend ostream &operator<<(ostream &out, const sphere &s);
    color getColor() const;

    virtual bool intersects(const ray &r);
    virtual double intersectDistance(const ray &r);
    virtual ray reflectedRay(const ray &r);
    virtual color getColor(const ray &r);
    virtual void print(ostream &out) const;

private:
    vector3d center;
    double radius;
    color objColor;
};

#endif //SPHERE_H