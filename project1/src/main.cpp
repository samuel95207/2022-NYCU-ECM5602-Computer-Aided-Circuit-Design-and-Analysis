#include <iostream>
#include <string>

#include "Circuit.h"

using namespace std;


int main(int argc, char** argv) { 
    Circuit C;
    C.readFile(argv[1]);
    C.printDevices();
    return 0; 
}