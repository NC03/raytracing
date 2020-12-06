#include "vector3d.h"
#include "object3d.h"

#ifndef PLANE_H
#define PLANE_H

class plane : public object3d
{
public:
    plane(vector3d point, vector3d u, vector3d v, color c=color(128,128,128));

    friend ostream &operator<<(ostream &out, const plane &p);

    vector3d getPoint() const;
    vector3d getVector1() const;
    vector3d getVector2() const;
    vector3d getNormal();

    color getColor() const;

    virtual bool intersects(const ray &r);
    virtual double intersectDistance(const ray &r);
    virtual ray reflectedRay(const ray &r);
    virtual color getColor(const ray &r);

private:
    vector3d point, u, v;
    color objColor;
};

#endif //PLANE_H