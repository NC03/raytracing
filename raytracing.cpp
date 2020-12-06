#include <iostream>
#include <fstream>
#include <vector>

#include "ray.h"
#include "vector3d.h"
#include "plane.h"
#include "color.h"
#include "sphere.h"
#include "checkeredPlane.h"
#include "scene.h"

using namespace std;

void print(color **image, int width, int height, ostream &out = cout);
void checkIntersect(ray r, plane p);
void checkIntersect(ray r, sphere s);
void populate(plane &camera, vector3d &start, vector<sphere> &spheres);

int main()
{
    // // const int WIDTH = 200;
    // // const int HEIGHT = 60;
    // const int WIDTH = 1920;
    // const int HEIGHT = 1080;
    // color **image = new color *[HEIGHT];
    // for (int i = 0; i < HEIGHT; i++)
    // {
    //     image[i] = new color[WIDTH];
    // }

    // plane camera(vector3d(0, 0, 0), vector3d(1, 0, 0), vector3d(0, 1, 0));
    // vector3d start = vector3d(0, 0, -0.6);
    // checkeredPlane p(vector3d(0, -5, 0), vector3d(1, 0, 1), vector3d(0, 0, 1));

    // vector<sphere> spheres;
    // populate(camera, start, spheres);

    // for (int i = 0; i < HEIGHT; i++)
    // {
    //     for (int j = 0; j < WIDTH; j++)
    //     {
    //         double x = j - WIDTH / 2, y = i - HEIGHT / 2;
    //         x /= max(WIDTH, HEIGHT);
    //         y /= -1 * max(WIDTH, HEIGHT);

    //         double ds = 1.0 / max(WIDTH, HEIGHT), dr = ds / 4;
    //         color colors[4];
    //         for (int k = 0; k < 4; k++)
    //         {
    //             bool intersect = false;
    //             double minDist = -1;
    //             image[i][j] = color();
    //             vector3d pos = camera.getPoint() + (x + dr * cos(M_PI * k / 2.0)) * camera.getVector1() + (y + dr * sin(M_PI * k / 2.0)) * camera.getVector2();
    //             ray r(start, pos - start);
    //             if (p.intersects(r) && (!intersect || p.intersectDistance(r) < minDist)) //TODO check
    //             {
    //                 intersect = true;
    //                 minDist = p.intersectDistance(r);
    //                 colors[k] = p.getColor(r);
    //             }
    //             for (sphere s : spheres)
    //             {
    //                 if (s.intersects(r) && (!intersect || s.intersectDistance(r) < minDist))
    //                 {
    //                     intersect = true;
    //                     minDist = s.intersectDistance(r);
    //                     colors[k] = s.getColor(r);
    //                 }
    //             }
    //         }
    //         image[i][j] = color::average(colors, 4);
    //     }
    // }

    // ofstream out("output/image.ppm");
    // print(image, WIDTH, HEIGHT, out);
    // out.close();

    // for (int i = 0; i < HEIGHT; i++)
    // {
    //     delete[] image[i];
    // }
    // delete[] image;

    // return 0;
    scene s;
    s.populate(cin);
    s.render();
    ofstream out("output/image.ppm");
    s.write(out);
    out.close();

    return 0;
}

void print(color **image, int width, int height, ostream &out)
{
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

void checkIntersect(ray r, plane p)
{
    cout << "ray: " << r << endl;
    cout << "plane: " << p << endl;
    vector3d normal = p.getNormal();
    double t = (p.getPoint().dot(normal) - r.getStart().dot(normal)) / (r.getDir().dot(normal));
    cout << t << ": " << r.eval(t) << endl;
}
void checkIntersect(ray r, sphere s)
{
    // cout << "ray: " << r << endl;
    // cout << "sphere: " << s << endl;
    double a = pow(r.getDir().magnitude(), 2);
    double b = 2 * (r.getStart().dot(r.getDir()) - r.getDir().dot(s.getPosition()));
    double c = pow(s.getPosition().magnitude(), 2) + pow(r.getStart().magnitude(), 2) - pow(s.getRadius(), 2) - 2 * r.getStart().dot(s.getPosition());
    double discriminant = pow(b, 2) - 4 * a * c;
    // cout << "eq: " << a << "t^2 + " << b << "t + " << c << endl;

    if (discriminant == 0)
    {
        double s = -b / (2 * a);
        // cout << "s: " << s << endl;
        if (s >= 0)
            cout << "true" << endl;
    }
    else if (discriminant > 0)
    {
        double s1 = (-b + sqrt(discriminant)) / (2 * a), s2 = (-b - sqrt(discriminant)) / (2 * a);
        // cout << "s1: " << s1 << endl;
        // cout << "s2: " << s2 << endl;
        if ((s1 >= 0) || (s2 >= 0))
            cout << "true" << endl;
    }
    else
    {
        // cout << "imaginary" << endl;
    }
    // cout << r.intersects(s) << endl;
}

void populate(plane &camera, vector3d &start, vector<sphere> &spheres)
{
    camera = plane(vector3d(0, 0, 0), vector3d(1, 0, 0), vector3d(0, 1, 0));
    start = vector3d(0, 0, -0.5);

    sphere s(vector3d(0, 0, 2), 1);
    spheres.push_back(s);
    spheres.push_back(sphere(vector3d(1, 0, 3), 1));
}
