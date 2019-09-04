#ifndef TEMPATURES_H
#define TEMPATURES_H

 #include <Adafruit_Sensor.h>
#include <dht.h>
#include <Arduino.h>
#include <Hash.h>
//#include <DHT.h>

class Tempatures
{

private:
    static int DHTPin;
    static int DHTType;

    static DHT dht;//(5, 11);

public:
    static float Temp_C;
    static float Humidity;
    static float HeatIndex;

    Tempatures(int pin, int senType);
    float readDHTHumidity();

    float readDHTTemperature();

    float readDHTHeatIndex();

    float ReadDHTSenor();



};

#endif