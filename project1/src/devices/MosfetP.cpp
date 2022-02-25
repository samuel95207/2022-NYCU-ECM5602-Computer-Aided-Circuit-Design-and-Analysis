#include "MosfetP.h"

MosfetP::MosfetP(string name_in, string node_D, string node_G, string node_S, double value_in) {
    name = name_in;
    index = atoi(name.substr(1).c_str());
    type = DeviceType::MOSFET_P;
    nodes.resize(3);
    nodes[0] = node_D;
    nodes[1] = node_G;
    nodes[2] = node_S;
    value = value_in;
}

Matrix MosfetP::stampMatrix() const{
    return Matrix();
}