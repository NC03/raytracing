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

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        string finName = argv[1];
        string foutName = argv[2];
        scene s;

        ifstream in(finName);
        s.populate(in);
        in.close();

        s.render();

        ofstream out(foutName);
        s.write(out);
        out.close();
    }
    else
    {
        cout << "Usage: ./raytracing input_file.scene.stream output_file.ppm" << endl;
    }

    return 0;
}
