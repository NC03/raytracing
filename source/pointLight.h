#include "lightSource.h"
#include "color.h"

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

class pointLight : public lightSource
{

    virtual double intensityValue();
    virtual color getColor();

};

#endif //POINTLIGHT_H