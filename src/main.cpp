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
#include "sml_parser.h"
uint8_t sml_buf[10000];
uint8_t json_buf[2000];
struct sml_values_electricity values_electricity;

#define FORMAT_LITTLEFS_IF_FAILED false

#define MYPORT_TX 12
#define MYPORT_RX 14
SoftwareSerial myPort;

AsyncWebServer server(80);

#define MAX_STR_MANUF 5
unsigned char manuf[MAX_STR_MANUF];
double T1Wh = -2, SumWh = -2;

typedef struct
{
  const unsigned char OBIS[6];
  void (*Handler)();
} OBISHandler;

void Manufacturer() { smlOBISManufacturer(manuf, MAX_STR_MANUF); }

void PowerT1() { smlOBISWh(T1Wh); }

void PowerSum() { smlOBISWh(SumWh); }

// clang-format off
OBISHandler OBISHandlers[] = {
    {{0x81, 0x81, 0xc7, 0x82, 0x03, 0xff}, &Manufacturer}, /* 129-129:199.130.3*255 */
    {{0x01, 0x00, 0x01, 0x08, 0x01, 0xff}, &PowerT1},      /*   1-  0:  1.  8.1*255 (T1) */
    {{0x01, 0x00, 0x01, 0x08, 0x00, 0xff}, &PowerSum},     /*   1-  0:  1.  8.0*255 (T1 + T2) */
    {{0}, 0}
};
// clang-format on
void printWifiStatus();
void readByte();
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

unsigned char currentChar = 0;

char buffer[50];
unsigned long counter = 0;
void loop()
{

  if (myPort.available() > 0)
  {
    currentChar = myPort.read();
    sml_buf = myPort.read();
    size_t len = sizeof(currentChar);

    struct sml_context sml_ctx = {
        .sml_buf = sml_buf,
        .sml_buf_len = len,
        .sml_buf_pos = 0,
        .values_electricity = &values_electricity,
    };

    sprintf(buffer, "Parsing %d bytes:\n", len);
    printMsg(buffer);

    while (sml_ctx.sml_buf_pos < sml_ctx.sml_buf_len)
    {
      int err = sml_parse(&sml_ctx);
      if (err)
      {
        sprintf(buffer, "Parser error %d at position 0x%x\n", err, sml_ctx.sml_buf_pos);
        printMsg(buffer);
      }

      sprintf(buffer, ">>>: %.3f kWh\n", sml_ctx.values_electricity->power_active_W);
      printMsg(buffer);
    }

    // readByte();
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

void readByte()
{
  unsigned int iHandler = 0;
  currentState = smlState(currentChar);
  if (currentState == SML_START)
  {
    /* reset local vars */
    manuf[0] = 0;
    T1Wh = -3;
    SumWh = -3;
  }
  if (currentState == SML_LISTEND)
  {
    /* check handlers on last received list */
    for (iHandler = 0; OBISHandlers[iHandler].Handler != 0 &&
                       !(smlOBISCheck(OBISHandlers[iHandler].OBIS));
         iHandler++)
      ;
    if (OBISHandlers[iHandler].Handler != 0)
    {
      OBISHandlers[iHandler].Handler();
    }
  }
  if (currentState == SML_UNEXPECTED)
  {
    Serial.print(F(">>> Unexpected byte!\n"));
  }
  if (currentState == SML_FINAL)
  {

    counter++;
    printMsg(">>> Successfully received a complete message!\n");
    sprintf(buffer, "Msg..: %lu\n", counter);
    printMsg(buffer);
    sprintf(buffer, ">>> Manufacturer.............: %s\n", manuf);
    printMsg(buffer);
    sprintf(buffer, ">>> Power T1    (1-0:1.8.1)..: %.3f kWh\n", T1Wh);
    printMsg(buffer);
    sprintf(buffer, ">>> Power T1+T2 (1-0:1.8.0)..: %.3f kWh\n\n", SumWh);
    printMsg(buffer);
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