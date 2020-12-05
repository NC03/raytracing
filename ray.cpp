#include "ray.h"

ray::ray(vector3d start, vector3d dir) : start(start), dir(dir.normalize())
{
}

ostream &operator<<(ostream &out, const ray &r)
{
    return out << r.start << " + t" << r.dir;
}

vector3d ray::getStart() const
{
    return start;
}
vector3d ray::getDir() const
{
    return dir;
}
vector3d ray::eval(double t) const
{
    return start + dir * t;
}