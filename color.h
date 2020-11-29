#include <iostream>

#ifndef COLOR_H
#define COLOR_H

using namespace std;

class color
{
public:
    color(int red, int green, int blue);

    int getRed() const;
    int getGreen() const;
    int getBlue() const;

    static color average(color a, color b, color c, color d);

    friend ostream &operator<<(ostream &out, const color &c);

private:
    int red, green, blue;
};

#endif //COLOR_H