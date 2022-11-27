/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

// #define BLYNK_DEBUG        // Optional, this enables more detailed prints

#include "config.h"

#define BLYNK_TEMPLATE_ID BLYNK_TEMPLATE_ID_OWNER
#define BLYNK_DEVICE_NAME BLYNK_DEVICE_NAME_OWNER
#define BLYNK_AUTH_TOKEN BLYNK_AUTH_TOKEN_OWNER

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "RodaiSensor.h"

#include "esp_log.h"

#define SOIL_SENSOR_1 V5
#define SOIL_SENSOR_2 V6
#define SOIL_SENSOR_3 V7
#define SOIL_SENSOR_4 V8

#define AMBIENT_TEMPERATURE_SENSOR V20
#define AMBIENT_HUMIDITY_SENSOR V21
#define LIGHT_SENSOR V25

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASS;

BlynkTimer timer;

RodaiSensor rodaiSensor = RodaiSensor();

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
    uint8_t data[256];
    
    int len = rodaiSensor.ReadHoldingRegisters(16, 6, 5, data);

    for (int i = 0; i < len; i++)
    {
        ESP_LOGI("MAIN", "DATA@%d=%0X",i, data[i]);
    }

    // You can send any value at any time.
    // Please don't send more that 10 values per second.
    Blynk.virtualWrite(SOIL_SENSOR_1, 0.4334f);
    Blynk.virtualWrite(SOIL_SENSOR_2, 0.233f);
    Blynk.virtualWrite(SOIL_SENSOR_3, 0.2354f);
    Blynk.virtualWrite(SOIL_SENSOR_4, 0.4353f);
    Blynk.virtualWrite(AMBIENT_TEMPERATURE_SENSOR, 35.64f);
    Blynk.virtualWrite(AMBIENT_HUMIDITY_SENSOR, 75.62f);
    Blynk.virtualWrite(LIGHT_SENSOR, 4324);
}

void setup()
{
    // Debug console
    Serial.begin(115200);

    Blynk.begin(auth, ssid, pass);

    // Setup a function to be called every second
    timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
    Blynk.run();
    timer.run(); // Initiates BlynkTimer
}