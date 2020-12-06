#include "sphere.h"

sphere::sphere(vector3d center, double radius, color c) : center(center), radius(radius), objColor(c)
{
}
double sphere::getRadius() const
{
    return radius;
}
vector3d sphere::getPosition() const
{
    return center;
}
ostream &operator<<(ostream &out, const sphere &s)
{
    return out << "{radius:" + to_string(s.radius) + ",position: " << s.getPosition() << "}";
}
color sphere::getColor() const
{
    return objColor;
}
bool sphere::intersects(const ray &r)
{
    double a = pow(r.getDir().magnitude(), 2);
    double b = 2 * r.getDir().dot(r.getStart() - getPosition());
    double c = pow(getPosition().magnitude(), 2) + pow(r.getStart().magnitude(), 2) - pow(getRadius(), 2) - 2 * r.getStart().dot(getPosition());
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
double sphere::intersectDistance(const ray &r)
{
    double a = pow(r.getDir().magnitude(), 2);
    double b = 2 * r.getDir().dot(r.getStart() - getPosition());
    double c = pow(getPosition().magnitude(), 2) + pow(r.getStart().magnitude(), 2) - pow(getRadius(), 2) - 2 * r.getStart().dot(getPosition());
    double discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant == 0)
    {
        double s = -b / (2 * a);
        return s;
    }
    else if (discriminant > 0)
    {
        double s1 = (-b + sqrt(discriminant)) / (2 * a), s2 = (-b - sqrt(discriminant)) / (2 * a);
        if(s1 >= 0 && s2 >= 0)
        {
            return min(s1,s2);
        }else if(s1 >= 0)
        {
            return s1;
        }else{
            return s2;
        }
    }
    else
    {
        return -1;
    }
}
ray sphere::reflectedRay(const ray &r)
{
    vector3d pos = r.eval(intersectDistance(r));
    vector3d norm = (pos - center).normalize();
    vector3d reflect = -2 * r.getDir().dot(norm) * norm + r.getDir();
    return ray(pos, reflect);
}
color sphere::getColor(const ray &r)
{
    return getColor();
}
