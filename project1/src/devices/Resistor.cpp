#include "Resistor.h"

Resistor::Resistor(string name_in, string node_p, string node_n, double value_in, string group_in) {
    name = name_in;
    index = atoi(name.substr(1).c_str());
    type = DeviceType::RESISTOR;
    nodes.resize(2);
    nodes[0] = node_p;
    nodes[1] = node_n;
    value = value_in;
    group = group_in;
}

Matrix Resistor::stampMatrix() const{
    return Matrix();
}