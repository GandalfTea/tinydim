
/* This class:
    * Creates the space
    * Handles coordinate mapping 360 <-> 540
    * Handles Rendering
    * Handle mouse motion
*/

#ifndef TINYDIM_VIEWER
#define TINYDIM_VIEWER

// OpenGL
#include <GL/glut.h>

// Local
#include <Core.h>

namespace tinydim {

typedef enum {
    OPENGL_INIT_FAILED,
    // to be completed
} ViewerException;

enum {
    VIEW_VERTICES,
    VIEW_TOPOGRAPHY,
    VIEW_NORMALS,
} ViewerOptional;

// TODO: Come up with a non-stupid name for this
struct Calibration {
    double fovy = 45.f;
    double z_near = 0.1f;
    double z_far = 50.f;
    int init_window_length = 800;
    int init_window_height = 800;
    int init_window_pos_x = 0;
    int init_window_pos_y = 0; 
};


/*
    The viewer is going to be a standard 3D 360 degree viewer.
    We will compress our extra space into these restrictions.
    TODO: Make a viewer with 0 spacial distortion for > 360deg
*/
class Viewer {
    public:
        Viewer() = delete;
        Viewer( Calibration c );
        Viewer( ViewerOptional, Calibration c );
        Viewer( ViewerOptional, ViewerOptional, Calibration c );
        Viewer( ViewerOptional, ViewerOptional, ViewerOptional, Calibration c );

        Viewer( double fovy, double z_near, double z_far, init_window_length = 800,
                init_window_height = 800, init_window_pos_x = 0, init_window_pos_y = 0);

        // Viewer can render both quads and triangles in the same scene
        void load( Model<Quad> );
        void load( Model<Trig> );

        void backgroundColor( float red, float green, float blue, float alpha );

        void start();

    private:

        // Optional Settings
        bool show_vertices = false;
        bool show_topography = false;
        bool show_normals = false;


        // Variables
        static float last_mouse_x = 0, last_mouse_y = 0;
        const float mouse_sensitivity = -1.0001f;
        float camera_pitch = 0, camera_yaw = 0; // in radians?
        

        // OpenGL Functions
        void reshape( GLsizei width, GLsizei height );
        void mouse_motion( int x, int y );
        void model_display( Model<Quads> model );
        void model_display( Model<Trig> model );
}

} // namespace
#endif
