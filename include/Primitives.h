
// PRIMITIVE GENERATION IN MULTIPLE DIMENSIONS

#ifndef TINYDIM_PRIMITIVES
#define TINYDIM_PRIMITIVES

#include "../include/Core.h";
#include <vector>
#include <ostream>
#include <set>

// debug
#include <iostream>

namespace tinydim {

// Generate cube in X dim
// RTS points to correct coordinates

struct Point {
    std::vector<float> pt{};
    int dim;

    Point( int dim ) {
        this->pt.resize( dim );
        this->dim = dim;
    }
};

inline bool operator<( Point lhs, Point rhs ) {
   // This is shit
   if( lhs.pt[4] > rhs.pt[4]) return true; 
   else if ( lhs.pt[4] < rhs.pt[4]) return false;
   else if ( lhs.pt[3] > rhs.pt[3]) return true;
   else if ( lhs.pt[3] < rhs.pt[3]) return false;
   else if ( lhs.pt[2] > rhs.pt[2]) return true;
   else if ( lhs.pt[2] < rhs.pt[2]) return false;
   else if ( lhs.pt[1] > rhs.pt[1]) return true;
   else if ( lhs.pt[1] < rhs.pt[1]) return false;
   else if ( lhs.pt[0] > rhs.pt[0]) return true;
   else if ( lhs.pt[0] < rhs.pt[0]) return false;
}

inline std::ostream& operator<< (std::ostream& outs, Point p) {
    std::string repr = "v [ ";
    for( auto i : p.pt ) {
        repr += std::to_string(i) + " ";
    }
    repr += " ]";
    return outs << repr;
}

struct Line {
    int from;
    int to;

    Line( int f, int t)
        : from(f), to(t) {}
};

// Store objects ready for rendering
struct Object {
    std::vector<Point> pts{};
    std::vector<Line> lines{};

    Object( std::vector<Point> points, std::vector<Line> lines )
        : pts(points), lines(lines) {}


    Model toModel() {
        Model ret; 
        std::vector<Vertex> vert;
        std::vector<uint32_t> geom;
        for( auto i : pts ) {
            Vertex v( i.pt[0], i.pt[1], i.pt[2]);
            vert.push_back(v);
        }

        for( auto i : lines) {
            geom.push_back(i.from);
            geom.push_back(i.to);
        }
        ret.geometry = geom;
        ret.vertices = vert;
        ret.topography = MODEL_LINES; 
        return ret;
    }
};

inline std::ostream& operator<< ( std::ostream& outs, Object o ) {

    std::string repr;

    for( auto a : o.pts) {
        repr += "v [ ";
        for( auto i : a.pt ) {
            repr += std::to_string(i) + " ";
        }
        repr += " ]\n";
    }

/*
    for( auto b : o.lines) {
        repr += "\nl [ ";
        for( auto i : o.pts[b.from].pt ) {
            repr += std::to_string(i) + " ";
        }
        repr += " ] - [ ";
        for( auto i : o.pts[b.to].pt ) {
            repr += std::to_string(i) + " ";
        }
        repr += " ]";
    }
*/

    for( auto b : o.lines) {
        repr += "\nl " + std::to_string(b.from) + " " + std::to_string(b.to);
    }
    return outs << repr;
}

/*
    RECURSIVE CUBE CREATOR IN X DIMENSIONS
*/

std::vector<Point> create_points( Point point, int depth=0 ) {
    std::vector<Point> points;
    std::set<Point> s;
    
    points.push_back(point);
    if( depth == point.dim ) {
        return points;
    }

    // Pad with 0
    auto res = create_points( point, depth+1);
    points.insert( points.end(), res.begin(), res.end() );

    point.pt[depth] = 1;

    // Add one without padding
    res = create_points( point, depth+1);
    points.insert( points.end(), res.begin(), res.end() );

    for( Point i : points) s.insert(i);
    points.assign( s.begin(), s.end() );
    return points;
}

/*
    LINK THE POINTS AT EDGES
*/
std::vector<Line> create_lines( std::vector<Point> pts ) {
    std::vector<Line> ret;
    for( size_t i=0; i < pts.size(); i++) {
        for( size_t j = i+1; j < pts.size(); j++) {
            float sum1{}, sum2{};
            for( auto num : pts[i].pt ) sum1 += num; 
            for( auto num : pts[j].pt ) sum2 += num; 

            if( sum1 - sum2 == 1 || sum1 - sum2 == -1 ) {
                Line a ( i, j );
                ret.push_back(a);
            }
        }
    }
    return ret;
}

Object Cube( int dimension ) {
    Point p(dimension); 
    std::vector<Point> a;
    std::vector<Line> b;
    a = create_points(p, 0);
    b = create_lines(a);
    return Object(a, b);
}


} // namespace
#endif
