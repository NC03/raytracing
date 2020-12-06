#include "scene.h"

scene::scene(int width, int height, plane camera, double focalLength) : width(width), height(height), camera(camera), focalLength(focalLength)
{
    image = new color *[height];
    for (int i = 0; i < height; i++)
    {
        image[i] = new color[width];
    }
}
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
    NONE
};
istream &operator>>(istream &in, Entry &e)
{
    string key;
    in >> key;
    cout << key << endl;
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
    }
}
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
            cout << camera << f << endl;
        }
        else if (e == Entry::PLANE)
        {

            double px, py, pz, ux, uy, uz, vx, vy, vz;
            int r, g, b;
            in >> px >> py >> pz >> ux >> uy >> uz >> vx >> vy >> vz >> r >> g >> b;
            plane *planeTemp = new plane(vector3d(px, py, pz), vector3d(ux, uy, uz), vector3d(vx, vy, vz), color(r, g, b));
            cout << *planeTemp << endl;
            objects.push_back(planeTemp);
        }
        else if (e == Entry::CHECKEREDPLANE)
        {

            double px, py, pz, ux, uy, uz, vx, vy, vz;
            int r1, g1, b1, r2, g2, b2;
            in >> px >> py >> pz >> ux >> uy >> uz >> vx >> vy >> vz >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
            objects.push_back(new checkeredPlane(vector3d(px, py, pz), vector3d(ux, uy, uz), vector3d(vx, vy, vz), 5, 5, color(r1, g1, b1), color(r2, g2, b2)));
        }
        else if (e == Entry::SPHERE)
        {

            double px, py, pz, r;
            in >> px >> py >> pz >> r;
            sphere *sphereTemp = new sphere(vector3d(px, py, pz), r);
            cout << *sphereTemp << endl;
            objects.push_back(sphereTemp);
        }
        else if (e == Entry::CHECKEREDSPHERE)
        {
            double px, py, pz, nx, ny, nz, sx, sy, sz;
            int r1, g1, b1, r2, g2, b2, r;
            in >> px >> py >> pz >> r >> nx >> ny >> nz >> sx >> sy >> sz >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
            objects.push_back(new checkeredSphere(vector3d(px, py, pz), r, vector3d(nx, ny, nz), vector3d(sx, sy, sz), 2*M_PI/20, M_PI/10, color(r1, g1, b1), color(r2, g2, b2)));
        }
        else if (e == Entry::NONE)
        {
            flag = true;
        }
    }
    // const int MAX_LEN = 256;
    // char l[MAX_LEN];
    // while (!in.eof())
    // {
    //     in.getline(l, MAX_LEN);
    //     string line = l;
    //     try
    //     {
    //         regex r("(.*):(.*)");
    //         smatch sm;
    //         regex_match(line, sm, r);
    //         if (sm.size() == 3)
    //         {
    //             if (sm[1] == "camera")
    //             {
    //                 r = regex("p\\((.*+)\\)");
    //                 smatch m;
    //                 vector3d p(0, 0, 0), u(0, 0, 0), v(0, 0, 0);
    //             }
    //             else
    //             {
    //                 cout << sm[1] << sm[2] << endl;
    //             }
    //         }
    //     }
    //     catch (...)
    //     {
    //         cout << "Error with line: " << line << endl;
    //     }
    // }
    // objects.push_back(new checkeredPlane(vector3d(0, -5, 0), vector3d(1, 0, 1), vector3d(0, 0, 1)));
    // objects.push_back(new sphere(vector3d(0, 0, 2), 1));
    // objects.push_back(new sphere(vector3d(1, 0, 3), 1));
}
void scene::render()
{
    vector3d start = camera.getVector1().cross(camera.getVector2()).normalize() * -1 * focalLength;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
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