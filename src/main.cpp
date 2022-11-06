#include <Arduino.h>
#include "FS.h"
#include <LittleFS.h>

#include <Arduino.h>
#include <WiFiManager.h>
#include <SPI.h>
#include "SPIFFS.h"
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <AsyncElegantOTA.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <SoftwareSerial.h>
#include <sml.h>
#include <WebSerial.h>

#define FORMAT_LITTLEFS_IF_FAILED false

#define MYPORT_TX 12
#define MYPORT_RX 14
SoftwareSerial myPort;

AsyncWebServer server(80);

void printWifiStatus();
void readByte(unsigned char currentChar);
void recvMsg(uint8_t *data, size_t len);
void printMsg(const char *message);

void setup()
{

  Serial.begin(9600);
  Serial.println("Booting...");

  myPort.begin(9600, SWSERIAL_8N1, MYPORT_RX, MYPORT_TX, false);
  if (!myPort)
  {
    Serial.println("Invalid SoftwareSerial pin configuration, check config");
    while (1)
    {
      delay(1000);
    }
  }

  if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED))
  {
    Serial.println("LittleFS Mount Failed");
    return;
  }

  WiFiManager wm;
  bool res;
  res = wm.autoConnect("LogMe_MeterLogger"); // password protected ap

  if (!res)
  {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else
  {
    // if you get here you have connected to the WiFi
    Serial.println("...connected to WIFI");
  }

  printWifiStatus();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/index.html", "text/html"); });

  server.serveStatic("/assets", LittleFS, "/assets/");

  AsyncElegantOTA.begin(&server); // Start ElegantOTA

  WebSerial.begin(&server);
  /* Attach Message Callback */
  WebSerial.msgCallback(recvMsg);

  server.begin();
}

void loop()
{
  ArduinoOTA.handle();

  while (myPort.available() > 0)
  {
    readByte(myPort.read());
  }
}

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

sml_states_t currentState;

void readByte(unsigned char currentChar)
{
  currentState = smlState(currentChar);
  if (currentState == SML_UNEXPECTED)
  {
    printMsg(">>> Unexpected byte\n");
  }
  if (currentState == SML_FINAL)
  {
    printMsg(">>> Successfully received a complete message!\n");
  }
  if (currentState == SML_CHECKSUM_ERROR)
  {
    printMsg(">>> Checksum error.\n");
  }
}

/* Message callback of WebSerial */
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

void printMsg(const char *message)
{
  Serial.print(message);
  WebSerial.print(message);
}