# Google Example Notes
20210821

1. cloned the github repo here. added to .gitignore
2. ran install.sh script to see what it did.  It seems it is installing software
3. noticed its taking a while to install.  
4. Now its using python. whew lad I hope its using the correct python.
5. completed
6. changed to `~/progs/ssl_publy/google-cloud-iot-arduino/examples/MKR1000-lwmqtt`
7. Copied this example to `~/progs/ssl_publy/gcp-example/`
8. Copied arduino secrets file and makefile from aruduino example to here
9. Tested with make and it compiles.


## Second attempt at the project repo readme instructions


# Notes on Firmware and GCP keys

## Creating the Device Key

From the GoogleCloudPlatform/google-cloud-iot-arduino

Generate a EC256 key - eliptical curve

```
cd keys/
openssl ecparam -genkey -name prime256v1 -noout -out ec_private.pem
openssl ec -in ec_private.pem -pubout -out ec_public.pem
```

Results in two files:
* ec_private.pem
* ec_public.pem


## GCP usage of public key to identify the arduino

This creates a device in the IoT Core Registry.  The command
uses the public key created above.

```
gcloud iot devices create atest-dev  --region=us-central1 \
    --registry=atest-registry \
    --public-key path=ec_public.pem,type=es256
```

## Arduino usage of public/private key in software
Do this to get data for private key entry in arduino code

```
cd keys/
openssl ec -in ec_private.pem -noout -text
```

Result looks like this:

```
read EC key
Private-Key: (256 bit)
priv:
    XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:
    XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:
    XX:XX
pub:
    XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:
    XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:
    XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:
    XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:XX:
    XX:XX:XX:XX:XX
ASN1 OID: prime256v1
NIST CURVE: P-256
```


