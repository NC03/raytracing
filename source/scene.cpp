#include "scene.h"

/**
 * scene constructor
 * 
 * @note There is no default constructor with 0 arguments
 * 
 */
scene::scene(int width, int height, plane camera, double focalLength) : width(width), height(height), camera(camera), focalLength(focalLength)
{
    image = libimage::Image(width, height, 255);
    cout << image << endl;
    // image = new color *[height];
    // for (int i = 0; i < height; i++)
    // {
    //     image[i] = new color[width];
    // }
}

/**
 * Scene Destructor
 * 
 */
scene::~scene()
{
    // for (int i = 0; i < height; i++)
    // {
    //     delete[] image[i];
    // }
    // delete[] image;
    while (objects.size() > 0)
    {
        object3d *last = objects.back();
        objects.pop_back();
        delete last;
    }
}

enum class Entry
{
    SPHERE,
    PLANE,
    CHECKEREDPLANE,
    CHECKEREDSPHERE,
    CAMERA,
    TRIANGLE,
    NONE
};
istream &operator>>(istream &in, Entry &e)
{
    string key;
    in >> key;
    // cout << key << endl;
    if (key == "SPHERE")
    {
        e = Entry::SPHERE;
    }
    else if (key == "PLANE")
    {
        e = Entry::PLANE;
    }
    else if (key == "CHECKEREDPLANE")
    {
        e = Entry::CHECKEREDPLANE;
    }
    else if (key == "CAMERA")
    {
        e = Entry::CAMERA;
    }
    else if (key == "CHECKEREDSPHERE")
    {
        e = Entry::CHECKEREDSPHERE;
    }
    else if (key == "TRIANGLE")
    {
        e = Entry::TRIANGLE;
    }
    else
    {
        e = Entry::NONE;
    }
    return in;
}
ostream &operator<<(ostream &out, Entry &e)
{
    switch (e)
    {
    case Entry::SPHERE:
        return out << "SPHERE";
    case Entry::PLANE:
        return out << "PLANE";
    case Entry::CHECKEREDPLANE:
        return out << "CHECKEREDPLANE";
    case Entry::CAMERA:
        return out << "CAMERA";
    case Entry::NONE:
        return out << "NONE";
    case Entry::CHECKEREDSPHERE:
        return out << "CHECKEREDSPHERE";
    case Entry::TRIANGLE:
        return out << "TRIANGLE";
    }
}

/**
 * Populates the scene object from the istream
 * @param in A reference to the istream input
 * 
 */
void scene::populate(istream &in)
{
    bool flag = false;
    Entry e;
    while (!flag)
    {
        in >> e;
        if (e == Entry::CAMERA)
        {
            double px, py, pz, ux, uy, uz, vx, vy, vz, f;
            in >> px >> py >> pz >> ux >> uy >> uz >> vx >> vy >> vz >> f;
            camera = plane(vector3d(px, py, pz), vector3d(ux, uy, uz), vector3d(vx, vy, vz));
            focalLength = f;
            cout << camera << endl;
        }
        else if (e == Entry::PLANE)
        {
            double px, py, pz, ux, uy, uz, vx, vy, vz;
            int r, g, b;
            in >> px >> py >> pz >> ux >> uy >> uz >> vx >> vy >> vz >> r >> g >> b;
            objects.push_back(new plane(vector3d(px, py, pz), vector3d(ux, uy, uz), vector3d(vx, vy, vz), color(r, g, b)));
        }
        else if (e == Entry::CHECKEREDPLANE)
        {

            double px, py, pz, ux, uy, uz, vx, vy, vz, w, h;
            int r1, g1, b1, r2, g2, b2;
            in >> px >> py >> pz >> ux >> uy >> uz >> vx >> vy >> vz >> r1 >> g1 >> b1 >> r2 >> g2 >> b2 >> w >> h;
            objects.push_back(new checkeredPlane(vector3d(px, py, pz), vector3d(ux, uy, uz), vector3d(vx, vy, vz), w, h, color(r1, g1, b1), color(r2, g2, b2)));
        }
        else if (e == Entry::SPHERE)
        {
            double px, py, pz, r;
            in >> px >> py >> pz >> r;
            sphere *sphereTemp = new sphere(vector3d(px, py, pz), r);
            objects.push_back(sphereTemp);
        }
        else if (e == Entry::CHECKEREDSPHERE)
        {
            double px, py, pz, nx, ny, nz, sx, sy, sz, r;
            int r1, g1, b1, r2, g2, b2;
            in >> px >> py >> pz >> r >> nx >> ny >> nz >> sx >> sy >> sz >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
            objects.push_back(new checkeredSphere(vector3d(px, py, pz), r, vector3d(nx, ny, nz), vector3d(sx, sy, sz), 2 * M_PI / 20, M_PI / 10, color(r1, g1, b1), color(r2, g2, b2)));
        }
        else if (e == Entry::TRIANGLE)
        {
            double v1x, v1y, v1z, v2x, v2y, v2z, v3x, v3y, v3z;
            int r, g, b;
            in >> v1x >> v1y >> v1z >> v2x >> v2y >> v2z >> v3x >> v3y >> v3z >> r >> g >> b;
            objects.push_back(new triangle(vector3d(v1x, v1y, v1z), vector3d(v2x, v2y, v2z), vector3d(v3x, v3y, v3z), color(r, g, b)));
        }
        else if (e == Entry::NONE)
        {
            flag = true;
            break;
        }
        cout << e << endl;
        if (objects.size() > 0)
        {
            cout << *objects.back() << endl;
        }
    }
}

/**
 * Writes the image data to the ostream
 * @param out A reference to the ostream where the image data is written
 * 
 */
void scene::write(ofstream &out)
{
    // cout << "write" << endl;
    // out << "P3\n"
    //     << width << " " << height << "\n256\n";
    // for (int i = 0; i < height; i++)
    // {
    //     for (int j = 0; j < width; j++)
    //     {
    //         color c = image[i][j];
    //         out << c.getRed() << " " << c.getGreen() << " " << c.getBlue() << " ";
    //     }
    //     out << endl;
    // }
    image.write(out, libimage::Image::Format::PPM);
}

void scene::push_object_back(object3d *object)
{
    objects.push_back(object);
}

/**
 * Runs the computations to render the scene
 */
void scene::render()
{
    // renderPart(0,width,0,height);

    vector<thread *> threads;
    void (scene::*func)(int, int, int, int) = &scene::renderPart;
    int N = 10;
    for (int i = 0; i < N; i++)
    {
        thread *t = new thread(func, this, 0, width, height * i / N, height * (i + 1) / N);
        threads.push_back(t);
    }
    for (int i = 0; i < 10; i++)
    {
        threads[i]->join();
        delete threads[i];
    }
}

libimage::Color convert(color c)
{
    return libimage::Color(c.getRed(), c.getGreen(), c.getBlue(), 255, 255);
}

void scene::renderPart(int xMin, int xMax, int yMin, int yMax)
{
    vector3d start = camera.getPoint() + camera.getVector1().cross(camera.getVector2()).normalize() * -1 * focalLength;
    for (int i = yMin; i < yMax; i++)
    {
        for (int j = xMin; j < xMax; j++)
        {
            double x = j - width / 2, y = i - height / 2;
            x /= max(width, height);
            y /= -1 * max(width, height);

            double ds = 1.0 / max(width, height), dr = ds / 4;
            color colors[4];
            for (int k = 0; k < 4; k++)
            {

                // image[i][j] = color();
                vector3d pos = camera.getPoint() + (x + dr * cos(M_PI * k / 2.0)) * camera.getVector1() + (y + dr * sin(M_PI * k / 2.0)) * camera.getVector2();
                ray r(start, pos - start);
                colors[k] = trace(r);
            }
            image(j, i) = convert(color::average(colors, 4));
            // image[i][j] = color::average(colors, 4);
        }
    }
}

vector<object3d *> scene::getObjects() const
{
    return objects;
}
vector<lightSource *> scene::getLights() const
{
    return lights;
}

ray reflectedRay(const ray &r, const vector3d &pos, const vector3d &normal)
{
    vector3d reflect = -2 * r.getDir().dot(normal) * normal + r.getDir();
    return ray(pos, reflect);
}
ray transmittedRay(const ray &r, const vector3d &pos, const vector3d &normal, material atmosphere, material inner)
{
    double a = acos(reflectedRay(r, pos, normal).getDir().dot(normal));
    double angle = asin(atmosphere.getDensity() / inner.getDensity() * sin(a));
    vector3d dir = (r.getDir().dot(normal) * normal + r.getDir()).normalize();
    vector3d nHat = -1 * normal;
    vector3d transmit = cos(angle) * nHat + sin(angle) * dir;
    //TODO implement Snell's law with total internal reflection
    return ray(pos, transmit);
}

double scene::getIntensity(const vector3d &pos)
{
    double out = 0;
    for (int i = 0; i < lights.size(); i++)
    {
        ray r(pos, lights[i]->getPosition() - pos);
        double objDist = minObjectDistance(r);
        double lightDist = lights[i]->distance(pos);
        if (lightDist < objDist || objDist < 0)
        {
            out += lightSource::attenuate(lightDist) * lights[i]->intensityValue();
        }
    }
    return out;
}

double scene::minObjectDistance(const ray &r)
{
    double minDist = -1;
    for (int i = 0; i < objects.size(); i++)
    {
        object3d *obj = objects[i];
        if (obj->intersects(r) && (obj->intersectDistance(r) < minDist || minDist < 0))
        {
            minDist = obj->intersectDistance(r);
        }
    }
    return minDist;
}

double min(double a, double b)
{
    return a < b ? a : b;
}

color scene::trace(const ray &r, double eps)
{
    //TODO consider recursively tracing the reflected, transmitted, and other rays
    double minDist = -1;
    int minIdx = 0;
    for (int i = 0; i < objects.size(); i++)
    {
        object3d *obj = objects[i];
        if (obj->intersects(r) && (obj->intersectDistance(r) < minDist || minDist < 0))
        {
            minDist = obj->intersectDistance(r);
            minIdx = i;
        }
    }

    if (minDist < 0)
    {
        return color();
    }
    else
    {
        object3d *object = objects[minIdx];

        double dist = minDist;
        vector3d pos = r.eval(dist);
        vector3d normal = object->normal(r);
        if (normal.dot(r.getDir()) < 0)
        {
            normal = normal * -1;
        }
        double red, green, blue = 0;
        // ray reflected = reflectedRay(r, pos, object->normal(r));
        // ray transmitted = transmittedRay(r, pos, object->normal(r));
        // material m = object->getMaterial();
        double intensity = getIntensity(pos + normal * eps) * lightSource::attenuate(dist);
        // cout << intensity << endl;
        color c = object->getColor(r);
        red = min(c.getRed() * intensity, 255);
        green = min(c.getGreen() * intensity, 255);
        blue = min(c.getBlue() * intensity, 255);

        return c;
        return color(static_cast<int>(red), static_cast<int>(green), static_cast<int>(blue));
    }
}
void scene::push_light_back(lightSource *light)
{
    lights.push_back(light);
}