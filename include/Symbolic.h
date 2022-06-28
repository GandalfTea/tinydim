
#ifndef SYMBOLIC
#define SYMBOLIC

//#ifdef __cplusplus__

#include <vector>
#include <cassert>
#include <cstdint>
#include <ostream>
#include <map>

// Debug
#include <iostream>

using std::size_t;

namespace Symbolic {


/*
    Symbolic Object and Matrix
    Full implementation
*/

// Keep track of all created symbols in order.
struct SymbolLedger {
    std::map<char, char> ledger; 
    uint16_t count{};

    void remove() {}
    void clear() {}
};


template <typename... Args, typename Type, typename=void>
struct Symbol {
    
    template <typename T>
    friend class SymMat<T>;

    std::vector<char> symb;

/*
    Type (*logic1)( Type );
    Type (*logic2)( Type, Type );
    Type (*logic3)( Type, Type, Type );
    Type (*logic4)( Type, Type, Type, Type );
    Type (*logic5)( Type, Type, Type, Type, Type );
*/
    Type (*logic) ( Args... args );

/*
    Symbol( char x, auto (*f)(Type)) 
        : logic1(f), vars(1) 
    {
            symb.puch_back(x);
    }
    Symbol( char x, char y, auto (*f)(Type, Type)) 
        : logic2(f) 
        {
            symb.puch_back(x);
            symb.puch_back(y);
        }
    Symbol( char x, char y, char z, auto (*f)(Type, Type, Type)) 
        : logic3(f) 
        {
            symb.puch_back(x);
            symb.puch_back(y);
            symb.puch_back(z);
        }
    Symbol( char x, char y, char z, char f,  auto (*f)(Type, Type, Type, Type)) 
        : logic4(f) {}
    Symbol( char x, char y, char z, char f, char i,  auto (*f)(Type, Type, Type, Type, Type)) 
        : logic5(f) {}
*/

    // If this works, it's insane
    Symbol( Args... args, auto (*f)(Args... func_args)) {

        // Capture all used symbols
        this->unpack_symbs( &args... );

        // Capture function
        logic = f;
    }

    void unpack_symbs(Args... pargs) {
        for( auto i : pargs ) {
            symb.push_back(*i);
        }
    }

    // TODO: Throw descriptive errors
    auto eval( Type x ) { return logic1(x); }
    auto eval( Type x, Type y ) { return logic2(x, y); }
    auto eval( Type x, Type y, Type z ) { return logic3(x, y, z); }
    auto eval( Type x, Type y, Type z, Type f ) { return logic4(x, y, z, f); }
    auto eval( Type x, Type y, Type z, Type f, Type i ) { return logic5(x, y, z, f, i); }

    std::string _get_logic_func_name() {
        return __PRETTY_FUNCTION__;
        // TODO: No fucking clue how to get the logic function name without overriding or calling and make it OS invariant
        // Create custom function type that injects the code for returning a struct of both arithmetic and name and somehow overriding the lambda init function with it?
    }
};


// define matrix class that accepts symbol

template <typename Type>
struct Mat {
    std::vector<std::vector<Type>> data;
    uint8_t r, c;

    Mat( std::vector<std::vector<double>> data, uint8_t r, uint8_t c )
        : data(data), r(r), c(c) {}
};


template <typename Type>
inline std::ostream& operator<< (std::ostream& outs, Mat<Type> m) {
    std::string repr = "\n[ ";
    for( size_t i{}; i < m.r; i++ ) {
        repr += "[ ";
        for( size_t f{}; f < m.c; f++ ) {
            repr += std::to_string(m.data[i][f]) + "  ";
        }
        (i == m.r-1) ? repr += " " : repr += " ],\n  ";
    }
    repr += "] ]\n";
    return outs << repr;
}


template <typename Type>
class SymMat {

    public:
        // Store number of values used (x, y, z, . . . )
        // Store used variables in each symbol and when eval push only certain values.
        mutable uint8_t vars{};

    public:

        template <typename T>
        friend inline std::ostream& operator<< ( std::ostream& outs, SymMat<T> m);

        // Constructor
        SymMat( uint8_t rows, uint8_t cols, Symbol<Type> fill) 
            : r(rows), c(cols)
        {
            for( size_t i{}; i < rows; i++ ) {
                std::vector<Symbol<Type>> row;
                for( size_t f{}; f < cols; f++ ) {
                    row.push_back(fill);
                }
                data.push_back(row);
            }
            std::cout << fill._get_logic_func_name() << std::endl;
            // Extract both name and variables from imported function
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

        // Evaluate Symbols
        Mat<Type> eval( Type x );
        Mat<Type> eval( Type x, Type y );
        Mat<Type> eval( Type x, Type y, Type z );
        Mat<Type> eval( Type x, Type y, Type z, Type f );
        Mat<Type> eval( Type x, Type y, Type z, Type f, Type i );

        // Helpers

    private:
        std::vector<std::vector<Symbol<Type>>> data;
        uint8_t r, c;
};

template <typename Type>
inline std::ostream& operator<< (std::ostream& outs, SymMat<Type> m) {
    std::string repr = "\n[ ";
    for( size_t i{}; i < m.r; i++ ) {
        repr += "[  ";
        for( size_t f{}; f < m.c; f++ ) {
            // This should print the logic function name from Symbol::_get_logic_function_name()
            repr += "sym  ";
        }
        (i == m.r-1) ? repr += " " : repr += "],\n  ";
    }
    repr += "] ]\n";
    return outs << repr;
}

} // namespace
#endif
