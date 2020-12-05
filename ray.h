#include "vector3d.h"

#ifndef RAY_H
#define RAY_H

class ray
{
public:
    ray(vector3d start, vector3d dir);

    friend ostream &operator<<(ostream &out, const ray &r);
    vector3d getStart() const;
    vector3d getDir() const;
    vector3d eval(double t) const;

private:
    vector3d start;
    vector3d dir;
};

#endif //RAY_H