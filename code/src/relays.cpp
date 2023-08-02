#include <Arduino.h>

#include "ArduinoJson.h"

#include "relays.h"
#include "mqtt.h"
#include "common.h"

unsigned long relayOffMillis;
bool isRelayOn = false;

void ReportOff()
{
    StaticJsonDocument<48> doc;

    doc["status"] = "off";
    doc["duration"] = 0;

    String output;

    serializeJson(doc, output);
    PublishData("RESULT", output.c_str(), true);
}

//  Switches relay ON for [duration] seconds
void StartRelay(unsigned int duration)
{
    digitalWrite(RELAY_KALORIFER_GPIO, HIGH);
    SerialMon.printf("Kalorifer turned on for %u seconds.\r\n", duration);
    relayOffMillis = millis() + (unsigned long)(duration * 1000);
    isRelayOn = true;

    StaticJsonDocument<48> doc;

    doc["status"] = "on";
    doc["duration"] = duration;

    String output;

    serializeJson(doc, output);
    PublishData("RESULT", output.c_str(), true);
}

//  Switches relay OFF
void StopRelay()
{
    digitalWrite(RELAY_KALORIFER_GPIO, LOW);
    SerialMon.printf("Kalorifer is now switched off.\r\n");
    isRelayOn = false;

    ReportOff();
}

void SetupRelays()
{
    pinMode(RELAY_KALORIFER_GPIO, OUTPUT);
    digitalWrite(RELAY_KALORIFER_GPIO, LOW);
}

void loopRelays()
{
    if (isRelayOn && (millis() > relayOffMillis))
    {
        digitalWrite(RELAY_KALORIFER_GPIO, LOW);
        SerialMon.printf("Kalorifer is now switched off.\r\n");
        isRelayOn = false;

        ReportOff();
    }
}