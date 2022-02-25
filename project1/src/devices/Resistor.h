#include <string>

#ifndef __DEVICE_H__
#define __DEVICE_H__
#include "Device.h"
#endif

using namespace std;

class Resistor : public Device {
   public:
    Resistor(string name_in, string node_p, string node_n, double value_in, string group_in = "");
    virtual Matrix stampMatrix() const override;
};