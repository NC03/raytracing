#include "coneLight.h"

coneLight::coneLight(vector3d r, vector3d dir, double angle, double i) : position(r), direction(dir.normalize()), angle(angle), intensity(i)
{
}

double coneLight::intensityValue(const ray &r)
{
    double a = acos(-1 * r.getDir().dot(direction));
    if (a <= angle)
    {
        return intensity;
    }
    else
    {
        return 0;
    }
}
color coneLight::getColor()
{
    return color(255, 255, 255);
}

vector3d coneLight::getPosition()
{
    return position;
}
void coneLight::print(ostream &out) const
{
    out << position << " - " << intensity << " - " << angle << " - " << direction;
}
