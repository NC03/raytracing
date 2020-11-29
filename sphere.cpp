#include "sphere.h"

sphere::sphere(vector3d center, double radius) : center(center), radius(radius)
{
}
double sphere::getRadius()
{
    return radius;
}