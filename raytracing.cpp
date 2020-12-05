#include <iostream>
#include <fstream>

#include "ray.h"
#include "vector3d.h"
#include "plane.h"
#include "color.h"
#include "sphere.h"

using namespace std;

void print(color **image, int width, int height, ostream &out = cout);
void checkIntersect(ray r, plane p);
void checkIntersect(ray r, sphere s);

int main()
{
    // const int WIDTH = 200;
    // const int HEIGHT = 60;
    const int WIDTH = 1920;
    const int HEIGHT = 1080;
    color **image = new color *[HEIGHT];
    for (int i = 0; i < HEIGHT; i++)
    {
        image[i] = new color[WIDTH];
    }

    plane camera(vector3d(0, 0, 0), vector3d(1, 0, 0), vector3d(0, 1, 0));
    sphere s(vector3d(0, 0, 2), 1);
    vector3d start = vector3d(0, 0, -0.6);

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            double x = j-WIDTH/2, y=i-HEIGHT/2;
            x /= max(WIDTH,HEIGHT);
            y /= max(WIDTH,HEIGHT);
            
            vector3d pos = camera.getPoint() + x * camera.getVector1() + y * camera.getVector2();
            ray r(start, pos - start);
            if (r.intersects(s))
            {
                image[i][j] = color(255, 0, 0);
            }
        }
    }

    ofstream out("output/image.ppm");
    print(image, WIDTH, HEIGHT, out);
    out.close();

    for (int i = 0; i < HEIGHT; i++)
    {
        delete[] image[i];
    }
    delete[] image;

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