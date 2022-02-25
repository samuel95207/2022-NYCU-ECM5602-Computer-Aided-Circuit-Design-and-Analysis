#include <string>
#include <vector>

#ifndef __MATRIX_H__
#define __MATRIX_H__
#include "../Matrix.h"
#endif

using namespace std;

enum class DeviceType {
    VOLTAGE_SRC,
    CURRENT_SRC,
    RESISTOR,
    CAPACITOR,
    INDUCTOR,
    DIODE,
    BJT_N,
    BJT_P,
    MOSFET_N,
    MOSFET_P,
    NONE
};


class Device {
   protected:
    string name;
    int index;
    DeviceType type = DeviceType::NONE;
    vector<string> nodes;
    double value = -1.0;
    string group = "";

   public:
    virtual ~Device();

    string getName() const;
    double getValue() const;
    DeviceType getType() const;
    string getGroup() const;
    vector<string> getNodes() const;
    void printInfo() const;

    virtual Matrix stampMatrix() const = 0;
};