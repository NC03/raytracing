#include "pointLight.h"

pointLight::pointLight(vector3d r, double i) : position(r), intensity(i)
{
}

double pointLight::intensityValue(const ray& r)
{
    return intensity;
}
double pointLight::intensityValue()
{
    return intensity;
}
color pointLight::getColor()
{
    return color(255, 255, 255);
}
vector3d pointLight::getPosition()
{
    return position;
}
void pointLight::print(ostream &out) const
{
    out << position << " - " << intensity;
}