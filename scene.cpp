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
}
void scene::populate(istream &in)
{
    objects.push_back(new checkeredPlane(vector3d(0, -5, 0), vector3d(1, 0, 1), vector3d(0, 0, 1)));
    objects.push_back(new sphere(vector3d(0, 0, 2), 1));
    objects.push_back(new sphere(vector3d(1, 0, 3), 1));
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
