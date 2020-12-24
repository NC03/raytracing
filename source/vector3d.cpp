#include "vector3d.h"

/**
 * vector3d constructor
 * 
 * Takes one double parameter for each component of the 3d-vector.
 * @note There is no default constructor with 0 arguments
 */
vector3d::vector3d(double x, double y, double z) : x(x), y(y), z(z)
{
}

/**
 * Getter method for the x-component of the vector3d object
 * @return The double value of the component
 */
double vector3d::getX() const
{
    return x;
}

/**
 * Getter method for the y-component of the vector3d object
 * @return The double value of the component
 */
double vector3d::getY() const
{
    return y;
}

/**
 * Getter method for the y-component of the vector3d object
 * @return The double value of the component
 */
double vector3d::getZ() const
{
    return z;
}

/**
 * Overloaded operator for vector3d addition
 * @param other A const reference to the right-hand-side argument
 * @return The vector3d sum
 */
vector3d vector3d::operator+(const vector3d &other) const
{
    return vector3d(x + other.x, y + other.y, z + other.z);
}

/**
 * Overloaded operator for vector3d subtraction
 * @param other A const reference to the right-hand-side argument
 * @return The vector3d difference
 */
vector3d vector3d::operator-(const vector3d &other) const
{
    return vector3d(x - other.x, y - other.y, z - other.z);
}

/**
 * Overloaded operator for vector3d scalar multiplication
 * @param scalar The scalar with which the vector3d object must be multiplied
 * @return The vector3d result
 */
vector3d vector3d::operator*(double scalar) const
{
    return vector3d(x * scalar, y * scalar, z * scalar);
}

/**
 * Method for the vector3d dot product
 * @param other A const reference to the other argument
 * @return The double value of the dot product of the two vector3d objects
 */
double vector3d::dot(const vector3d &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

/**
 * Method for the vector3d cross product
 * @param other A const reference to the other argument
 * @return The vector3d result of the cross product between the two vector3d objects
 */
vector3d vector3d::cross(const vector3d &other) const
{
    return vector3d(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

/**
 * Overloaded operator for stream insertion of a vector3d
 * @param out A reference to the left-hand-side argument(ostream)
 * @param other A const reference to the right-hand-side argument(vector3d)
 * @return A reference to the ostream argument, enabling chaining of insertion statements
 */
ostream &operator<<(ostream &out, const vector3d &vec)
{
    string str = "[" + to_string(vec.x) + "," + to_string(vec.y) + "," + to_string(vec.z) + "]";
    return out << str;
}

/**
 * Method to create unit vectors
 * @return The vector3d unit vector(magnitude=1) in the same direction
 */
vector3d vector3d::normalize() const
{
    return operator*(1 / magnitude());
}

/**
 * Calculates the magnitude of the vector3d
 * @return The double value of the magnitude of the vector3d
 */
double vector3d::magnitude() const
{
    return sqrt(x * x + y * y + z * z);
}

/**
 * Overloaded equality operator
 * @return True if the components are all equal; otherwise, False
 * @note There may be issues with floating point precision (eg. 1.00001 will not equal 0.9999999)
 */
bool vector3d::operator==(const vector3d &vec)
{
    return (x == vec.x) && (y == vec.y) && (z == vec.z);
}

/**
 * Overloaded operator for vector3d scalar multiplication
 * @param scalar The scalar with which the vector3d object must be multiplied
 * @return The vector3d result
 */
vector3d operator*(double scalar, const vector3d &vec)
{
    return vector3d(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}