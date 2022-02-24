#include <list>
#include <string>
#include <vector>
#include <unordered_map>


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
#include "xVectorElement.h"


using namespace std;

class Circuit {
   private:
    list<Device> devices;
    vector<xVectorElement> xVector;

    vector<string> nodeList;
    vector<pair<string, Device*>> g2List;

    unordered_map<string, int> xIndexMap;
    unordered_map<int, string> indexXMap;



   public:
    Circuit();
    void readFile(string fileName);
    void writeFile(string mnaFilename, string xVecFilename, string rhsFilename);
    void printDevices();

   private:
    void _createXVector();
};