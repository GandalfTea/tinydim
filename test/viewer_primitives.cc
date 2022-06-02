
#include <iostream>
#include <Viewer.cc>
#include <IO.h>

using namespace std;
using namespace tinydim;

int main( int argc, char** argv) {
    
    Calibration c;
    Viewer viewer(c);

    Model model;
    if( !loadModel("../models/teapot.obj", model& )) {
        cout << "Object Load Failed. Terminating." << endl;
        return -1;
    }

    viewer.load(model);
    viewer.start();

    return 0;
}
