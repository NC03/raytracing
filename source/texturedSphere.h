#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

#include "sphere.h"

#ifndef TEXTUREDSPHERE_H
#define TEXTUREDSPHERE_H

class texturedSphere : public sphere
{
public:
    texturedSphere(vector3d pos, double r, vector3d n, vector3d s, int w, int h, string filePath);
    // ~texturedSphere();
    
    virtual color getColor(const ray &r);

private:
    vector3d north, start;
    int width, height;
    color c1, c2;
    color **image;
};

#endif //TEXTUREDSPHERE_H