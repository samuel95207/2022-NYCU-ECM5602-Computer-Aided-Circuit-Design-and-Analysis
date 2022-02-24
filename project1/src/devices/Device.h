#include <string>
#include <vector>

using namespace std;

enum class DeviceType {
    VOLTAGE_SRC,
    CURRENT_SRC,
    RESISTOR,
    CAPACITOR,
    INDUCTOR,
    DIODE,
    BJT_N,
    BJT_P,
    MOSFET_N,
    MOSFET_P,
    NONE
};


class Device {
   protected:
    string name;
    int index;
    DeviceType type = DeviceType::NONE;
    vector<string> nodes;
    double value = -1.0;
    string group = "";

   public:
    DeviceType getType();
    string getGroup();
    void printInfo();
};