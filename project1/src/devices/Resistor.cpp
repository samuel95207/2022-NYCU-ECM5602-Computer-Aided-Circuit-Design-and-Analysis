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

Matrix Resistor::stampMatrix() const {
    if (group == "G2" || group == "g2") {
        if (nodes[0] == "0" && nodes[1] == "0") {
            return Matrix({{-value}});
        } else if (nodes[0] == "0") {
            return Matrix({{0.0, -1.0}, {-1.0, -value}});
        } else if (nodes[1] == "0") {
            return Matrix({{0.0, 1.0}, {1.0, -value}});
        } else {
            return Matrix({{0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}, {1.0, -1.0, -value}});
        }
    } else {
        if (nodes[0] == "0" && nodes[1] == "0") {
            return Matrix();
        } else if (nodes[0] == "0" || nodes[1] == "0") {
            return Matrix({{1.0 / value}});
        } else {
            return Matrix({{1.0 / value, -1.0 / value}, {-1.0 / value, 1.0 / value}});
        }
    }
    return Matrix();
}