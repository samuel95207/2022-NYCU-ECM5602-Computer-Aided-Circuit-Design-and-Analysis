#include "BjtP.h"

BjtP::BjtP(string name_in, string node_C, string node_B, string node_E, double value_in) {
    name = name_in;
    index = atoi(name.substr(1).c_str());
    type = DeviceType::BJT_P;
    nodes.resize(3);
    nodes[0] = node_C;
    nodes[1] = node_B;
    nodes[2] = node_E;
    value = value_in;
}


pair<Matrix, Matrix> BjtP::stampMatrix() const { return pair<Matrix, Matrix>(Matrix(), Matrix()); }
