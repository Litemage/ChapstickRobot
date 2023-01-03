/*
  Firmware by Jacob Simeone
  Using PlatformIO VSCode extension as IDE
*/

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "Constants.h" // Contains constants used in this project
#include "Subsystems.h"
#include "CommandRunner.h"

/* -------------------------- USER DEFINED FUNCIONS ------------------------- */

void ReconnectWifi(const char* ssid, const char* pass){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to wifi...");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected. LocalIP=");
  Serial.println(WiFi.localIP());
}

void ReconnectMqtt(PubSubClient* client, const std::vector<String> topics, const char* clientID){
  while (!client->connected()){
    Serial.println("Attempting connection to mqtt broker");
    if (client->connect(clientID)){
      Serial.println("Successfully connected to broker");
      for (int i=0; i < topics.size(); i++){
        client->subscribe(topics[i].c_str());
        Serial.print("Subscribed to: ");
        Serial.println(topics[i].c_str());
      }
    } else {
      Serial.print("Failed to connect to broker. rc=");
      Serial.print(client->state());
      Serial.println(". Trying again in 5 seconds");
      delay(5000);
    }
  }
}

void IndicateBlink(u_int8_t blinks){
  for (u_int8_t i = 0; i < blinks; i++){
    digitalWrite(2, HIGH);
    delay(400);
    digitalWrite(2, LOW);
    delay(400);
  }
}


/* ------------------------------ OBJECT SETUP ------------------------------ */

// Init Subsystems
Sub_DriveTrain drivetrain(Constants::DriveConstants::controllerPins, Constants::PWMSettings::controllerSettings);
Sub_Claw claw(Constants::Claw::pin);
Sub_Elevator elevator(Constants::Elevator::pin);

// Init other necessary classes
WiFiClient espClient;
PubSubClient mqttClient(espClient);

// Init command runner
CommandRunner commandRunner(drivetrain, claw, elevator);

/* -------------------------------- CALLBACK -------------------------------- */

void callback(const char* topic, byte* payload, unsigned int length){
  // Only process command if topic is "CHAPSTER"
  if (strcmp(topic, "CHAPSTER") == 0){
    commandRunner.ProcessCommand(ChapsterCommand((u_int8_t*)payload, length));
  }
}

/* ------------------------------ SETUP ROUTINE ----------------------------- */

void setup() {
  pinMode(2, OUTPUT);

  // Start serial
  Serial.begin(115200);

  mqttClient.setServer(Constants::MQTT::broker, Constants::MQTT::brokerPort);
  mqttClient.setCallback(callback);

  ReconnectWifi(Constants::WIFI::ssid.c_str(), Constants::WIFI::pass.c_str());

  ReconnectMqtt(&mqttClient, Constants::MQTT::topics, Constants::MQTT::clientID.c_str());

}

/* ---------------------------- MAIN PROGRAM LOOP --------------------------- */

void loop() {
  // Keep wifi alive
  if (!WiFi.isConnected()){
    ReconnectWifi(Constants::WIFI::ssid.c_str(), Constants::WIFI::pass.c_str());
  }

  // keep mqtt client alive
  if (!mqttClient.connected()){
    ReconnectMqtt(&mqttClient, Constants::MQTT::topics, Constants::MQTT::clientID.c_str());
  }

  mqttClient.loop();
}