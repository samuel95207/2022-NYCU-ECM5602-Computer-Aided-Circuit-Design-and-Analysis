#include "Capacitor.h"

Capacitor::Capacitor(string name_in, string node_p, string node_n, double value_in) {
    name = name_in;
    index = atoi(name.substr(1).c_str());
    type = DeviceType::CAPACITOR;
    nodes.resize(2);
    nodes[0] = node_p;
    nodes[1] = node_n;
    value = value_in;
}


pair<Matrix, Matrix> Capacitor::stampMatrix() const {
    Matrix mnaStamp = Matrix();
    Matrix rhsStamp = Matrix();
    if (group == "G2" || group == "g2") {
        if (nodes[0] == "0" && nodes[1] == "0") {
            mnaStamp = Matrix({{1.0}});
            rhsStamp = Matrix(1, 1);
        } else if (nodes[0] == "0") {
            mnaStamp = Matrix({{0.0, -1.0}, {value, 1.0}});
            rhsStamp = Matrix(2, 1);
        } else if (nodes[1] == "0") {
            mnaStamp = Matrix({{0.0, 1.0}, {-value, 1.0}});
            rhsStamp = Matrix(2, 1);
        } else {
            mnaStamp = Matrix({{0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}, {-value, value, 1.0}});
            rhsStamp = Matrix(3, 1);
        }
    } else {
        if (nodes[0] == "0" && nodes[1] == "0") {
            mnaStamp = Matrix();
            rhsStamp = Matrix();
        } else if (nodes[0] == "0" || nodes[1] == "0") {
            mnaStamp = Matrix({{value}});
            rhsStamp = Matrix(1, 1);
        } else {
            mnaStamp = Matrix({{value, -value}, {-value, value}});
            rhsStamp = Matrix(2, 1);
        }
    }
    return pair<Matrix, Matrix>(mnaStamp, rhsStamp);
}