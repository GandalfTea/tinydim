
#include <Viewer.h>

namespace tinydim {


/*  CONSTRUCTORS   */

// Just Calibration
Viewer::Viewer( Calibration c ) 
    : this.fovy(c.fovy), this.z_near(c.z_near), this.z_far(c.z_far),
      this.init_window_length(c.init_window_length), this.init_window_height(c.init_window_height),
      this.init_window_pos_x(c.init_window_pos_x),   this.init_window_pos_y(c.init_window_pos_y)
{
    this.check_calibration_sanity();
}

Viewer::Viewer( double fovy, double z_near, double z_far, init_window_length = 800,
                init_window_height = 800, init_window_pos_x = 0, init_window_pos_y = 0) 
    : this.fovy(fovy), this.z_near(z_near), this.z_far(z_far),
      this.init_window_length(init_window_length), this.init_window_height(init_window_height),
      this.init_window_pos_x(init_window_pos_x),   this.init_window_pos_y(init_window_pos_y)
{
    this.check_calibration_sanity();
}


// With Optionals
Viewer::Viewer( ViewerOptional v, Calibration c)
    : this.fovy(c.fovy), this.z_near(c.z_near), this.z_far(c.z_far),
      this.init_window_length(c.init_window_length), this.init_window_height(c.init_window_height),
      this.init_window_pos_x(c.init_window_pos_x),   this.init_window_pos_y(c.init_window_pos_y)
{
    this.check_calibration_sanity();

    if(v == VIEW_VERTICES) this.show_vertices = true;
    else if(v == VIEW_TOPOGRAPHY) this.show_topography = true;
    else if(v == VIEW_NORMALS) this.show_normals = true;
    else throw ViewerException(UNKNOWN_OPTIONAL);
}

Viewer::Viewer( ViewerOptional v1, ViewerOptional v2, Calibration c ) 
    : this.fovy(c.fovy), this.z_near(c.z_near), this.z_far(c.z_far),
      this.init_window_length(c.init_window_length), this.init_window_height(c.init_window_height),
      this.init_window_pos_x(c.init_window_pos_x),   this.init_window_pos_y(c.init_window_pos_y)
{
    this.check_calibration_sanity();

    if(v1 == VIEW_VERTICES || v2 == VIEW_VERTICES) this.show_vertices = true;
    else if(v1 == VIEW_TOPOGRAPHY || v2 == VIEW_TOPOGRAPHY) this.show_topography = true;
    else if(v1 == VIEW_NORMALS || v2 == VIEW_NORMALS) this.show_normals = true;
    else throw ViewerException(UNKNOWN_OPTIONAL);
}

Viewer::Viewer( ViewerOptional v1, ViewerOptional v2, ViewerOptional v3, Calibration c ) 
    : this.fovy(c.fovy), this.z_near(c.z_near), this.z_far(c.z_far),
      this.init_window_length(c.init_window_length), this.init_window_height(c.init_window_height),
      this.init_window_pos_x(c.init_window_pos_x),   this.init_window_pos_y(c.init_window_pos_y)
{
    this.check_calibration_sanity();

    if(v1 == VIEW_VERTICES || v2 == VIEW_VERTICES || v3 == VIEW_VERTICES) this.show_vertices = true;
    else if(v1 == VIEW_TOPOGRAPHY || v2 == VIEW_TOPOGRAPHY || v3 == VIEW_TOPOGRAPHY) this.show_topography = true;
    else if(v1 == VIEW_NORMALS || v2 == VIEW_NORMALS || v3 == VIEW_TOPOGRAPHY) this.show_normals = true;
    else throw ViewerException(UNKNOWN_OPTIONAL);
}



/*  OpenGL and GLUT   */

void Viewer::reshape( GLsizei width, GLsizei height ) {
    if( height = 0 ) height = 1;
    GLfloat aspect = (GLfloat) width / (GLfloat) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(this.fovy, aspect, this.z_near, this.z_far);
}

void Viewer::mouse_motion( int x, int y ) {
    // TODO: code later
}



// TODO: glutDisplayFunc might not like overloading this function
// Might want to merge the two

void Viewer::model_display( Model<Quad> model ) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // if moved, gluLookAt

    // auto rotation around origin ?

    if( this.show_vertices ) {
        glBegin(GL_POINTS);
        glColor3f(0.0, 1.0f, 1.0f);
            // iterate through vertex vector
        glEnd();

    } else if( this.show_topography) {
        glBegin(GL_QUADS);

        // Set to color of quad
        glColor3f(0.4f, 0.4f, 0.4f);
            // iterate through each quad vertex coordinate and create vertex
        glEnd();
    } else if( this.show_normals) {
        glBegin(GL_LINES);
        glLineWidth(0.001);
        glColor3f(1.0f, 0.5f, 0.2f);    // Orange color
            // Iterate through normals
        glEnd();
    }
}

void Viewer::model_display( Model<Trig> model ) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // if moved, gluLookAt

    // auto rotation around origin ?

    if( this.show_vertices ) {
        glBegin(GL_POINTS);
        glColor3f(0.0, 1.0f, 1.0f);
            // iterate through vertex vector
        glEnd();

    } else if( this.show_topography) {
        glBegin(GL_TRIANGLES);

        // Set to color of quad
        glColor3f(0.4f, 0.4f, 0.4f);
            // iterate through each trig vertex coordinate and create vertex
        glEnd();
    } else if( this.show_normals) {
        glBegin(GL_LINES);
        glLineWidth(0.001);
        glColor3f(1.0f, 0.5f, 0.2f);    // Orange color
            // Iterate through normals
        glEnd();
    }
}

} // namespace
