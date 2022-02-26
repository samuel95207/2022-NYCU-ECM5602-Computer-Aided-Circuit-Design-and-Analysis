#include "Diode.h"

#include <cstdlib>

Diode::Diode(string name_in, string node_p, string node_n, double value_in) {
    name = name_in;
    index = atoi(name.substr(1).c_str());
    type = DeviceType::DIODE;
    nodes.resize(2);
    nodes[0] = node_p;
    nodes[1] = node_n;
    value = value_in;
}

pair<Matrix, Matrix> Diode::stampMatrix() const { return pair<Matrix, Matrix>(Matrix(), Matrix()); }