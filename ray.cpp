#include "ray.h"

ray::ray(vector3d start, vector3d dir) : start(start), dir(dir.normalize())
{
}

ostream &operator<<(ostream &out, const ray &r)
{
    return out << r.start << " + t" << r.dir;
}
