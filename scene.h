#include <iostream>
#include <fstream>
#include <vector>

#include "ray.h"
#include "vector3d.h"
#include "plane.h"
#include "color.h"
#include "sphere.h"
#include "checkeredPlane.h"

#ifndef SCENE_H
#define SCENE_H

class scene
{
public:
    scene(int width = 1920, int height = 1080, plane camera = plane(vector3d(0, 0, 0), vector3d(1, 0, 0), vector3d(0, 1, 0)), double focalLength = 0.5);
    ~scene();
    void populate(istream &in);
    void render();
    void write(ostream &out);

private:
    int width, height;
    color **image;
    plane camera;
    double focalLength;
    vector<object3d *> objects;
};

#endif //SCENE_H