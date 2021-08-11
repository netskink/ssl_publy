// The WiFi101.h header file includes
// WiFiClient.h
// WiFiSSLClient.h
// WiFiServer.h
#include <WiFi101.h> //for MKR1000
#include "arduino_secrets.h"

const char ssid[] = MYSSID; //  your network SSID (name)
const char pass[] = MYSSIDPWD;    // your network password (use for WPA, or use as key for WEP)

// This is from the WiFi101 library
WiFiClient client;  // This is the client used by webfetch code
// This is from WiFi101 library
WiFiSSLClient wifiSslClient;


// Specify IP address or hostname
String hostName = "www.google.com";

// server is used by the webpage fetch code
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
char server[] = "www.google.com";    // name address for Google (using DNS)



int pingResult;



unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);



}

void loop() {
  IPAddress ip;
  
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


  ip = WiFi.localIP();
  Serial.print("IP: ");
  Serial.println(ip);



  // Print info about the wifi network
  printCurrentNet();
  printWiFiData();
  Serial.print("wifi time: ");
  while(0 != getTime());
  Serial.println(getTime());

  // Attempt to ping
  Serial.print("Pinging ");
  Serial.print(hostName);
  Serial.print(": ");

  pingResult = WiFi.ping(hostName);

  if (pingResult >= 0) {
    Serial.print("SUCCESS! RTT = ");
    Serial.print(pingResult);
    Serial.println(" ms");
  } else {
    Serial.print("FAILED! Error code: ");
    Serial.println(pingResult);
  }

  Serial.println("Halt");
  while(true);
  
}

unsigned long getTime() {
  // get the current time from the WiFi module
  return WiFi.getTime();
}



void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI): ");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type: ");
  Serial.println(encryption, HEX);
  Serial.println();
}

void printWiFiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP address : ");
  Serial.println(ip);

  Serial.print("Subnet mask: ");
  Serial.println((IPAddress)WiFi.subnetMask());

  Serial.print("Gateway IP : ");
  Serial.println((IPAddress)WiFi.gatewayIP());

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}



void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}
