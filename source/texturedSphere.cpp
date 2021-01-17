#include "texturedSphere.h"

/**
 * Constructor for texturedSphere object
 * 
 * @param pos The vector3d position vector of the center of the sphere
 * @param r The radius of the sphere
 * 
 * For pos, r @see sphere
 * 
 * @param n The vector pointing in the "north" direction of the sphere
 * @param s The vector pointing in the "start" direction of the sphere. Must be linearly independent from the "north" vector.
 * @param filePath The string path to the image
 * 
 */
texturedSphere::texturedSphere(vector3d pos, double r, vector3d n, vector3d s, string filePath) : sphere(pos, r), north(n.normalize()), start((s - n * (s.dot(n) / n.magnitude())).normalize())
{

    ifstream inputImage(filePath);
    image = libimage::Image::read(inputImage, libimage::Image::Format::PPM);
    inputImage.close();
    width = image.getWidth();
    height = image.getHeight();
}

/**
 * Constructor for texturedSphere object
 * 
 * @param pos The vector3d position vector of the center of the sphere
 * @param r The radius of the sphere
 * @param n The vector pointing in the "north" direction of the sphere
 * @param s The vector pointing in the "start" direction of the sphere. Must be linearly independent from the "north" vector.
 * @param image The libimage::Image to be mapped on the texturedSphere
 * 
 */
texturedSphere::texturedSphere(vector3d pos, double r, vector3d n, vector3d s, libimage::Image image) : sphere(pos, r), north(n.normalize()), start((s - n * (s.dot(n) / n.magnitude())).normalize()), image(image)
{
    width = image.getWidth();
    height = image.getHeight();
}

/**
 * Maps a real number to another real number via linear interpolation
 * 
 */
int texturedSphere::map(double v, double min, double max, int nmin, int nmax)
{
    return static_cast<int>((v - min) / (max - min) * (nmax - nmin) + nmin);
}

/**
 * Converts from libimage::Color to color
 * 
 */
color texturedSphere::convert(libimage::Color c)
{
    return color(c.getRed(), c.getGreen(), c.getBlue());
}

color texturedSphere::getColor(const ray &r) const
{
    color c1(255, 0, 0), c2(0, 128, 128);
    vector3d point = r.eval(intersectDistance(r));
    vector3d spherical = point - getPosition();
    double z = spherical.dot(north);
    double x = spherical.dot(start);
    double y = spherical.dot(north.cross(start));

    double phi = asin(z / getRadius());
    double theta = atan(y / x);

    if (x < 0)
    {
        theta += M_PI;
    }
    while (theta < 0)
    {
        theta += 2 * M_PI;
    }
    while (theta > 2 * M_PI)
    {
        theta -= 2 * M_PI;
    }
    // int temp = height-height+width-width+phi-phi;

    //TODO theta does not measure the vector in standard position, it goes clockwise instead of counter-clockwise: ex. has to go 255 to 0 instead of expected 0 to 255
    // return color(map(theta,0,2*M_PI+temp,255,0),0,0);

    //TODO fix makefile

    int iy = map(phi, -M_PI / 2, M_PI / 2, height - 1, 0);
    int ix = map(theta, 0, 2 * M_PI, width - 1, 0);
    // int i = static_cast<int>(height - 1 - (phi + M_PI / 2) / M_PI * (height - 1));
    // int j = static_cast<int>(theta / 2 / M_PI * (width - 1));

    libimage::Color c = image(ix, iy);

    return color(c.getRed(), c.getGreen(), c.getBlue());
}
