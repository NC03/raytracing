#include "scene.h"

/**
 * scene constructor
 * 
 * @note There is no default constructor with 0 arguments
 * 
 */
scene::scene(int width, int height, plane camera, double focalLength) : width(width), height(height), camera(camera), focalLength(focalLength)
{
    image = new color *[height];
    for (int i = 0; i < height; i++)
    {
        image[i] = new color[width];
    }
}

/**
 * Scene Destructor
 * 
 */
scene::~scene()
{
    for (int i = 0; i < height; i++)
    {
        delete[] image[i];
    }
    delete[] image;
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
void scene::write(ostream &out)
{
    cout << "write" << endl;
    out << "P3\n"
        << width << " " << height << "\n256\n";
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            color c = image[i][j];
            out << c.getRed() << " " << c.getGreen() << " " << c.getBlue() << " ";
        }
        out << endl;
    }
}

void scene::push_back(object3d *object)
{
    objects.push_back(object);
}

/**
 * Runs the computations to render the scene
 */
void scene::render()
{
    //renderPart(0,width,0,height)
    void (scene::*func)(int, int, int, int) = &scene::renderPart;

    thread t1(func, this, 0, width / 2, 0, height / 2), t2(func, this, width / 2, width, 0, height / 2), t3(func, this, 0, width / 2, height / 2, height), t4(func, this, width / 2, width, height / 2, height);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
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
                bool firstIntersect = true;
                double minDist = -1;
                image[i][j] = color();
                vector3d pos = camera.getPoint() + (x + dr * cos(M_PI * k / 2.0)) * camera.getVector1() + (y + dr * sin(M_PI * k / 2.0)) * camera.getVector2();
                ray r(start, pos - start);
                for (object3d *obj : objects)
                {
                    if (obj->intersects(r) && (firstIntersect || obj->intersectDistance(r) < minDist))
                    {
                        firstIntersect = false;
                        minDist = obj->intersectDistance(r);
                        colors[k] = obj->getColor(r);
                    }
                }
            }
            image[i][j] = color::average(colors, 4);
        }
    }
}