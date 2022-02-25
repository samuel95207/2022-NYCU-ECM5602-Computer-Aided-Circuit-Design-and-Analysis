#include "VoltageSource.h"

#include <cstdlib>

VoltageSource::VoltageSource(string name_in, string node_p, string node_n, double value_in) {
    name = name_in;
    index = atoi(name.substr(1).c_str());
    type = DeviceType::VOLTAGE_SRC;
    nodes.resize(2);
    nodes[0] = node_p;
    nodes[1] = node_n;
    value = value_in;
}

Matrix VoltageSource::stampMatrix() const {
    if (nodes[0] == "0" && nodes[1] == "0") {
        return Matrix();
    } else if (nodes[0] == "0") {
        return Matrix({{0.0, -1.0}, {-1.0, 0.0}});
    } else if (nodes[1] == "0") {
        return Matrix({{0.0, 1.0}, {1.0, 0.0}});
    } else {
        return Matrix({{0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}, {1.0, -1.0, 0.0}});
    }
    return Matrix();
}