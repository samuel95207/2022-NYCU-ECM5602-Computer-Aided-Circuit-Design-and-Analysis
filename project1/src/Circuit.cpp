#include "Circuit.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


Circuit::Circuit() {}

void Circuit::readFile(string fileName) {
    ifstream infile(fileName.c_str());
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);

        Device device;

        string name, node0, node1, node2, group, valueStr;
        double value;
        iss >> name;
        char typeChar = toupper(name[0]);
        char subtypeChar = toupper(name[1]);
        switch (typeChar) {
            case 'V':
                iss >> node0 >> node1 >> value;
                device = VoltageSource(name, node0, node1, value);
                break;
            case 'I':
                iss >> node0 >> node1 >> value;
                device = CurrentSource(name, node0, node1, value);
                break;
            case 'R':
                iss >> node0 >> node1 >> value >> group;
                if (group == "" || group[0] == '%') {
                    device = Resistor(name, node0, node1, value);
                } else {
                    device = Resistor(name, node0, node1, value, group);
                }
                break;
            case 'C':
                iss >> node0 >> node1 >> value;
                device = Capacitor(name, node0, node1, value);
                break;
            case 'L':
                iss >> node0 >> node1 >> value;
                device = Inductor(name, node0, node1, value);
                break;
            case 'D':
                iss >> node0 >> node1 >> valueStr;
                if (valueStr == "" || valueStr[0] == '%') {
                    device = Diode(name, node0, node1);
                } else {
                    value = atof(valueStr.c_str());
                    device = Diode(name, node0, node1, value);
                }
                break;
            case 'Q':
                iss >> node0 >> node1 >> node2 >> valueStr;
                if (valueStr == "" || valueStr[0] == '%') {
                    value = -1.0;
                } else {
                    value = atof(valueStr.c_str());
                }
                if (subtypeChar == 'N') {
                    device = BjtN(name, node0, node1, node2, value);
                } else if (subtypeChar == 'P') {
                    device = BjtP(name, node0, node1, node2, value);
                }
                break;
            case 'M':
                iss >> node0 >> node1 >> node2 >> valueStr;
                if (valueStr == "" || valueStr[0] == '%') {
                    value = -1.0;
                } else {
                    value = atof(valueStr.c_str());
                }
                if (subtypeChar == 'N') {
                    device = MosfetN(name, node0, node1, node2, value);
                } else if (subtypeChar == 'P') {
                    device = MosfetP(name, node0, node1, node2, value);
                }
                break;
            default:
                break;
        }
        if (device.getType() != DeviceType::NONE) {
            devices.push_back(device);
        }
    }

    infile.close();
}

void Circuit::printDevices() {
    for (auto device : devices) {
        device.printInfo();
        cout << "\n";
    }
};
