#include <iostream>

#ifndef __DEVICE_H__
#define __DEVICE_H__
#include "Device.h"
#endif


using namespace std;


DeviceType Device::getType() { return type; }

void Device::printInfo() {
    cout << "name = " << name << "\n";
    cout << "index = " << index << "\n";

    cout << "type = ";
    switch (type) {
        case DeviceType::VOLTAGE_SRC:
            cout << "VOLTAGE_SRC";
            break;
        case DeviceType::CURRENT_SRC:
            cout << "CURRENT_SRC";
            break;
        case DeviceType::RESISTOR:
            cout << "RESISTOR";
            break;
        case DeviceType::CAPACITOR:
            cout << "CAPACITOR";
            break;
        case DeviceType::INDUCTOR:
            cout << "INDUCTOR";
            break;
        case DeviceType::DIODE:
            cout << "DIODE";
            break;
        case DeviceType::BJT_N:
            cout << "BJT_N";
            break;
        case DeviceType::BJT_P:
            cout << "BJT_P";
            break;
        case DeviceType::MOSFET_N:
            cout << "MOSFET_N";
            break;
        case DeviceType::MOSFET_P:
            cout << "MOSFET_P";
            break;
        case DeviceType::NONE:
            cout << "NONE";
            break;
        default:
            break;
    }
    cout << "\n";

    cout << "nodes = [ ";
    for (auto node : nodes) {
        cout << node << " ";
    }
    cout << "]\n";

    cout << "value = " << value << "\n";

    if (group != "") {
        cout << "group = " << group << "\n";
    }
}