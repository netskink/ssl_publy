/*
  GCP (Google Cloud Platform) IoT Core WiFi
  This sketch securely connects to GCP IoT Core using MQTT over WiFi.
  It uses a private key stored in the ATECC508A and a JSON Web Token (JWT) with
  a JSON Web Signature (JWS).
  It publishes a message every 5 seconds to "/devices/{deviceId}/state" topic
  and subscribes to messages on the "/devices/{deviceId}/config" and
  "/devices/{deviceId}/commands/#" topics.
  The circuit:
  - Arduino MKR WiFi 1010 or MKR1000
  This example code is in the public domain.
*/

#include <ArduinoECCX08.h>
#include <utility/ECCX08JWS.h>
#include <ArduinoMqttClient.h>
#include <Arduino_JSON.h>
#include <WiFi101.h> // for MKR1000

#include "arduino_secrets.h"

/////// Enter your sensitive data in arduino_secrets.h
const char ssid[]        = SECRET_SSID;
const char pass[]        = SECRET_PASS;

const char projectId[]   = SECRET_PROJECT_ID;
const char cloudRegion[] = SECRET_CLOUD_REGION;
const char registryId[]  = SECRET_REGISTRY_ID;
const String deviceId    = SECRET_DEVICE_ID;

const char broker[]      = "mqtt.googleapis.com";

WiFiSSLClient wifiSslClient;
MqttClient    mqttClient(wifiSslClient);

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!ECCX08.begin()) {
    Serial.println("No ECCX08 present!");
    while (1);
  }

  // Calculate and set the client id used for MQTT
  String clientId = calculateClientId();

  mqttClient.setId(clientId);

  // Set the message callback, this function is
  // called when the MQTTClient receives a message
  mqttClient.onMessage(onMessageReceived);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  Serial.println("Before the connectMQTT()");
  Serial.println("Delay to get terminal up");
  delay(10000);
  Serial.println("Go!");


  if (!mqttClient.connected()) {
    // MQTT client is disconnected, connect
    connectMQTT();
  }

  // poll for new MQTT messages and send keep alives
  mqttClient.poll();

  // publish a message roughly every 5 seconds.
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();

    publishMessage();
  }
}

unsigned long getTime() {
  // get the current time from the WiFi module
  return WiFi.getTime();
}

void connectWiFi() {
  Serial.print("Attempting to connect to SSID: ");
  Serial.print(ssid);
  Serial.print(" ");

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }
  Serial.println();

  Serial.println("You're connected to the network");
  Serial.println();
}

void connectMQTT() {
  Serial.print("Attempting to connect to MQTT broker: ");
  Serial.print(broker);
  Serial.println(" ");

  while (!mqttClient.connected()) {
    // Calculate the JWT and assign it as the password
    String jwt = calculateJWT();

    mqttClient.setUsernamePassword("", jwt);

    if (!mqttClient.connect(broker, 8883)) {
      Serial.print("mqttClient.connectError(): ");
      Serial.println(mqttClient.connectError());
      // failed, retry
      Serial.print("Halt");
      while(true);
      //Serial.print(".");
      delay(5000);
    }
  }
  Serial.println();

  Serial.println("You're connected to the MQTT broker");
  Serial.println();

  // subscribe to topics
  mqttClient.subscribe("/devices/" + deviceId + "/config", 1);
  mqttClient.subscribe("/devices/" + deviceId + "/commands/#");
}

String calculateClientId() {
  String clientId;

  // Format:
  //
  //   projects/{project-id}/locations/{cloud-region}/registries/{registry-id}/devices/{device-id}
  //

  clientId += "projects/";
  clientId += projectId;
  clientId += "/locations/";
  clientId += cloudRegion;
  clientId += "/registries/";
  clientId += registryId;
  clientId += "/devices/";
  clientId += deviceId;

  return clientId;
}

String calculateJWT() {
  unsigned long now = getTime();
  
  // calculate the JWT, based on:
  //   https://cloud.google.com/iot/docs/how-tos/credentials/jwts
  JSONVar jwtHeader;
  JSONVar jwtClaim;

  jwtHeader["alg"] = "ES256";
  jwtHeader["typ"] = "JWT";

  jwtClaim["aud"] = projectId;
  jwtClaim["iat"] = now;
  jwtClaim["exp"] = now + (24L * 60L * 60L); // expires in 24 hours 

  return ECCX08JWS.sign(0, JSON.stringify(jwtHeader), JSON.stringify(jwtClaim));
}

void publishMessage() {
  Serial.println("Publishing message");

  // send message, the Print interface can be used to set the message contents
  mqttClient.beginMessage("/devices/" + deviceId + "/state");
  mqttClient.print("hello ");
  mqttClient.print(millis());
  mqttClient.endMessage();
}

void onMessageReceived(int messageSize) {
  // we received a message, print out the topic and contents
  Serial.print("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    Serial.print((char)mqttClient.read());
  }
  Serial.println();

  Serial.println();
}
