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

    return 0;
}