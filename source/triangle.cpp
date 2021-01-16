#include "triangle.h"

triangle::triangle(vector3d v1, vector3d v2, vector3d v3, color c) : vertex1(v1), vertex2(v2), vertex3(v3), objColor(c)
{
}

ostream &operator<<(ostream &out, const triangle &t)
{
    return out << "[" << t.vertex1 << "," << t.vertex2 << "," << t.vertex3 << "]";
}
void triangle::print(ostream &out) const
{
    out << "[" << vertex1 << "," << vertex2 << "," << vertex3 << "]";
}

vector3d triangle::getVertex1() const
{
    return vertex1;
}
vector3d triangle::getVertex2() const
{
    return vertex2;
}
vector3d triangle::getVertex3() const
{
    return vertex3;
}
vector3d triangle::normal(const ray &r) const
{
    return normal();
}
vector3d triangle::normal() const
{
    return getPlane().normal();
}
plane triangle::getPlane() const
{
    return plane(vertex1, vertex2 - vertex1, vertex3 - vertex1);
}

color triangle::getColor() const
{
    return objColor;
}

bool triangle::intersects(const ray &r) const
{
    if (!getPlane().intersects(r))
    {
        return false;
    }
    else
    {
        vector3d p = r.eval(intersectDistance(r));
        vector<vector3d> vertices = getVertices();
        for (int i = 0; i < 3; i++)
        {
            vector3d u = vertices[(i + 1) % 3] - vertices[i];
            vector3d v = vertices[(i + 2) % 3] - vertices[i];
            vector3d w = p - vertices[i];

            double outerAngle = abs(acos(u.dot(v) / u.magnitude() / v.magnitude())),
                   inner1 = abs(acos(u.dot(w) / u.magnitude() / w.magnitude())),
                   inner2 = abs(acos(w.dot(v) / w.magnitude() / v.magnitude())),
                   epsilon = 1e-3;
            //TODO: sin or cos?
            //TODO: barycentric coordinates?
            if (!(abs(inner1 + inner2 - outerAngle) < epsilon))
            {
                return false;
            }
        }
        return true;
    }
}
double triangle::intersectDistance(const ray &r) const
{
    return getPlane().intersectDistance(r);
}
color triangle::getColor(const ray &r) const
{
    return getColor();
}

vector<vector3d> triangle::getVertices() const
{
    vector<vector3d> out;
    out.push_back(vertex1);
    out.push_back(vertex2);
    out.push_back(vertex3);
    return out;
}