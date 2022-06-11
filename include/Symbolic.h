
#ifndef SYMBOLIC
#define SYMBOLIC

#include <vector>
#include <cassert>
#include <cstdint>
#include <ostream>

using std::size_t;

namespace Symbolic {


/*
    Use:

    Symbol<float> a( [](double x, double y) {x - 2 + y*x} );
    a.eval(2, 4);
*/


template <typename Type>
struct Symbol {
    Type (*logic1)( Type );
    Type (*logic2)( Type, Type );
    Type (*logic3)( Type, Type, Type );
    Type (*logic4)( Type, Type, Type, Type );
    Type (*logic5)( Type, Type, Type, Type, Type );

    Symbol( auto (*f)(Type)) 
        : logic1(f) {}
    Symbol( auto (*f)(Type, Type)) 
        : logic2(f) {}
    Symbol( auto (*f)(Type, Type, Type)) 
        : logic3(f) {}
    Symbol( auto (*f)(Type, Type, Type, Type)) 
        : logic4(f) {}
    Symbol( auto (*f)(Type, Type, Type, Type, Type)) 
        : logic5(f) {}

    // TODO: Throw descriptive errors
    auto eval( Type x ) { return logic1(x); }
    auto eval( Type x, Type y ) { return logic2(x, y); }
    auto eval( Type x, Type y, Type z ) { return logic3(x, y, z); }
    auto eval( Type x, Type y, Type z, Type f ) { return logic4(x, y, z, f); }
    auto eval( Type x, Type y, Type z, Type f, Type i ) { return logic5(x, y, z, f, i); }
};



template <typename Type>
struct Mat {
    std::vector<std::vector<Type>> data;
    uint8_t r, c;
};


template <typename Type>
inline std::ostream& operator<< (std::ostream& outs, Mat<Type> m) {
    std::string repr = "[ ";
    for( size_t i{}; i < m.r; i++ ) {
        for( size_t f{}; f < m.c; f++ ) {
            repr += to_string(m.at(i, f)) + " ";
        }
        repr += "\n";
    }
    repr += " ]";
    return outs << repr;
}


template <typename Type>
class SymMat {
    public:
        SymMat( uint8_t rows, uint8_t cols, Symbol<Type> fill) {
            for( size_t i{}; i < rows; i++ ) {
                for( size_t f{}; f < cols; f++ ) {
                    data[i][f] = fill;
                }
            }
        }

        // Change Symbol 
        void row( uint8_t row, Symbol<Type> sym ) {
            for( size_t i{}; i < this->c; i++ ) {
                data[row][i] = sym;
            }
        }

        void col( uint8_t col, Symbol<Type> sym ) {
            for( size_t i{}; i < this->r; i++ ) {
                data[i][col] = sym;
            }
        }

        void diag( Symbol<Type> sym ) {
            assert( this->c == this.r );
            for( size_t i{}; i < this->c; i++ ) {
                data[i][i] = sym;
            } 
        }

        void fill( Symbol<Type> sym ) {
            for( size_t i{}; i < this->r; i++ ) {
                for( size_t f{}; f < this->c; f++ ) {
                    data[i][f] = sym;  
                }
            }
        }

        void at( uint8_t r, uint8_t c, Symbol<Type> sym ) {
            data[r][c] = sym;
        }

        Mat<Type> eval( Type x );
        Mat<Type> eval( Type x, Type y );
        Mat<Type> eval( Type x, Type y, Type z );
        Mat<Type> eval( Type x, Type y, Type z, Type f );
        Mat<Type> eval( Type x, Type y, Type z, Type f, Type i );

    private:
        std::vector<std::vector<Symbol<Type>>> data;
        uint8_t r, c;
};


// define matrix class that accepts symbol

} // namespace
#endif
