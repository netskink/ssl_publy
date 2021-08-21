# ssl_publy
Arduino Failure to Connect to GCP discussion


I have a problem with connecting to GCP with MQTT/SSL.  I tried to privately
debug this problem, then I filed some issues, then I started this discussion.

The files here are a mix of notes in markdown, source/project directories and screenshots.

## So what's the problem?

LOL, when I first started this endeavor the problem was connecting to GCP.  Now
the problem is to understand why.  Although, I  can connect to google.com using
HTTPS, I can't when using MQTT/SSL.

I didn't just come up with the original source/firmware.  I am using two 
samples publicly available github repo's.  One is from Arduino
and the other is from Google.


* [GoogleCloudPlatform/google-cloud-iot-arduinio](https://github.com/GoogleCloudPlatform/google-cloud-iot-arduino)
* [Arduino/ArduinoCloudProviderExamples](https://github.com/arduino/ArduinoCloudProviderExamples)

So what is the difference?

* Arduino 
    * Stores private key in crypto chip
    * Signs JWT with crypto chip
* GCP
    * Stores private key in source
    * Performs crypto routines in software


For simplicity sake I will focus on the Arduino, since it has the 
advantage of using the crypto chip - storage of private key, crypto routines
in hardware. 

## Guide to these notes

For the most part these are unedited.  Newer documents build on earlier 
knowledge.  With that in mind, here is a suggested table of contents:

* First attempt with Wireshark  [crash_dump.md](capture_dump.md)
* Uncategorized notes  [notes.md](notes.md)
* Important URLs  [urls.md](urls.md)
* Big picture [big_picture.md](big_picture.md)
* Arduino example notes [arduino.md](arduino.md)
* GCP example notes [gcp.md](gcp.md)


I should compare the output of these two commands:

* openssl s_client -connect mqtt.2030.ltsapis.goog:8883
* openssl s_client -connect mqtt.googleapis.com:8883

other commands too use
openssl s_client -showcerts -connect www.google.com:443 | less

echo | openssl s_client -showcerts -servername gnupg.org -connect gnupg.org:443 2>/dev/null | openssl x509 -inform pem -noout -text

curl --insecure -vvI https://www.google.com 2>&1 | awk 'BEGIN { cert=0 } /^\* SSL connection/ { cert=1 } /^\*/ { if (cert) print }'

nmap -p 443 --script ssl-cert gnupg.org



