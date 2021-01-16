#include <iostream>
#include <fstream>
#include <chrono>
#include <string>


#include "scene.h"
#include "texturedSphere.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        string finName = argv[1];
        string foutName = argv[2];
        scene s;

        ifstream in(finName);
        s.populate(in);
        // checkeredsphere: p(-1,0,2) r(1) n(0,1,-1) s(1,0,0) c1(255,128,128) c2(255,200,200)
        string img = "output/earth2.ppm";

        texturedSphere *ts = new texturedSphere(vector3d(-1,0,2),1,vector3d(0,1,-1),vector3d(1,0,0),2048,1024,img);

        s.push_back(ts);
        in.close();

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
