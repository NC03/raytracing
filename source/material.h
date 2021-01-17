#ifndef MATERIAL_H
#define MATERIAL_H

#include <cmath>

/**
 * @brief NOT DOCUMENTED
 */
class material
{
public:
    material(double kr = 0.125, double kt = 0, double density = 1) : reflectedCoefficient(kr), transmittedCoefficient(kt), density(density)
    {
    }

    

    double getReflectedCoefficient()
    {
        return reflectedCoefficient;
    }
    double getTransmittedCoefficient()
    {
        return transmittedCoefficient;
    }
    double getDensity()
    {
        return density;
    }

private:
    double reflectedCoefficient;
    double transmittedCoefficient;
    double density;

    /*
    ambient color reflection
    diffuse color reflection
    specular color reflection
    shininess (blurriness)
    emissive color intensity
    */
};

#endif //MATERIAL_H