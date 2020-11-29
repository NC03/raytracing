#include "vector3d.h"

#ifndef RAY_H
#define RAY_H

class ray
{
public:
    ray(vector3d start, vector3d dir);

    friend ostream &operator<<(ostream &out, const ray &r);

private:
    vector3d start;
    vector3d dir;
};

#endif //RAY_H