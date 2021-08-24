# Important URLS

## Web Guides
* [Illustrated SSL](https://tls.ulfheim.net/)
* [ssl tls protocol](https://sites.google.com/site/tlsssloverview/ssl-tls-protocol-layers/handshake-layer/change-cipher-spec-protocol)

## Src Repos
* [GoogleCloudPlatform/google-cloud-iot-arduinio](https://github.com/GoogleCloudPlatform/google-cloud-iot-arduino)
* [Arduino/ArduinoCloudProviderExamples](https://github.com/arduino/ArduinoCloudProviderExamples)



## GCP Example specifies the following SSL related urls
* [roots cert](https://pki.goog/roots.pem)
  * Stored locally [here ](certs/roots.pem)
    * The complete Google root CA certificate (128KB)
* MQTT server address [mqtt.googleapis.com](mqtt.googleapis.com)
  * Stored locally [here](certs/xxx.dmp)
  * This is the notes from the "Downloading MQTT server certificates"
    section on cloud.google.com/iot/docs
    * This package establishes the chain of trust to communicate with 
      Google products and services, including Cloud IoT Core
    * the complete google root CA certification package is
      the roots.pem cert.

* MQTT LTS Server/Domain - mqtt.2030.ltsapis.goog
  * Stored locally [here](certs/mqtt.2030.ltsapis.goog_1.dmp) 
  * In the official docs this is noted as a minimal set
    for use with memory limited devices.
* [Primary cert](https://pki.goog/gtsltsr/gtsltsr.crt)
  * Stored locally [here](certs/gtslsr.crt)    
  *
  * Binary file
* [Backup cert](https://pki.goog/gsr4/GSR4.crt)
  * Stored locally [here](certs/GSR4.crt) 
  * Binary file

  * This is the notes from the "Downloading MQTT server certificates"
    section on cloud.google.com/iot/docs
    * This package establishes the chain of trust to communicate with 
      Google products and services, including Cloud IoT Core

cloud.google.com/docs

https://cloud.google.com/iot/docs/how-tos/mqtt-bridge#downloading_mqtt_server_certificates


# url for decoding base64
https://cryptii.com/pipes/base64-to-hex


```
nmap -p 443 --script ssl-cert gnupg.org
nmap -p 8883 --script ssl-cert mqtt.googleapis.com | less
```


https://sites.google.com/site/tlsssloverview/ssl-tls-protocol-layers/handshake-layer/change-cipher-spec-protocol


https://pki.goog/repository/

https://cloud.google.com/iot/docs/concepts/device-security

https://cloud.google.com/iot/docs/how-tos/mqtt-bridge#downloading_mqtt_server_certificates

mqtt.googleapis.com:8883 


