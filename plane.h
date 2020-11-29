#include "vector3d.h"

#ifndef PLANE_H
#define PLANE_H

class plane
{
public:
    plane(vector3d point, vector3d u, vector3d v);

    friend ostream& operator<<(ostream& out, const plane& p);

private:
    vector3d point, u, v;
};

#endif //PLANE_H