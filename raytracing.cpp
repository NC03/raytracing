#include <iostream>

#include "ray.h"
#include "vector3d.h"
#include "plane.h"
#include "color.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    plane p(vector3d(0, 0, 0), vector3d(1, 0, 0), vector3d(0, 1, 0));

    cout << p << endl;
    ray r(vector3d(0, 0, 0), vector3d(1, 2, 0));
    cout << r << endl;

    color red(255,0,0);
    cout << red << endl;

    return 0;
}