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

pair<Matrix, Matrix> VoltageSource::stampMatrix() const {
    Matrix mnaStamp = Matrix();
    Matrix rhsStamp = Matrix();
    if (nodes[0] == "0" && nodes[1] == "0") {
        mnaStamp = Matrix({{0}});
        rhsStamp = Matrix({{value}});
    } else if (nodes[0] == "0") {
        mnaStamp = Matrix({{0.0, -1.0}, {-1.0, 0.0}});
        rhsStamp = Matrix({{0}, {value}});
    } else if (nodes[1] == "0") {
        mnaStamp = Matrix({{0.0, 1.0}, {1.0, 0.0}});
        rhsStamp = Matrix({{0}, {value}});
    } else {
        mnaStamp = Matrix({{0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}, {1.0, -1.0, 0.0}});
        rhsStamp = Matrix({{0}, {0}, {value}});
    }
    return pair<Matrix, Matrix>(mnaStamp, rhsStamp);
}