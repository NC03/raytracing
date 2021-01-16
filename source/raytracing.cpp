#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

#include "scene.h"
#include "texturedSphere.h"
#include "pointLight.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        string finName = argv[1];
        string foutName = argv[2];
        scene s;

        // ifstream in(finName);
        // s.populate(in);
        // checkeredsphere: p(-1,0,2) r(1) n(0,1,-1) s(1,0,0) c1(255,128,128) c2(255,200,200)
        // string img = "output/earth2.ppm";

        // texturedSphere *ts = new texturedSphere(vector3d(-1,0,2),1,vector3d(0,1,-1),vector3d(1,0,0),2048,1024,img);

        // s.push_object_back(ts);
        // in.close();
        //checkeredplane: p(0,-5,0) u(1,0,0) v(0,0,1) c1(255,255,255) c2(0,0,0) w(5) h(5)

        checkeredPlane *p = new checkeredPlane(vector3d(0, -5, 0), vector3d(1, 0, 0), vector3d(0, 0, 1), 5,5,color(0, 0, 0), color(255, 255, 255));
        s.push_object_back(p);

        pointLight *l = new pointLight(vector3d(0,4,0));
        s.push_light_back(l);

        s.render();

        ofstream out(foutName);
        s.write(out);
        out.close();
        chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
        chrono::duration<double, std::milli> deltaTime = end - start;
        cout << "Time elapsed(millis): " << deltaTime.count() << endl;
    }
    else
    {
        cerr << "Usage: ./raytracing input_file.scene.stream output_file.ppm" << endl;
    }
    return 0;
}
