#include "CurrentSource.h"

CurrentSource::CurrentSource(string name_in, string node_p, string node_n, double value_in) {
    name = name_in;
    index = atoi(name.substr(1).c_str());
    type = DeviceType::CURRENT_SRC;
    nodes.resize(2);
    nodes[0] = node_p;
    nodes[1] = node_n;
    value = value_in;
}

pair<Matrix, Matrix> CurrentSource::stampMatrix() const {
    Matrix mnaStamp = Matrix();
    Matrix rhsStamp = Matrix();
    if (group == "G2" || group == "g2") {
        if (nodes[0] == "0" && nodes[1] == "0") {
            mnaStamp = Matrix({{1.0}});
            rhsStamp = Matrix({{value}});
        } else if (nodes[0] == "0") {
            mnaStamp = Matrix({{0.0, -1.0}, {0.0, 1.0}});
            rhsStamp = Matrix({{0}, {value}});
        } else if (nodes[1] == "0") {
            mnaStamp = Matrix({{0.0, 1.0}, {0.0, 1.0}});
            rhsStamp = Matrix({{0}, {value}});
        } else {
            mnaStamp = Matrix({{0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}, {0.0, 0.0, 1.0}});
            rhsStamp = Matrix({{0}, {0}, {value}});
        }
    } else {
        if (nodes[0] == "0" && nodes[1] == "0") {
            mnaStamp = Matrix();
            rhsStamp = Matrix();
        } else if (nodes[0] == "0") {
            mnaStamp = Matrix({{0.0}});
            rhsStamp = Matrix({{value}});
        } else if (nodes[1] == "0") {
            mnaStamp = Matrix({{0.0}});
            rhsStamp = Matrix({{-value}});
        } else {
            mnaStamp = Matrix({{0.0, 0.0}, {0.0, 0.0}});
            rhsStamp = Matrix({{-value}, {value}});
        }
    }
    return pair<Matrix, Matrix>(mnaStamp, rhsStamp);
}