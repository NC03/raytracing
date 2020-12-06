#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

#include "ray.h"
#include "vector3d.h"
#include "plane.h"
#include "color.h"
#include "sphere.h"
#include "checkeredPlane.h"
#include "scene.h"

using namespace std;

void populate(scene &scene, istream &in);

int main(int argc, char *argv[])
{
    string finName = "example.scene.stream";
    string foutName = "output/image.ppm";
    if (argc == 3)
    {
        finName = argv[1];
        foutName = argv[2];
    }
    scene s;

    ifstream in(finName);
    s.populate(in);
    in.close();

    s.render();

    ofstream out(foutName);
    s.write(out);
    out.close();

    return 0;
}

void populate(scene &scene, istream &in)
{
    const int MAX_LEN = 256;
    char l[MAX_LEN];
    while (!in.eof())
    {
        in.getline(l, MAX_LEN);
        string line = l;
        //PROCESS
    }
}