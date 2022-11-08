#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "debug.h"
#include <sml/sml_file.h>

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    char buffer[50];
    if (type == WS_EVT_CONNECT)
    {
        // client connected
        sprintf(buffer, "ws[%s][%u] connect\n", server->url(), client->id());
        DEBUG(buffer);
        client->printf("Hello Client %u :)", client->id());
        client->ping();
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        // client disconnected

        sprintf(buffer, "ws[%s][%u] disconnect: %u\n", server->url(), client->id());
        DEBUG(buffer);
    }
    else if (type == WS_EVT_ERROR)
    {
        // error was received from the other end
        sprintf(buffer, "ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t *)arg), (char *)data);
        DEBUG(buffer);
    }
    else if (type == WS_EVT_PONG)
    {
        // pong message was received (in response to a ping request maybe)
        sprintf(buffer, "ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char *)data : "");
        DEBUG(buffer);
    }
}

void publishMessage(AsyncWebSocket *wss, Sensor *sensor, sml_file *file)
{

    char jsonDoc[1024];

    DynamicJsonDocument json(1024);
    json["sensor"] = sensor->config->name;

    for (int i = 0; i < file->messages_len; i++)
    {
        sml_message *message = file->messages[i];
        if (*message->message_body->tag == SML_MESSAGE_GET_LIST_RESPONSE)
        {
            sml_list *entry;
            sml_get_list_response *body;
            body = (sml_get_list_response *)message->message_body->data;
            for (entry = body->val_list; entry != NULL; entry = entry->next)
            {
                if (!entry->value)
                { // do not crash on null value
                    continue;
                }

                char obisIdentifier[32];
                char buffer[255];

                sprintf(obisIdentifier, "%d-%d:%d.%d.%d/%d",
                        entry->obj_name->str[0], entry->obj_name->str[1],
                        entry->obj_name->str[2], entry->obj_name->str[3],
                        entry->obj_name->str[4], entry->obj_name->str[5]);

                // String entryTopic = baseTopic + "sensor/" + (sensor->config->name) + "/obis/" + obisIdentifier + "/";

                if (((entry->value->type & SML_TYPE_FIELD) == SML_TYPE_INTEGER) ||
                    ((entry->value->type & SML_TYPE_FIELD) == SML_TYPE_UNSIGNED))
                {
                    double value = sml_value_to_double(entry->value);
                    int scaler = (entry->scaler) ? *entry->scaler : 0;
                    int prec = -scaler;
                    if (prec < 0)
                        prec = 0;
                    value = value * pow(10, scaler);
                    sprintf(buffer, "%.*f", prec, value);
                    json[obisIdentifier] = value;
                    // publish(entryTopic + "value", buffer);
                }
                else if (!sensor->config->numeric_only)
                {
                    if (entry->value->type == SML_TYPE_OCTET_STRING)
                    {
                        char *value;
                        sml_value_to_strhex(entry->value, &value, true);
                        // publish(entryTopic + "value", value);
                        json[obisIdentifier] = value;
                        free(value);
                    }
                    else if (entry->value->type == SML_TYPE_BOOLEAN)
                    {
                        // publish(entryTopic + "value", entry->value->data.boolean ? "true" : "false");
                        json[obisIdentifier] = entry->value->data.boolean ? "true" : "false";
                    }
                }
            }
        }
    }

    serializeJson(json, jsonDoc);
    wss->textAll(jsonDoc);
}