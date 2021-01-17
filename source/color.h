#ifndef COLOR_H
#define COLOR_H

#include <iostream>

using namespace std;

/**
 * @brief A class for RGB colors
 */
class color
{
public:
    color(int red=128, int green=128, int blue=128);

    int getRed() const;
    int getGreen() const;
    int getBlue() const;

    static color average(color a, color b, color c, color d);
    static color average(color arr[], int len);

    friend ostream &operator<<(ostream &out, const color &c);

private:
    int red, green, blue;
};

#endif //COLOR_H