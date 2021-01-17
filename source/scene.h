#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <thread>
#include <functional>
#include <cmath>

#include "ray.h"
#include "vector3d.h"
#include "plane.h"
#include "color.h"
#include "sphere.h"
#include "checkeredPlane.h"
#include "checkeredSphere.h"
#include "triangle.h"
#include "lightSource.h"
#include "material.h"
#include "libimage.h"
#include "pointLight.h"
#include "texturedSphere.h"
#include "libimage.h"

using namespace std;

/**
 * @brief A class for a 3d scene
 */
class scene
{
public:
    scene(int width = 1920, int height = 1080, plane camera = plane(vector3d(0, 0, 0), vector3d(1, 0, 0), vector3d(0, 1, 0)), double focalLength = 0.5);
    ~scene();
    void populate(istream &in);
    void render();
    void write(ofstream &out);
    void push_object_back(object3d *object); ///< @deprecated
    void push_light_back(lightSource *light);
    vector<object3d *> getObjects() const;
    vector<lightSource *> getLights() const;
    double getLightIntensity(const vector3d &pos);

    color trace(const ray &r, int depth = 5, double eps = 1e-3);
    double traceIntensity(const ray &r, int depth = 5, double eps = 1e-3);

    plane getCamera()
    {
        return camera;
    }

private:
    double minObjectDistance(const ray &r);
    void renderPart(int xMin, int xMax, int yMin, int yMax);
    int width, height;
    // color **image;
    libimage::Image image;
    plane camera;
    double focalLength;
    vector<object3d *> objects;
    vector<lightSource *> lights;
    material atmosphere;
};

#endif //SCENE_H
