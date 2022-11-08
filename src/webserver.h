#include <Arduino.h>
#include "FS.h"
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <list>
#include "sensor.h"

void configEndpoints(AsyncWebServer *server)
{
    // Root URL
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(LittleFS, "/index.html", "text/html"); });
    // Serve all assets
    server->serveStatic("/assets", LittleFS, "/assets/");
}
