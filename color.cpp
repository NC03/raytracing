#include "color.h"

color::color(int red, int green, int blue) : red(red), green(green), blue(blue)
{
}

int color::getRed() const
{
    return red;
}
int color::getGreen() const
{
    return green;
}
int color::getBlue() const
{
    return blue;
}

color color::average(color a, color b, color c, color d)
{
    int red = a.red + b.red + c.red + d.red;
    int green = a.green + b.green + c.green + d.green;
    int blue = a.blue + b.blue + c.blue + d.blue;
    return color(static_cast<int>(red / 4), static_cast<int>(green / 4), static_cast<int>(blue / 4));
}

ostream &operator<<(ostream &out, const color &c)
{
    return out << "(" << c.red << "," << c.green << "," << c.blue << ")";
}
 color color::average(color arr[], int len)
{
    double red = 0, green = 0, blue = 0;
    for(int i = 0; i < len; i++)
    {
        red += arr[i].red;
        green += arr[i].green;
        blue += arr[i].blue;
    }
    return color(static_cast<int>(red/len),static_cast<int>(green/len),static_cast<int>(blue/len));
}