//This is config file for project , Here you can decide what product you want to make
// Device Type can be marked here 
//Config Here

#define WEMO_SWITCH ;
#define WEMOS ; //Wemos switch 
#define WeatherStation ;// Weather station 
#define SENSOR ; // Sensor 
#define GATEWAY ; // Gateway server
#define DEVICETYPE WEMOS // What type of device it will be 

#define WEBSERVER ;   // WebServer.. Give basic web interface to on Off
//#define WITTY ;       //Witty Cloud board  very just 3 pin for input or output . good for sensor module
//#define ESP32 ;       // ESP32 Boad dev kit rev1
#define NODEMCU ;     // Esp8266  or nodemcu board
#define Alexa ;       // WeMo Switch support with Alexa ( Will Be working for google and other)
#define RetroSwitch ; // To be Used with old/ exisiting wiring
#define MQTT ;        // Enbaling MQTT
#define WEBAPI ;      // Enabling WebApi to control Switches and board .. In version 2.0
#define ASYNC_TCP_SSL_ENABLED  1 //  SSL MQT
// Config ends here

//Device Configuration for Hardware Specific
#define _DEVICE_ID   420430 ; 
#define _ACTIVATION_CODE Life@124;

#define MAX_NO_RELAY 10;
#define NO_OF_RELAY 4;
#define NO_OF_SWITCH 4;
#define IS_RETRO_SWITCH 1; // True 1 , false 0
#define SWITCH_PIN_ARRAY ={1,2,3,5};// Input pin
#define RELAY_PIN_ARRAY={1,2,3,5}; // OutPut Pin;

#define ENABLE_IN_BUILT_LED 0; // 1 enable ; 0 disable
#define IN_BUILT_LED_PIN D4;  // Mention Pin for In built Led , harware specific. 

#define _SSID_ "AMIT_IOT";
#define _SSID_PASSWORD "12345678";
#define _HOST_ "AMITIOT_DEVICE";
#define WebServer_HTTP_Port 80;
#define WebServer_HTTPS_Port  443;

#ifdef Alexa
  #define Start_Port  81;
  #define Last_Port  90; //Max Switch /Replay can be handle by Alexa WeMos
#endif

//Static IPaddress; 

  #define IPAddress_IP;
  #define IPAddress_GW;
  #define IPAddress_SN;



