#include "ray.h"

/**
 * ray constructor
 * 
 * @param start The vector3d position of the start of the ray
 * @param dir The vector3d in the direction of the ray
 * @note There is no default constructor with 0 arguments
 */
ray::ray(vector3d start, vector3d dir) : start(start), dir(dir.normalize())
{
}

/**
 * Overloaded operator for stream insertion of a ray
 * @param out A reference to the left-hand-side argument(ostream)
 * @param r A const reference to the right-hand-side argument(ray)
 * @return A reference to the ostream argument, enabling chaining of insertion statements
 */
ostream &operator<<(ostream &out, const ray &r)
{
    return out << r.start << " + t" << r.dir;
}

/**
 * Getter method for the start of the ray
 * @return The vector3d position of the start of the ray
 */
vector3d ray::getStart() const
{
    return start;
}

/**
 * Getter method for the direction of the ray
 * @return The vector3d in the direction of the ray
 */
vector3d ray::getDir() const
{
    return dir;
}

/**
 * Evaluates the parametric equation of the ray
 * 
 * The result is given by \f$ \vec{r}=\vec{a}+\vec{b}t \f$, where \f$\vec{a}\f$ is the vector3d start and \f$\vec{b}\f$ is the vector3d unit vector direction
 * @param t The parameter at which the ray equation is evaluated
 * @return The vector3d result
 */
vector3d ray::eval(double t) const
{
    return start + dir * t;
}
