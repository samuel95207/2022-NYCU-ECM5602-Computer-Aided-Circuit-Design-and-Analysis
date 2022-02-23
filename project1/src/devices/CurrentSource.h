#include <string>

#ifndef __DEVICE_H__
#define __DEVICE_H__
#include "Device.h"
#endif

using namespace std;

class CurrentSource : public Device {
   public:
    CurrentSource(string name_in, string node_p, string node_n, double value_in);
};