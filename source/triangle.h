#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <cmath>

#include "vector3d.h"
#include "object3d.h"
#include "plane.h"
#include "color.h"

/**
 * @brief NOT DOCUMENTED 3d triangles
 */
class triangle : public object3d
{
public:
    triangle(vector3d v1, vector3d v2, vector3d v3, color c = color(128, 128, 128));

    friend ostream &operator<<(ostream &out, const triangle &p);

    vector3d getVertex1() const;
    vector3d getVertex2() const;
    vector3d getVertex3() const;
    vector<vector3d> getVertices() const;
    plane getPlane() const;

    color getColor() const;

    virtual bool intersects(const ray &r) const;
    virtual double intersectDistance(const ray &r) const;
    virtual color getColor(const ray &r) const;
    virtual void print(ostream &out) const;
    virtual vector3d normal(const ray &r) const;
    vector3d normal() const;

private:
    vector3d vertex1, vertex2, vertex3;
    color objColor;
};

#endif //TRIANGLE_H