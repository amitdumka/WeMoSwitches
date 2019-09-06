/*
   Four Channel Relayed Based on wemos switches
   By: Amit Kumar (2019)
   Version 1.0
*/

#include "Config.h"
#include "CYN_OTA.h"
#define VERSION 1.1 

static const double DeviceId = 5458979879;

#ifdef WEMO_SWITCH
#include "WeMo_Main.h"
WeMo_Main weMoMain;
#endif

void setup()
{

  Serial.begin(115200);
  CallWiFiManager(false); //Call to connect to Wifi NetWork;

#ifdef WEMO_SWITCH
  Serial.println("Wemo Switch is activated");
  weMoMain.CallInSetUp();
#endif

  FirmwareUpdater::UpdaterInstaller();
  Serial.print("Version: "); Serial.println(VERSION);

} // end of Setup

void loop()
{
  FirmwareUpdater::UpdaterLooper();

#ifdef WEMO_SWITCH
  weMoMain.CallInLoop();
#endif
}
