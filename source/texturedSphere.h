#ifndef TEXTUREDSPHERE_H
#define TEXTUREDSPHERE_H

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

#include "sphere.h"
#include "libimage.h"

class texturedSphere : public sphere
{
public:
    texturedSphere(vector3d pos, double r, vector3d n, vector3d s, string filePath);
    texturedSphere(vector3d pos, double r, vector3d n, vector3d s, libimage::Image img);

    // ~texturedSphere();

    using sphere::getColor;
    virtual color getColor(const ray &r) const;

private:
    vector3d north, start;
    int width, height;
    color c1, c2;
    libimage::Image image;
    // color **image;
};

#endif //TEXTUREDSPHERE_H