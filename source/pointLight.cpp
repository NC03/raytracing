#include "pointLight.h"

pointLight::pointLight(vector3d r) : position(r)
{
}

double pointLight::intensityValue()
{
    return 1e4;
}
color pointLight::getColor()
{
    return color(255, 255, 255);
}
vector3d pointLight::getPosition()
{
    return position;
}