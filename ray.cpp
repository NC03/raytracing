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
bool ray::intersects(const sphere &s)
{
    double a = pow(dir.magnitude(), 2);
    double b = 2 * dir.dot(start - s.getPosition());
    double c = pow(s.getPosition().magnitude(), 2) + pow(start.magnitude(), 2) - pow(s.getRadius(), 2) - 2 * start.dot(s.getPosition());
    double discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant == 0)
    {
        double s = -b / (2 * a);
        return s >= 0;
    }
    else if (discriminant > 0)
    {
        double s1 = (-b + sqrt(discriminant)) / (2 * a), s2 = (-b - sqrt(discriminant)) / (2 * a);
        return (s1 >= 0) || (s2 >= 0);
    }
    else
    {
        return false;
    }
}
