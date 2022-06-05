
#include <iostream>
#include "../include/Viewer.h";
#include "../include/IO.h";
#include "../include/Primitives.h";

using namespace std;
using namespace tinydim;

int main( int argc, char** argv) {
    
    Calibration c;
    c.init_window_pos_x = 50;
    c.init_window_pos_y = 50;
    c.z_far = 500.0f;
    c.z_near = 0.01f;
    Viewer viewer(VIEW_TOPOGRAPHY, VIEW_VERTICES, c);

    Model model;
    bool res = loadModel("../models/teapot.obj", &model );
    if( !res ) {
        cout << "Object Load Failed. Terminating." << endl;
        return -1;
    }

    auto cube = Cube(3);
    auto cube_model = cube.toModel();
    viewer.load(&cube_model);

    //viewer.load(&model);
    cout << viewer.howManyModels() << endl;
    viewer.start();

    return 0;
}
