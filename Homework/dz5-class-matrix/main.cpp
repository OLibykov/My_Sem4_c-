#include <iostream>
#include "matrix.h"

using namespace std;

int main(){

    matrix a(3, 3);
    cin >> a;
    a[2][2] = 5;
    int x = a[0][0];
    cout << a;
    const matrix b;
    cout << b[1][1];
    //b[0][1] = 5;
    return 0;
}

