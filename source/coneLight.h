#ifndef CONELIGHT_H
#define CONELIGHT_H

class coneLight : public lightSource
{
    virtual ~lightSource()
    {
    }
    virtual double intensityValue() = 0;
    virtual color getColor() = 0;
    virtual double distance(vector3d r) = 0;
};

#endif //CONELIGHT_H