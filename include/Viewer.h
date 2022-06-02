
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
    UNKNOWN_OPTIONAL
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
        Viewer( ViewerOptional v, Calibration c );
        Viewer( ViewerOptional v1, ViewerOptional v2, Calibration c );
        Viewer( ViewerOptional v1, ViewerOptional v2, ViewerOptional v3, Calibration c );

        Viewer( double fovy, double z_near, double z_far, init_window_length = 800,
                init_window_height = 800, init_window_pos_x = 0, init_window_pos_y = 0);

        // Viewer can render both quads and triangles in the same scene
        void load( Model<Quad> );
        void load( Model<Trig> );

        //void backgroundColor( float red, float green, float blue, float alpha );

        void start();

    private:

        // Optional Settings
        bool show_vertices = false;
        bool show_topography = false;
        bool show_normals = false;

        // Variables
        Model* models[]; // array of models to render
        static float last_mouse_x = 0, last_mouse_y = 0;
        const float mouse_sensitivity = 0.0001f;
        float camera_pitch = 0, camera_yaw = 0; // in radians

        // Calibration
        double fovy, z_near, z_far;
        int init_window_length, init_window_height;
        int init_window_pox_x, init_window_pos_y;

        void check_calibration_sanity();

        // OpenGL Functions
        void reshape( GLsizei width, GLsizei height );
        void mouse_motion( int x, int y );
        void model_display( Model<Quads> model );
        void model_display( Model<Trig> model );
}

} // namespace
#endif
