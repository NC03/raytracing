#include<iostream>

#include "vector3d.h"

#ifndef SPHERE_H
#define SPHERE_H

class sphere
{
public:
    sphere(vector3d center, double radius);

    double getRadius() const;
    vector3d getPosition() const;
    friend ostream& operator<<(ostream& out, const sphere& s);

private:
    vector3d center;
    double radius;
};

#endif //SPHERE_H