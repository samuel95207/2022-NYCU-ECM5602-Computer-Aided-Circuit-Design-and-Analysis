#include "xVectorElement.h"

#include <iostream>
#include <string>

using namespace std;

xVectorElement::xVectorElement(string name, xVectorElementType type, Device *device_in) : name(name), type(type) {
    if (type == xVectorElementType::G2) {
        device = device_in;
    } else {
        device = nullptr;
    }
}

string xVectorElement::getName() { return name; }


ostream &operator<<(ostream &out, xVectorElement &element) {
    if (element.type == xVectorElementType::NODE) {
        out << "V(" << element.name << ")";
    } else if (element.type == xVectorElementType::G2) {
        out << "I(" << element.name << ")";
    }
    return out;
}