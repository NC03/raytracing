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

ostream &operator<<(ostream& out, const color & c)
{
    return out << "(" << c.red << "," << c.green << "," << c.blue << ")";
}
