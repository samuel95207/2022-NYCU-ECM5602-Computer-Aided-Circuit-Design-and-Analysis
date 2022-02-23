#include <list>
#include <string>


#ifndef __DEVICE_H__
#define __DEVICE_H__
#include "devices/Device.h"
#endif

#include "devices/BjtN.h"
#include "devices/BjtP.h"
#include "devices/Capacitor.h"
#include "devices/CurrentSource.h"
#include "devices/Diode.h"
#include "devices/Inductor.h"
#include "devices/MosfetN.h"
#include "devices/MosfetP.h"
#include "devices/Resistor.h"
#include "devices/VoltageSource.h"


using namespace std;

class Circuit {
   private:
    list<Device> devices;

   public:
    Circuit();
    void readFile(string fileName);
    void printDevices();
};