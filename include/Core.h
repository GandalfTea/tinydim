
#ifndef TINYDIM_CORE
#define TINYDIM_CORE


#define _USE_MATH_DEFINES // import constants from cmath
#include <cmath>

namespace tinydim {

/*  CORE DATA STRUCTURES   */

typedef int Scalar;
typedef unsigned char uchar;

// Radians <-> Degrees
#define R2D(x) x * (180 / M_PI)
#define D2R(x) x * (M_PI / 180)

struct Vertex {
    float x, y, z;
    float color[3];
};

// TODO: Make these store only pointers
struct Quad {
    Vertex points[4];
    float normal[3];
};

struct Trig {
    Vertex points[3];
    float normal[3];
};

template <typename Topography>
struct Model {
    std::vector<Topography> geometry;
};



// Direction unit vector
// Used for mouse and keyboard movement
struct Direction {

    // Variables
    float x, y, z;

    // normalize the vector into a unit vector
    Direction( float x, float y, float z ) {
       float len = sqrt( pow(x, 2) + pow(y, 2) + pow(z, 2) ); 
        this.x = x / len;
        this.y = y / len;
        this.z = z / len;
    }
}

} // namespace
#endif
