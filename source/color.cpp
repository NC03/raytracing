#include "color.h"

/**
 * Constructor for the color object
 * The minimum and maximum values for each channel are 0 and 255, respectively
 * @param red The value of the red channel
 * @param green The value of the green channel
 * @param blue The value of the blue channel
 */
color::color(int red, int green, int blue) : red(red), green(green), blue(blue)
{
}

/**
 * @return the value of the red channel
 */
int color::getRed() const
{
    return red;
}
/**
 * @return the value of the green channel
 */
int color::getGreen() const
{
    return green;
}
/**
 * @return the value of the blue channel
 */
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

/**
 * Overloaded stream insertion operator to print a summary of the color object
 * @param out The ostream to print the summary to
 * @param c The color to print
 * @return A reference to the stream argument enabling chaining of statements
 */
ostream &operator<<(ostream &out, const color &c)
{
    return out << "(" << c.red << "," << c.green << "," << c.blue << ")";
}

/**
 * Compute average color by averaging each channel independently
 * @param arr The array of colors to average
 * @param len The number of colors to average
 * PRECONDITION: len must be less than or equal to the size of the array to avoid segmentation fault from buffer overflow
 */
color color::average(color arr[], int len)
{
    double red = 0, green = 0, blue = 0;
    for (int i = 0; i < len; i++)
    {
        red += arr[i].red;
        green += arr[i].green;
        blue += arr[i].blue;
    }
    return color(static_cast<int>(red / len), static_cast<int>(green / len), static_cast<int>(blue / len));
}