#include <Arduino.h>
#include "FS.h"
#include <LittleFS.h>

#include <Arduino.h>
#include <WiFiManager.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <AsyncElegantOTA.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <SoftwareSerial.h>
#include <WebSerial.h>

#include "debug.h"
#include "config.h"
#include "sensor.h"
#include "webserver.h"
#include "websocket.h"
#include <list>
#include <sml/sml_file.h>

#pragma region GeneralConfig

#define FORMAT_LITTLEFS_IF_FAILED false
std::list<Sensor *> *sensors = new std::list<Sensor *>();

#pragma endregion Region_1

//#define MYPORT_TX 12
// define MYPORT_RX 14

AsyncWebServer server(80);
AsyncWebSocket wss("/sensors");
void readByte();

void process_message(byte *buffer, size_t len, Sensor *sensor)
{
  // Parse
  sml_file *file = sml_file_parse(buffer + 8, len - 16);

  // DEBUG_SML_FILE(file);

  // publisher.publish(sensor, file);

  publishMessage(&wss, sensor, file);

  // free the malloc'd memory
  sml_file_free(file);
}

void setup()
{

  Serial.begin(9600);
  Serial.println("Booting...");
  delay(1000);

  DEBUGU8("Setting up %d configured sensors...\n", NUM_OF_SENSORS);
  const SensorConfig *config = SENSOR_CONFIGS;
  for (uint8_t i = 0; i < NUM_OF_SENSORS; i++, config++)
  {
    Sensor *sensor = new Sensor(config, process_message);
    sensors->push_back(sensor);
  }
  DEBUG("Sensor setup done.");

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

  wss.onEvent(onEvent);
  server.addHandler(&wss);

  configEndpoints(&server);

  AsyncElegantOTA.begin(&server); // Start ElegantOTA

  WebSerial.begin(&server);
  /* Attach Message Callback */
  WebSerial.msgCallback(recvMsg);

  server.begin();
  WEBSERIAL = true;
}

void loop()
{

  for (std::list<Sensor *>::iterator it = sensors->begin(); it != sensors->end(); ++it)
  {
    (*it)->loop();
  }
  wss.cleanupClients();
}
