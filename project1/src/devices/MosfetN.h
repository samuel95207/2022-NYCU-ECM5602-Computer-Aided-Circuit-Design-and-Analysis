#include <string>

#ifndef __DEVICE_H__
#define __DEVICE_H__
#include "Device.h"
#endif

using namespace std;

class MosfetN : public Device {
   public:
    MosfetN(string name_in, string node_D, string node_G, string node_S, double value_in = -1.0);
    virtual Matrix stampMatrix() const override;
};