// #include "coreiot.h"

// constexpr uint32_t MAX_MESSAGE_SIZE = 1024U;
// constexpr char LED_STATE_ATTR[] = "ledState";
// constexpr char BLINKING_INTERVAL_ATTR[] = "blinkingInterval";

// WiFiClient wifiClient;
// Arduino_MQTT_Client mqttClient(wifiClient);
// ThingsBoard tb(mqttClient, MAX_MESSAGE_SIZE);

// volatile bool attributesChanged = false;
// volatile bool ledState = false;
// volatile uint16_t blinkingInterval = 1000U;
// uint32_t previousDataSend = 0;
// constexpr int16_t telemetrySendInterval = 10000U;

// RPC_Response setLedSwitchState(const RPC_Data &data){
//     bool newState = data;
//     Serial.println("Switch state change: ");
//     Serial.print(newState);
//     digitalWrite(48, newState ? HIGH : LOW);
//     attributesChanged = true;
//     return RPC_Response("setLedSwitchValue", newState);
// }

// const std::array<RPC_Callback, 1U> callbacks = {
//     RPC_Callback{ "setLedSwitchValue", setLedSwitchState }
// };

// void processSharedAttributes(const Shared_Attribute_Data &data) {
//     for (auto it = data.begin(); it != data.end(); ++it){
//         if (strcmp(it->key().c_str(), BLINKING_INTERVAL_ATTR) == 0) {
//             blinkingInterval = it->value().as<uint16_t>();
//         } else if (strcmp(it->key().c_str(), LED_STATE_ATTR) == 0) {
//             ledState = it->value().as<bool>();
//             digitalWrite(48, ledState);
//             Serial.println("LED state is set to: ");
//             Serial.print(ledState);
//         }
//     }
//     attributesChanged = true;
// }

// const Shared_Attribute_Callback attributes_callback(&processSharedAttributes, &LED_STATE_ATTR, &LED_STATE_ATTR+1);
// const Attribute_Request_Callback attribute_shared_request_callback(&processSharedAttributes, &LED_STATE_ATTR, &LED_STATE_ATTR+1);

// // Task CoreIoT
// void coreiot_task(void *pvParameters) {
//     SystemHandles* handles = (SystemHandles*)pvParameters;

//     // Khai báo biến runtime
//     const char* TOKEN = handles->sysData.coreiot_token.c_str();
//     const char* THINGSBOARD_SERVER = handles->sysData.coreiot_server.c_str();
//     uint16_t THINGSBOARD_PORT = handles->sysData.coreiot_port.toInt();
//     for (;;) {
//         if (WiFi.status() == WL_CONNECTED) {
//         if (!tb.connected()) {
//             if (tb.connect(handles->sysData.coreiot_server.c_str(), handles->sysData.coreiot_token.c_str(), handles->sysData.coreiot_port.toInt())){
//                 Serial.println("Successed to connect");
//                 tb.RPC_Subscribe(callbacks.cbegin(), callbacks.cend());
//                 Serial.println("Successed to subscribe for RPC");
//                 tb.Shared_Attributes_Subscribe(attributes_callback);
//                 Serial.println("Successed to subscribe for shared attribute updates");
//                 tb.Shared_Attributes_Request(attribute_shared_request_callback);
//                 Serial.println("Successed to request for shared attributes");
//                 String mac = WiFi.macAddress();
//                 Serial.print("MAC Address: ");
//                 Serial.println(mac);
//             }
//         }

//         if (attributesChanged) {
//             attributesChanged = false;
//             tb.sendAttributeData(LED_STATE_ATTR, digitalRead(48));
//         }

//         if (millis() - previousDataSend > telemetrySendInterval) {
//             previousDataSend = millis();
//             float temp = 0.0; 
//             float humi = 0.0;
//             SensorData d = {0, 0, 0};
                
//             if (handles->qLcd != NULL) {
//                 if (xQueuePeek(handles->qLcd, &d, 0) == pdTRUE) {
//                     temp = d.temperature;
//                     humi = d.humidity;
//                 }
//             }
//             tb.sendTelemetryData("temperature", temp);
//             tb.sendTelemetryData("humidity", humi);
//         }
//       tb.loop();
//     }
//     vTaskDelay(pdMS_TO_TICKS(100));
//   }
// }

#include "coreiot.h"

// ----------- CONFIGURE THESE! -----------
const char* coreIOT_Server = "10.0.229.238";  
const char* coreIOT_Token = "g7drm1amhd3dchr379xu";   // Device Access Token
const int   mqttPort = 1883;
// ----------------------------------------

WiFiClient espClient;
PubSubClient client(espClient);


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
        
      Serial.println("connected to CoreIOT Server!");
      client.subscribe("v1/devices/me/rpc/request/+");
      Serial.println("Subscribed to v1/devices/me/rpc/request/+");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("] ");

  // Allocate a temporary buffer for the message
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';
  Serial.print("Payload: ");
  Serial.println(message);

  // Parse JSON
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  const char* method = doc["method"];
  if (strcmp(method, "setStateLED") == 0) {
    // Check params type (could be boolean, int, or string according to your RPC)
    // Example: {"method": "setValueLED", "params": "ON"}
    const char* params = doc["params"];

    if (strcmp(params, "ON") == 0) {
      Serial.println("Device turned ON.");
      //TODO

    } else {   
      Serial.println("Device turned OFF.");
      //TODO

    }
  } else {
    Serial.print("Unknown method: ");
    Serial.println(method);
  }
}


void setup_coreiot(){
    while (true){
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println(" Connected!");
            client.setServer("10.0.229.238", 1883);
            client.setCallback(callback);
            Serial.print("MQTT Server: ");
            Serial.println(coreIOT_Server);
            break;
        }
    }
}

void coreiot_task(void *pvParameters){
    SystemHandles* handles = (SystemHandles*)pvParameters;
    setup_coreiot();

    while(1){

        if (!client.connected()) {
            reconnect();
        }
        client.loop();

        float temp = 0.0; 
            float humi = 0.0;
            SensorData d = {0, 0, 0};
                
            if (handles->qLcd != NULL) {
                if (xQueuePeek(handles->qLcd, &d, 0) == pdTRUE) {
                    temp = d.temperature;
                    humi = d.humidity;
                }
            }
        // Sample payload, publish to 'v1/devices/me/telemetry'
        String payload = "{\"temperature\":" + String(temp) +  ",\"humidity\":" + String(humi) + "}";
        
        client.publish("v1/devices/me/telemetry", payload.c_str());


        
        Serial.println("Published payload: " + payload);
        vTaskDelay(10000);  // Publish every 10 seconds
    }
}