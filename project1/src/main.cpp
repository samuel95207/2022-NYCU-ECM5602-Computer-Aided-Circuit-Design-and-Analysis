#include <iostream>
#include <string>

#include "Circuit.h"

using namespace std;


int main(int argc, char** argv) {
    Circuit C;
    C.readFile(argv[1]);
    C.printDevices();
    C.applyStamps();
    C.writeFile(argv[2], argv[3], argv[4]);

    C.solve().print();

    // Matrix A({{1, 3, 7}, {7, 2, 8}, {2, 6, 3}});
    // Matrix B({{2, 5, 3}});

    // A.print();
    // auto LUP = A.LUDecomposition();
    // cout << "L\n" << LUP.first.first <<endl;
    // cout << "U\n" << LUP.first.second <<endl;
    // cout << "A\n" << A <<endl;
    // cout << "L * U\n" << (LUP.first.first & LUP.first.second) <<endl;
  
    // // A.inverse().print();

    // Matrix::solveEquation(A, B, "inverseMatrix").print();
    // Matrix::solveEquation(A, B, "LUDecomposition").print();


    return 0;
}