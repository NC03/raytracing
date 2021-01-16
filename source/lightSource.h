#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <cmath>

#include "ray.h"
#include "color.h"
#include "object3d.h"
#include "vector3d.h"

class lightSource //: public object3d
{
public:
    virtual ~lightSource()
    {
    }
    virtual double intensityValue(const ray& r) = 0;
    virtual color getColor() = 0;
    double distance(vector3d r)
    {
        return (getPosition() - r).magnitude();
    }
    virtual vector3d getPosition() = 0;

    static double attenuate(double distance)
    {
        double a = 0;
        double b = 0;
        double c = 4*M_PI;
        return 1.0 / (a + b * distance + c * pow(distance, 2));
    }

    /**
     * Overloaded stream insertion operator for lightSource
     * @param out The reference to the ostream to insert the object in
     * @param i The lightSource to insert
     * @return A reference to the ostream argument to allow chaining
     * 
     */
    friend ostream &operator<<(ostream &out, const lightSource &i)
    {
        i.print(out);
        return out;
    }

    /**
     * Prints the current object to the ostream argument
     * @param out A reference to the ostream to print the object with
     */
    virtual void print(ostream &out) const = 0;
};

#endif //LIGHTSOURCE_H