#include <string>

#ifndef __DEVICE_H__
#define __DEVICE_H__
#include "Device.h"
#endif

using namespace std;

class BjtN : public Device {
   public:
    BjtN(string name_in, string node_C, string node_B, string node_E, double value_in = -1.0);
};