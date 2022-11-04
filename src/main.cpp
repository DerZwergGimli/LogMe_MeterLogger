#include <Arduino.h>
#include <WiFiManager.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"

#define WIRE Wire

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &WIRE);

AsyncWebServer server(80);

void setup()
{

  Serial.begin(9600);
  Wire.begin(5, 4);
  Serial.println("Booting...");

  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("... booting!");
  display.display();

  WiFiManager wm;
  bool res;
  display.clearDisplay();
  display.println("Connect to AP:\n\n");
  display.println("LogMe_MeterLogger");
  display.display();
  res = wm.autoConnect("LogMe_MeterLogger"); // password protected ap

  if (!res)
  {
    display.clearDisplay();
    display.print("...failed to connect WIFI!");
    display.display();

    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else
  {
    // if you get here you have connected to the WiFi
    Serial.println("...connected to WIFI");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("WiFi Connected!");
    display.print("IP: ");
    display.print(WiFi.localIP());
    display.setCursor(0, 0);
    display.display(); // actually display all of the above
  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", "text/html"); });

  server.serveStatic("/assets", SPIFFS, "/assets/");

  server.begin();
}

void loop()
{
}