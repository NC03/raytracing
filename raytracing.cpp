#include <iostream>
#include <fstream>

#include "ray.h"
#include "vector3d.h"
#include "plane.h"
#include "color.h"

using namespace std;

void print(color **image, int width, int height, ostream &out = cout);
void checkIntersect(ray r, plane p);

int main()
{
    const int WIDTH = 1920;
    const int HEIGHT = 1080;
    color **image = new color *[HEIGHT];
    for (int i = 0; i < HEIGHT; i++)
    {
        image[i] = new color[WIDTH];
    }

    plane camera(vector3d(0, 0, 0), vector3d(1, 0, 0), vector3d(0, 1, 0));
    vector3d start = vector3d(0, 0, -1);

    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            int x = i - WIDTH / 2, y = j - HEIGHT / 2;
            vector3d pos = camera.getPoint() + x * camera.getVector1() + y * camera.getVector2();
            ray r(start, pos - start);
            if ((i == 0 || i == WIDTH - 1) && (j == 0 || j == HEIGHT - 1))
            {
                checkIntersect(r, camera);
            }
        }
    }

    ofstream out("output/image.ppm");
    print(image, WIDTH, HEIGHT, out);
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
    cout << t << endl;
    cout << r.eval(t) << endl;
}