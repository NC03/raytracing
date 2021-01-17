#ifndef RAY_H
#define RAY_H

#include "vector3d.h"

/**
 * @brief A class for 3d rays
 */
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