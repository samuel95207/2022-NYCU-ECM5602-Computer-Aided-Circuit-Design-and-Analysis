#include "Inductor.h"

Inductor::Inductor(string name_in, string node_p, string node_n, double value_in) {
    name = name_in;
    index = atoi(name.substr(1).c_str());
    type = DeviceType::INDUCTOR;
    nodes.resize(2);
    nodes[0] = node_p;
    nodes[1] = node_n;
    value = value_in;
}

pair<Matrix, Matrix> Inductor::stampMatrix() const {
    Matrix mnaStamp = Matrix();
    Matrix rhsStamp = Matrix();
    if (nodes[0] == "0" && nodes[1] == "0") {
        mnaStamp = Matrix({{value}});
        rhsStamp = Matrix(1, 1);
    } else if (nodes[0] == "0") {
        mnaStamp = Matrix({{0.0, -1.0}, {1.0, value}});
        rhsStamp = Matrix(2, 1);
    } else if (nodes[1] == "0") {
        mnaStamp = Matrix({{0.0, 1.0}, {-1.0, value}});
        rhsStamp = Matrix(2, 1);
    } else {
        mnaStamp = Matrix({{0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}, {-1.0, 1.0, value}});
        rhsStamp = Matrix(3, 1);
    }

    return pair<Matrix, Matrix>(mnaStamp, rhsStamp);
}