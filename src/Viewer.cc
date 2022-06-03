
#include "../include/Viewer.h"
#include <iostream>

namespace tinydim {



// Error Handling Messages
std::map<ViewerError, std::string> exception_message = {
    { UNKNOWN_OPTIONAL, "Unknown optional render option passed into constructor." },
    { UNKNOWN_TOPOLOGY, "Unknown model topology passed into Viewer model_display() function." },
    { CALIBRATION_SANITY_FAIL_WINDOW, "Calibration Sanity Check Failed. Please review the window size values of the Calibration struct." },
    { CALIBRATION_SANITY_FAIL_PERSPECTIVE, "Calibration Sanity Check Failed. Please review the GLPerspective values of the Calibration struct." }
};

template<typename T>
std::vector<T> DEFAULT_VECTOR;


// Static member variables init

double Viewer::fovy = 45.0f;
double Viewer::z_near = 0.01f;
double Viewer::z_far = 100.f;
int Viewer::init_window_length = 800;
int Viewer::init_window_height = 800;
int Viewer::init_window_pos_x = 0;
int Viewer::init_window_pos_y = 0;
bool Viewer::show_vertices = false;
bool Viewer::show_topography = false;
bool Viewer::show_normals = false;
std::vector<Model*> Viewer::models = DEFAULT_VECTOR<Model*>;



/*  CONSTRUCTORS   */

// Just Calibration
Viewer::Viewer( Calibration c )  {
    fovy = c.fovy;
    z_near = c.z_near;
    z_far = c.z_far;
    init_window_length = c.init_window_length;
    init_window_height = c.init_window_height;
    init_window_pos_x = c.init_window_pos_x;
    init_window_pos_y = c.init_window_pos_y;
    this->check_calibration_sanity();
}

Viewer::Viewer( double fovy, double z_near, double z_far, uint16_t init_window_length,
                uint16_t init_window_height, uint16_t init_window_pos_x, uint16_t init_window_pos_y) 
{
    fovy = fovy;
    z_near = z_near;
    z_far = z_far;
    init_window_length = init_window_length;
    init_window_height = init_window_height;
    init_window_pos_x = init_window_pos_x;
    init_window_pos_y = init_window_pos_y;
    this->check_calibration_sanity();
}


// With Optionals
Viewer::Viewer( ViewerOptional v, Calibration c) {
    fovy = c.fovy;
    z_near = c.z_near;
    z_far = c.z_far;
    init_window_length = c.init_window_length;
    init_window_height = c.init_window_height;
    init_window_pos_x = c.init_window_pos_x;
    init_window_pos_y = c.init_window_pos_y;
    this->check_calibration_sanity();

    if(v == VIEW_VERTICES) this->show_vertices = true;
    else if(v == VIEW_TOPOGRAPHY) this->show_topography = true;
    else if(v == VIEW_NORMALS) this->show_normals = true;
    else throw ViewerException(UNKNOWN_OPTIONAL);
}

Viewer::Viewer( ViewerOptional v1, ViewerOptional v2, Calibration c ) {
    fovy = c.fovy;
    z_near = c.z_near;
    z_far = c.z_far;
    init_window_length = c.init_window_length;
    init_window_height = c.init_window_height;
    init_window_pos_x = c.init_window_pos_x;
    init_window_pos_y = c.init_window_pos_y;
    this->check_calibration_sanity();

    if(v1 == VIEW_VERTICES || v2 == VIEW_VERTICES) this->show_vertices = true;
    else if(v1 == VIEW_TOPOGRAPHY || v2 == VIEW_TOPOGRAPHY) this->show_topography = true;
    else if(v1 == VIEW_NORMALS || v2 == VIEW_NORMALS) this->show_normals = true;
    else throw ViewerException(UNKNOWN_OPTIONAL);
}

Viewer::Viewer( ViewerOptional v1, ViewerOptional v2, ViewerOptional v3, Calibration c ) {
    fovy = c.fovy;
    z_near = c.z_near;
    z_far = c.z_far;
    init_window_length = c.init_window_length;
    init_window_height = c.init_window_height;
    init_window_pos_x = c.init_window_pos_x;
    init_window_pos_y = c.init_window_pos_y;
    this->check_calibration_sanity();

    if(v1 == VIEW_VERTICES || v2 == VIEW_VERTICES || v3 == VIEW_VERTICES) this->show_vertices = true;
    else if(v1 == VIEW_TOPOGRAPHY || v2 == VIEW_TOPOGRAPHY || v3 == VIEW_TOPOGRAPHY) this->show_topography = true;
    else if(v1 == VIEW_NORMALS || v2 == VIEW_NORMALS || v3 == VIEW_TOPOGRAPHY) this->show_normals = true;
    else throw ViewerException(UNKNOWN_OPTIONAL);
}


/*  HELPERS  */

void Viewer::check_calibration_sanity() {
    if( this->fovy < 0 || this->z_near < 0 || this->z_far < 0 )
        throw ViewerException(CALIBRATION_SANITY_FAIL_PERSPECTIVE);
    else if ( this->init_window_length < 0 || this->init_window_height < 0)
        throw ViewerException(CALIBRATION_SANITY_FAIL_WINDOW);
}

void InitGL() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void Viewer::start() {
    int argc = 0;
    char** argv = (char**)'c';
    glutInit( &argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize( this->init_window_length, this->init_window_height);
    glutInitWindowPosition( this->init_window_pos_x, this->init_window_pos_y);
    glutCreateWindow("TinyDim");

    glutDisplayFunc(this->model_display);
    glutReshapeFunc(this->reshape);
    glutIdleFunc(this->model_display);
    glutPassiveMotionFunc(this->mouse_motion);

    InitGL();

    glutMainLoop();
    return;
}

void Viewer::load( Model* m ) {
    this->models.push_back(m);
}



// Helpers

int Viewer::howManyModels() {
    return models.size();
}


/*  OpenGL and GLUT   */

void Viewer::reshape( GLsizei width, GLsizei height ) {
    if( height = 0 ) height = 1;
    GLfloat aspect = (GLfloat) width / (GLfloat) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, z_near, z_far);
}

void Viewer::mouse_motion( int x, int y ) {
    // TODO: code later
}


// Iterate through the models vector and render each depending on topology type
void Viewer::model_display() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // if camera moved, gluLookAt

    // auto rotation around origin ?

    for( auto *model : models ) {
        if( show_vertices ) {
            glBegin(GL_POINTS);
            glColor3f(0.0, 1.0f, 1.0f);
                for( auto i : model->vertices ) {
                   glVertex3f( i.x, i.y, i.z ); 
                }
            glEnd();
        }

        if( show_topography) {
            if( model->topography == MODEL_QUADS ) {
                glBegin(GL_QUADS);
                glColor3f(0.4f, 0.4f, 0.4f);    // Set to color of quad
                for( size_t i{}; i < model->geometry.size(); i+= 4 ) {
                    glVertex3f( model->vertices[i].x,   model->vertices[i].y,   model->vertices[i].z);
                    glVertex3f( model->vertices[i+1].x, model->vertices[i+1].y, model->vertices[i+1].z);
                    glVertex3f( model->vertices[i+2].x, model->vertices[i+2].y, model->vertices[i+2].z);
                    glVertex3f( model->vertices[i+3].x, model->vertices[i+3].y, model->vertices[i+3].z);
                }
            } else if( model->topography == MODEL_TRIANGLES ) {
                glBegin(GL_TRIANGLES);
                glColor3f(0.4f, 0.4f, 0.4f);    // Set to color of quad
                for( size_t i{}; i < model->geometry.size(); i+= 3 ) {
                    glVertex3f( model->vertices[i].x,   model->vertices[i].y,   model->vertices[i].z);
                    glVertex3f( model->vertices[i+1].x, model->vertices[i+1].y, model->vertices[i+1].z);
                    glVertex3f( model->vertices[i+2].x, model->vertices[i+2].y, model->vertices[i+2].z);
                }
            } else {
                throw ViewerException(UNKNOWN_TOPOLOGY);
                return;
            }
            glEnd();
        }

        if( show_normals) {
            glBegin(GL_LINES);
            glLineWidth(0.001);
            glColor3f(1.0f, 0.5f, 0.2f);    // Orange color
                // How we show normal depends on how they are computed (Not Known Yet, maybe per vertex?)
            glEnd();
        }
    }
}
} // namespace
