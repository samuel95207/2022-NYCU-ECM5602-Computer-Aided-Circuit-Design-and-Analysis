#include <string>

#ifndef __DEVICE_H__
#define __DEVICE_H__
#include "Device.h"
#endif

using namespace std;

class MosfetP : public Device {
   public:
    MosfetP(string name_in, string node_D, string node_G, string node_S, double value_in = -1.0);
};