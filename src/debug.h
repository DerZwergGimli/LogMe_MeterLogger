#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>
#include <WiFiManager.h>
#include <WebSerial.h>

bool WEBSERIAL = false;

void printWifiStatus()
{
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

void recvMsg(uint8_t *data, size_t len)
{
    WebSerial.println("Received Data...");
    String d = "";
    for (int i = 0; i < len; i++)
    {
        d += char(data[i]);
    }
    WebSerial.println(d);
}

void DEBUG(const char *message)
{
    Serial.print(message);
    if (WEBSERIAL)
    {
        WebSerial.print(message);
    }
}

void DEBUGE(const char *message, const char *value)
{
    char buffer[50];

    sprintf(buffer, message, value);
    Serial.print(buffer);
    if (WEBSERIAL)
    {
        WebSerial.print(message);
    }
}

void DEBUGU8(const char *message, uint8_t value)
{
    char buffer[50];

    sprintf(buffer, message, value);
    Serial.print(buffer);
    if (WEBSERIAL)
    {
        WebSerial.print(message);
    }
}

#endif