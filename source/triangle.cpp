#include "triangle.h"

triangle::triangle(vector3d v1, vector3d v2, vector3d v3, color c) : vertex1(v1), vertex2(v2), vertex3(v3), objColor(c)
{
}

ostream &operator<<(ostream &out, const triangle &t)
{
    return out << "[" << t.vertex1 << "," << t.vertex2 << "," << t.vertex3 << "]";
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
vector3d triangle::getNormal() const
{
    return getPlane().getNormal();
}
plane triangle::getPlane() const
{
    return plane(vertex1, vertex2 - vertex1, vertex3 - vertex1);
}

color triangle::getColor() const
{
    return objColor;
}

bool triangle::intersects(const ray &r)
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
            //TODO: sin or cos?
            double omega = abs(acos(u.dot(w) / u.magnitude() / w.magnitude())) + abs(acos(w.dot(v) / w.magnitude() / v.magnitude()));
            double theta = abs(acos(u.dot(v) / u.magnitude() / v.magnitude()));
            if (omega > theta)
            {
                return false;
            }
        }
        return true;
    }
}
double triangle::intersectDistance(const ray &r)
{
    return getPlane().intersectDistance(r);
}
ray triangle::reflectedRay(const ray &r)
{
    return getPlane().reflectedRay(r);
}
color triangle::getColor(const ray &r)
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