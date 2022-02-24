#include <string>

#ifndef __DEVICE_H__
#define __DEVICE_H__
#include "devices/Device.h"
#endif

enum class xVectorElementType {
    NODE,
    G2
};

class xVectorElement {
   private:
    string name;
    xVectorElementType type;
    Device *device;


   public:
    xVectorElement(string name, xVectorElementType type, Device *device = nullptr);
    friend ostream &operator<<(std::ostream &out, xVectorElement &element);
};