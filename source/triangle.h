#include <vector>
#include <cmath>

#include "vector3d.h"
#include "object3d.h"
#include "plane.h"
#include "color.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H

class triangle : public object3d
{
public:
    triangle(vector3d v1, vector3d v2, vector3d v3, color c=color(128,128,128));

    friend ostream &operator<<(ostream &out, const triangle &p);

    vector3d getVertex1() const;
    vector3d getVertex2() const;
    vector3d getVertex3() const;
    vector3d getNormal() const;
    vector<vector3d> getVertices() const;
    plane getPlane() const;

    color getColor() const;

    virtual bool intersects(const ray &r);
    virtual double intersectDistance(const ray &r);
    virtual ray reflectedRay(const ray &r);
    virtual color getColor(const ray &r);
    virtual void print(ostream &out) const;

private:
    vector3d vertex1, vertex2, vertex3;
    color objColor;
};

#endif //TRIANGLE_H