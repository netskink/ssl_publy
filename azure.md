Endpoint is greenstreamhub.azure-devices.net

$ openssl s_client -showcerts greenstreamhub.azure-devices.net:8883

After that command it will show to certs.  Copy first one to azure.pem
and second one to  Microsoft_RSA_TLS_CA_01.pem



$ openssl x509 -in azure.pem -noout --text

Using the above command shows the following info:

Issuer: C = US, O = Microsoft Corporation, CN = Microsoft RSA TLS CA 01
Subject: CN = *.azure-devices.net


This says, this is the cert for all *.azure-devices.net and it
was issued by MS RSA TLS CA 01.






$ openssl x509 -in Microsoft_RSA_TLS_CA_01.pem -noout --text| less

Using the above command shows the following info:


Issuer: C = IE, O = Baltimore, OU = CyberTrust, CN = Baltimore CyberTrust Root
Subject: C = US, O = Microsoft Corporation, CN = Microsoft RSA TLS CA 01

This says, this is the cert for Microsoft RSA TLS CA 01 and it 
was issued by Baltimore CyberTrust Root.




This url/file shows the PEM for Baltimore CyberTrust Root

https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c

Its the first entry in the file.  Save this portion of the array to Baltimore_Cybertrust_Root.pem







