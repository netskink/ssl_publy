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
* MQTT LTS Domain - mqtt.2030.ltsapis.goog
  * Stored locally [here ] as `openssl s_client -showcerts mqtt.2030.ltsapis.goog:8883 < /dev/null > mqtt.2030.ltsapis.goog_1.dmp`   (certs/roots.pem)
* [Primary cert](https://pki.goog/gtsltsr/gtsltsr.crt)
* [Backup cert](https://pki.goog/gsr4/GSR4.crt)


https://sites.google.com/site/tlsssloverview/ssl-tls-protocol-layers/handshake-layer/change-cipher-spec-protocol


https://pki.goog/repository/

https://cloud.google.com/iot/docs/concepts/device-security

https://cloud.google.com/iot/docs/how-tos/mqtt-bridge#downloading_mqtt_server_certificates

mqtt.googleapis.com:8883 


