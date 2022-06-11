
#include <Symbolic.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace Symbolic;

float l1( float x, float y) { return x + y / x; }
float l2( float x, float y) { return x + y / 3; }
float l3( float x, float y) { return (x + 9) / 2; }

int main( int argc, char* argv[] ) {
        
    //Symbol<float> first( [](float x, float y){ return x+y; } );
    Symbol<float> first( l1 );
    Symbol<float> second( l2 );
    Symbol<float> third( l3 );

    vector<Symbol<float>> array;
    array.push_back(first);
    array.push_back(second);
    array.push_back(third);

    for( auto i : array ) {
        auto ret = i.eval( 5, 2);
        cout << ret << endl;
    }

    
    return 0;
}
