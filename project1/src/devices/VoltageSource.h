#include <string>

#ifndef __DEVICE_H__
#define __DEVICE_H__
#include "Device.h"
#endif

using namespace std;

class VoltageSource : public Device {
   public:
    VoltageSource(string name_in, string node_p, string node_n, double value_in = -1.0);
};