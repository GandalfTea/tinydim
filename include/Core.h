
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

    Vertex( float X, float Y, float Z ) : x(X), y(Y), z(Z) {}
};

// unit vector
struct Normal {
   float x, y, z; 
}

enum {
    MODEL_QUADS,
    MODEL_TRIANGLES
} ModelTopography;

struct Model {
    std::vector<uint32_t> geometry;
    std::vector<Vertex> vertices;
    std::vector<Normal> normals;
    ModelTopography topography = MODEL_QUADS;
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


// HYPER-DIMENTIONAL HELPERS

// Map 360 <-> 720
#define 360TO720(x) x*2
#define 720TO360(x) x/2

// Map any degree space to 360
#define 360TOX(space, y) (y * space) / 360
#define XTO360(space, y) (y * 360) / space


} // namespace
#endif
