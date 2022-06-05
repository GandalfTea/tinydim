
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
#include "./Core.h"

namespace tinydim {


// Viewer Exception Handling
typedef enum {
    OPENGL_INIT_FAILED,
    UNKNOWN_OPTIONAL,
    UNKNOWN_TOPOLOGY,
    CALIBRATION_SANITY_FAIL_WINDOW,
    CALIBRATION_SANITY_FAIL_PERSPECTIVE
} ViewerError;

extern std::map<ViewerError, std::string> exception_message; 

struct ViewerException {
    ViewerException(ViewerError error) {
        throw std::runtime_error("VIEWER EXCEPTION : " + exception_message[error]);
    }
};


typedef enum {
    VIEW_VERTICES,
    VIEW_TOPOGRAPHY,
    VIEW_NORMALS,
} ViewerOptional;


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

        Viewer( double fovy, double z_near, double z_far, uint16_t init_window_length = 800,
                uint16_t init_window_height = 800, uint16_t init_window_pos_x = 0, uint16_t init_window_pos_y = 0);

        // Viewer can render both quads and triangles in the same scene
        void load( Model* m );
        //void backgroundColor( float red, float green, float blue, float alpha );
        void start();

        // Helpers
        int howManyModels();

    private:

        // Optional Settings
        static bool show_vertices;
        static bool show_topography;
        static bool show_normals;

        // Variables
        static std::vector<Model*> models;
        static constexpr float last_mouse_x = 0, last_mouse_y = 0;
        static const float mouse_sensitivity;
        static float camera_pitch, camera_yaw; // in radians

        // Calibration
        static double fovy, z_near, z_far;
        static int init_window_length, init_window_height;
        static int init_window_pos_x, init_window_pos_y;
        static bool first_render;

        void check_calibration_sanity();

        // OpenGL Functions
        static void reshape( GLsizei width, GLsizei height );
        static void mouse_motion( int x, int y );
        static void move_camera();
        static void timer(int);
        static void model_display();
};

} // namespace
#endif
