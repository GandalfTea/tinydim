
#ifndef TINYDIM_IO
#define TINYDIM_IO

#include "./Core.h"
#include <fstream>

namespace tinydim {

bool loadModel( const char* path , Model* ret) {
    std::ifstream load_model( path, std::ios::in );
    if( load_model.fail() ) {
        return false;
    }
        
    // buffers
    std::vector<Vertex> vert_buffer{};
    std::vector<uint32_t> face_buffer{};

    std::string type;
    while( load_model>>type ) {

        switch( *type.c_str() ) {
            case '#': {
                // skip comments
                std::getline(load_model, type);
                continue;
            }
            case 'v': {
                float x{}, y{}, z{};
                load_model >> x >> y >> z;
                vert_buffer.push_back( Vertex(x, y, z));
                break;
            }
            case 'f': {
                uint32_t a{}, b{}, c{};
                load_model >>a >> b >> c;
                face_buffer.push_back(a);
                face_buffer.push_back(b);
                face_buffer.push_back(c);
                break;
            }

            // If the .obj file has more handlers that are not yet supported
            default: {
                return false;
            }
        /*    case "vt": {
                // texture 
            }
            case "vn": {
                // normals
            }
            case 'l': {
                // line
            }*/   
        }
    }

    ret->vertices = vert_buffer;
    ret->geometry = face_buffer;
    ret->topography = MODEL_TRIANGLES;
    return true;
}


} // namespace
#endif
