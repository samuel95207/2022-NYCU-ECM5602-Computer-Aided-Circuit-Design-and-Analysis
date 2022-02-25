#include "Circuit.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


Circuit::Circuit() {}
Circuit::~Circuit() {
    for (auto device : devices) {
        delete device;
    }
}


void Circuit::readFile(string fileName) {
    ifstream infile(fileName.c_str());
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);

        Device* device;

        string name, node0, node1, node2, group, valueStr;
        double value;
        iss >> name;
        char typeChar = toupper(name[0]);
        char subtypeChar = toupper(name[1]);
        switch (typeChar) {
            case 'V':
                iss >> node0 >> node1 >> value;
                device = new VoltageSource(name, node0, node1, value);
                break;
            case 'I':
                iss >> node0 >> node1 >> value;
                device = new CurrentSource(name, node0, node1, value);
                break;
            case 'R':
                iss >> node0 >> node1 >> value >> group;
                if (group == "" || group[0] == '%') {
                    device = new Resistor(name, node0, node1, value);
                } else {
                    device = new Resistor(name, node0, node1, value, group);
                }
                break;
            case 'C':
                iss >> node0 >> node1 >> value;
                device = new Capacitor(name, node0, node1, value);
                break;
            case 'L':
                iss >> node0 >> node1 >> value;
                device = new Inductor(name, node0, node1, value);
                break;
            case 'D':
                iss >> node0 >> node1 >> valueStr;
                if (valueStr == "" || valueStr[0] == '%') {
                    device = new Diode(name, node0, node1);
                } else {
                    value = atof(valueStr.c_str());
                    device = new Diode(name, node0, node1, value);
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
                    device = new BjtN(name, node0, node1, node2, value);
                } else if (subtypeChar == 'P') {
                    device = new BjtP(name, node0, node1, node2, value);
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
                    device = new MosfetN(name, node0, node1, node2, value);
                } else if (subtypeChar == 'P') {
                    device = new MosfetP(name, node0, node1, node2, value);
                }
                break;
            default:
                break;
        }
        if (device->getType() != DeviceType::NONE) {
            if (device->getType() == DeviceType::VOLTAGE_SRC ||
                (device->getType() == DeviceType::RESISTOR &&
                 (device->getGroup() == "G2" || device->getGroup() == "g2"))) {
                g2List.push_back(pair<string, Device*>(name, device));
            }

            devices.push_back(device);
        }
    }

    infile.close();


    for (auto it = devices.rbegin(); it != devices.rend(); ++it) {
        auto device = *it;
        auto nodes = device->getNodes();
        for (auto node : nodes) {
            if (node != "" && node != "0" && find(nodeList.begin(), nodeList.end(), node) == nodeList.end()) {
                nodeList.push_back(node);
            }
        }
    }
    reverse(nodeList.begin(), nodeList.end());

    _createXVector();

    mnaMatrix = Matrix(xVector.size(), xVector.size());
    rhsMatrix = Matrix(xVector.size(), 1);
}

void Circuit::writeFile(string mnaFilename, string xVecFilename, string rhsFilename) const {
    ofstream mnaFile(mnaFilename.c_str());
    mnaFile << mnaMatrix;
    mnaFile.close();

    ofstream xVecFile(xVecFilename.c_str());
    for (auto element : xVector) {
        xVecFile << element << "\n";
    }
    xVecFile.close();

    ofstream rhsFile(rhsFilename.c_str());
    rhsFile << rhsMatrix;
    rhsFile.close();
}


void Circuit::printDevices() const {
    for (auto device : devices) {
        device->printInfo();
        cout << "\n";
    }
};


void Circuit::applyStamps() {
    for (auto device : devices) {
        if (device->getType() == DeviceType::VOLTAGE_SRC) {
            int row = xIndexMap[device->getName()];
            double newValue = rhsMatrix.getValue(row, 0) + device->getValue();
            rhsMatrix.setValue(row, 0, newValue);
        } else if (device->getType() == DeviceType::CURRENT_SRC) {
            auto nodes = device->getNodes();
            string nodeP = nodes[0];
            string nodeN = nodes[1];
            if (nodeP != "0") {
                int nodePRow = xIndexMap[nodeP];
                double newNodePValue = rhsMatrix.getValue(nodePRow, 0) - device->getValue();
                rhsMatrix.setValue(nodePRow, 0, newNodePValue);
            }
            if (nodeN != "0") {
                int nodeNRow = xIndexMap[nodeN];
                double newNodeNValue = rhsMatrix.getValue(nodeNRow, 0) + device->getValue();
                rhsMatrix.setValue(nodeNRow, 0, newNodeNValue);
            }
        }

        auto nodes = device->getNodes();
        int nodesSize = nodes.size();
        if (nodesSize == 2) {
            string nodeP = nodes[0];
            string nodeN = nodes[1];
            vector<int> Offsets;
            Matrix stampMatrix = device->stampMatrix();
            // device->printInfo();
            // cout << device->getName() << endl;
            if (nodeP != "0") {
                Offsets.push_back(xIndexMap[nodeP]);
            }
            if (nodeN != "0") {
                Offsets.push_back(xIndexMap[nodeN]);
            }
            if (device->getGroup() == "G2" || device->getGroup() == "g2") {
                Offsets.push_back(xIndexMap[device->getName()]);
            }
            if (device->getType() == DeviceType::VOLTAGE_SRC) {
                Offsets.push_back(xIndexMap[device->getName()]);
            }
            mnaMatrix.stamp(stampMatrix, Offsets, Offsets);
        }
    }
    mnaMatrix.print();
}


Matrix Circuit::solve() { return Matrix::solveEquation(mnaMatrix, rhsMatrix); }




void Circuit::_createXVector() {
    for (auto devicePair : g2List) {
        xVector.push_back(xVectorElement(devicePair.first, xVectorElementType::G2, devicePair.second));
    }
    for (auto node : nodeList) {
        xVector.push_back(xVectorElement(node, xVectorElementType::NODE));
    }

    reverse(xVector.begin(), xVector.end());

    int size = xVector.size();
    for (int i = 0; i < size; i++) {
        string name = xVector[i].getName();
        xIndexMap[name] = i;
        indexXMap[i] = name;
    }
}
