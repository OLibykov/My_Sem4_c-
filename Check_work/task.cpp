#include <iostream>
using namespace std;

template <class T, double d> T f () {

            T s = 0;

            for ( int i=0; i <10 ; ++i){  s+= d; }

            return s;

}

int main () {

            double d = 1.5;

            cout  << f < int, d > () << endl;

            return 0;

}