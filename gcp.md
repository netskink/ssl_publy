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


The GCP example mentions the cert urls.  The cloud.google.com/docs on IoT
core refer to pki.goog/root.crt (or whatever the url is) as the site
for the certs.  I used the firmware updater to load the ip address from 
nslookup on pki.goog and perhaps it loaded them or perhaps not.

Still the error persists.


This site has this code
https://github.com/arduino-libraries/WiFi101/issues/217

```
static sint8 burn_certificates(void)
{
	sint8	ret = 0;

	printf(">> De-init WINC device to enter into download mode\r\n");
	m2m_wifi_deinit(NULL);

    if(0 != m2m_wifi_download_mode()) {
		printf("Unable to initialize bus, Press RESET button to try again.\r\n");
		while(1);
	}

	printf(">> WINC entered into download mode\r\n");

	printf("---> Start Certificate Upload on WINC\r\n");

	for (uint8 idx=0; idx < NUM_OF_ROOT_TLS_CHAIN_CERTIFICATES; idx++)
	{
	   /* Write the Root certificates to WINC */
	   if(root_tls_certs_name[idx].cert_type == ROOT_CERT)
	     ret += WriteRootCertificate(root_tls_certs[idx].pu8FileData,root_tls_certs[idx].u32FileSz);

	   /* Write the TLS RSA based certificates to WINC */
       if(root_tls_certs_name[idx].cert_type == TLS_RSA_CERT)
	   {
       	 ret += WriteTlsCertificate(root_tls_certs[idx].pu8FileData,root_tls_certs[idx].u32FileSz,
		 &root_tls_certs[idx+1],root_tls_certs_name[idx].numOfChainCert);
		 idx = idx + root_tls_certs_name[idx].numOfChainCert;
	   }

	   /* Write the TLS ECC based certificates to WINC */
       if(root_tls_certs_name[idx].cert_type == TLS_ECC_CERT)
       {
	       ret += WriteTlsCertificate(NULL,0,&root_tls_certs[idx],root_tls_certs_name[idx].numOfChainCert);
		   idx = idx + root_tls_certs_name[idx].numOfChainCert -1;
       }
    }

	return ret;
}
```
