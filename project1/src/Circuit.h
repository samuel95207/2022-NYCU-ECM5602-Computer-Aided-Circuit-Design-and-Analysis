#include <list>
#include <string>
#include <unordered_map>
#include <vector>


#ifndef __DEVICE_H__
#define __DEVICE_H__
#include "devices/Device.h"
#endif

#include "Matrix.h"
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
    Matrix mnaMatrix;

    vector<string> nodeList;
    vector<pair<string, Device*>> g2List;

    unordered_map<string, int> xIndexMap;
    unordered_map<int, string> indexXMap;



   public:
    Circuit();
    void readFile(string fileName);
    void writeFile(string mnaFilename, string xVecFilename, string rhsFilename) const;
    void printDevices() const;

   private:
    void _createXVector();
};