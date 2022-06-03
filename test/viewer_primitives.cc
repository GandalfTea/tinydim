
#include <iostream>
#include "../include/Viewer.h"
#include "../include/IO.h"

using namespace std;
using namespace tinydim;

int main( int argc, char** argv) {
    
    Calibration c;
    c.init_window_pos_x = 50;
    c.init_window_pos_y = 50;
    Viewer viewer(VIEW_VERTICES, c);

    Model model;
    bool res = loadModel("../models/teapot.obj", &model );
    if( !res ) {
        cout << "Object Load Failed. Terminating." << endl;
        return -1;
    }


    viewer.load(&model);
    cout << viewer.howManyModels() << endl;
    viewer.start();

    return 0;
}
