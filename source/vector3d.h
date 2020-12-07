#include <iostream>
#include <string>
#include <cmath>

#ifndef VECTOR3D_H
#define VECTOR3D_H

using namespace std;

class vector3d
{
public:
    vector3d(double x, double y, double z);

    double getX() const;
    double getY() const;
    double getZ() const;

    vector3d operator+(const vector3d &other) const;
    vector3d operator-(const vector3d &other) const;
    vector3d operator*(double scalar) const;
    friend vector3d operator*(double scalar, const vector3d &vec);

    double dot(const vector3d &other) const;
    vector3d cross(const vector3d &other) const;
    vector3d normalize() const;
    double magnitude() const;

    friend ostream &operator<<(ostream &out, const vector3d &vec);
    bool operator==(const vector3d &vec);

private:
    double x, y, z;
};

#endif //VECTOR3D_H