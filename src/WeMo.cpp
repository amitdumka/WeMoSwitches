#include "WeMo.h"

const String WeMo::Activation_Code = "Att01@24";

//Change Before Flashing
 const  char *WeMo::SSID = "AmitKr";
 const char *WeMo::password = "12345678";
 const char *WeMo::Host = "Amit_IOT";

const double WeMo::Device_Id = 67861;

String WeMo::RelayNames[] = {"SW1", "SW2", "SW3", "SW4"};
int WeMo::RelayStatus[] = {0, 0, 0, 0};
int WeMo::RelayPins[] = {0, 0, 0, 0};
int WeMo::RelayPort[] = {81, 82, 83, 84};

