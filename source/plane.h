#ifndef PLANE_H
#define PLANE_H

#include <vector>

#include "vector3d.h"
#include "object3d.h"
#include "material.h"
#include "lightSource.h"

class scene;

class plane : public object3d
{
public:
    plane(vector3d point, vector3d u, vector3d v, color c = color(128, 128, 128));

    friend ostream &operator<<(ostream &out, const plane &p);

    vector3d getPoint() const;
    vector3d getVector1() const;
    vector3d getVector2() const;

    color getColor() const;

    virtual bool intersects(const ray &r) const;
    virtual double intersectDistance(const ray &r) const;
    virtual color getColor(const ray &r) const;
    virtual void print(ostream &out) const;
    virtual vector3d normal(const ray &r) const;
    vector3d normal() const;

private:
    vector3d point, u, v;
    color objColor;
    material m;
};

#endif //PLANE_H