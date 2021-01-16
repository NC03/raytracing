#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "lightSource.h"
#include "color.h"
#include "vector3d.h"

class pointLight : public lightSource
{
public:
    pointLight(vector3d r);

    virtual double intensityValue();
    virtual color getColor();
    virtual vector3d getPosition();

private:
    vector3d position;
};

#endif //POINTLIGHT_H