openssl s_client -showcerts mqtt.googleapis.com:8883 | less

These are the items of interest

Certificate chain
 0 s:CN = mqtt.googleapis.com
   i:C = US, O = Google Trust Services LLC, CN = GTS CA 1C3
-----BEGIN CERTIFICATE-----
MIIFdzCCBF+gAwIBAgIRAIcbHMd3L255CgAAAAD8+IMwDQYJKoZIhvcNAQELBQAw
RjELMAkGA1UEBhMCVVMxIjAgBgNVBAoTGUdvb2dsZSBUcnVzdCBTZXJ2aWNlcyBM
TEMxEzARBgNVBAMTCkdUUyBDQSAxQzMwHhcNMjEwODMwMDQwMzU1WhcNMjExMTIy
MDQwMzU0WjAeMRwwGgYDVQQDExNtcXR0Lmdvb2dsZWFwaXMuY29tMIIBIjANBgkq
hkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAyjn2+x3dKpy+eeo/4qcxlpP9CY/Q3a+d
nzuzaMxNl9aaxd7ahi+t3XzIghnAPEjtXX8P50tzKueWMNH4fBOIR9FrTgy/yqbV
V4zgMdvWXh4jUa+o3Ob4jzEB3U4BqhVvBr8JutGVgr0vvdG/jvBPVg2m/bYpN8cM
2IbTU7tl27+hkI7WrHicdCgdpFR0WZPo7r35DPuZn8N8DXFj9pLwFh0dHO8O75K+
1ulVHXb8NKN9PYIp43l0yGJxFfY7tpYDrwqCKFt7vN6YkNKB7h8/Yi3q4fpy0SKt
dCH5DP9CFyJV0wHlPI0YTPA1X+8EvIUcsJ/xIzpkA1xRiik7+aftNQIDAQABo4IC
hjCCAoIwDgYDVR0PAQH/BAQDAgWgMBMGA1UdJQQMMAoGCCsGAQUFBwMBMAwGA1Ud
EwEB/wQCMAAwHQYDVR0OBBYEFGAc477Rr6AZ3RS7Y0jODwu2D9DZMB8GA1UdIwQY
MBaAFIp0f6+Fze6VzT2c0OJGFPNxNR0nMGoGCCsGAQUFBwEBBF4wXDAnBggrBgEF
BQcwAYYbaHR0cDovL29jc3AucGtpLmdvb2cvZ3RzMWMzMDEGCCsGAQUFBzAChiVo
dHRwOi8vcGtpLmdvb2cvcmVwby9jZXJ0cy9ndHMxYzMuZGVyMDgGA1UdEQQxMC+C
E21xdHQuZ29vZ2xlYXBpcy5jb22CGG1xdHQtbXRscy5nb29nbGVhcGlzLmNvbTAh
BgNVHSAEGjAYMAgGBmeBDAECATAMBgorBgEEAdZ5AgUDMDwGA1UdHwQ1MDMwMaAv
oC2GK2h0dHA6Ly9jcmxzLnBraS5nb29nL2d0czFjMy9tb1ZEZklTaWEyay5jcmww
ggEEBgorBgEEAdZ5AgQCBIH1BIHyAPAAdwD2XJQv0XcwIhRUGAgwlFaO400TGTO/
3wwvIAvMTvFk4wAAAXuVcU8HAAAEAwBIMEYCIQDFJv54j7V1n0MZ3agzycJ8sbiG
NrUt+qIHMHSM63QrygIhAKoVX9HXWWZ7AIVXcGDwHi1zsIw5r2oPH+E9nXpzA/e9
AHUA7sCV7o1yZA+S48O5G8cSo2lqCXtLahoUOOZHssvtxfkAAAF7lXFTTgAABAMA
RjBEAiBDvmD9yDw1/L5sPMq/zxLDnd9w2Yo4hXR3CCf3d/edsQIgPgA/NOSLGWyq
rwhwEkcbx0GIaKunvVeYA+wn7QPAkbEwDQYJKoZIhvcNAQELBQADggEBAE/pNh7t
duWTbw/aSBm7zkG390bl0gMwKBfc3Vbi5IcBNPTWHKclcx278fqdQaEL0kJmp/j3
O+lAjJKFLt2oHHOmsMzbAeE/gIKdFP9HjNzADwkXO0SR0VJ5nLAN5JRYIBVZaPy2
0jRm6dzj0/IYDwuWShFfvUKjoxn1Vrei12pTbkD3XQ75wgECTNRAxUoCNGNFO7/P
b6DA+3tnUHN7rgs1ZkqfPVFVhO7I4Pk5V7yX/AfD5V/jhFhek7ongp3w8aPd6udi
ouV59UJjXsQFljNt87JCAEAoYznq3/WaA/0dGu6UqtWqxPzrPkpWy+0YykRqSEBe
qMB6abLIhjXD8Jw=
-----END CERTIFICATE-----


1 s:C = US, O = Google Trust Services LLC, CN = GTS CA 1C3
   i:C = US, O = Google Trust Services LLC, CN = GTS Root R1
-----BEGIN CERTIFICATE-----
MIIFljCCA36gAwIBAgINAgO8U1lrNMcY9QFQZjANBgkqhkiG9w0BAQsFADBHMQsw
CQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEU
MBIGA1UEAxMLR1RTIFJvb3QgUjEwHhcNMjAwODEzMDAwMDQyWhcNMjcwOTMwMDAw
MDQyWjBGMQswCQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZp
Y2VzIExMQzETMBEGA1UEAxMKR1RTIENBIDFDMzCCASIwDQYJKoZIhvcNAQEBBQAD
ggEPADCCAQoCggEBAPWI3+dijB43+DdCkH9sh9D7ZYIl/ejLa6T/belaI+KZ9hzp
kgOZE3wJCor6QtZeViSqejOEH9Hpabu5dOxXTGZok3c3VVP+ORBNtzS7XyV3NzsX
lOo85Z3VvMO0Q+sup0fvsEQRY9i0QYXdQTBIkxu/t/bgRQIh4JZCF8/ZK2VWNAcm
BA2o/X3KLu/qSHw3TT8An4Pf73WELnlXXPxXbhqW//yMmqaZviXZf5YsBvcRKgKA
gOtjGDxQSYflispfGStZloEAoPtR28p3CwvJlk/vcEnHXG0g/Zm0tOLKLnf9LdwL
tmsTDIwZKxeWmLnwi/agJ7u2441Rj72ux5uxiZ0CAwEAAaOCAYAwggF8MA4GA1Ud
DwEB/wQEAwIBhjAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwEgYDVR0T
AQH/BAgwBgEB/wIBADAdBgNVHQ4EFgQUinR/r4XN7pXNPZzQ4kYU83E1HScwHwYD
VR0jBBgwFoAU5K8rJnEaK0gnhS9SZizv8IkTcT4waAYIKwYBBQUHAQEEXDBaMCYG
CCsGAQUFBzABhhpodHRwOi8vb2NzcC5wa2kuZ29vZy9ndHNyMTAwBggrBgEFBQcw
AoYkaHR0cDovL3BraS5nb29nL3JlcG8vY2VydHMvZ3RzcjEuZGVyMDQGA1UdHwQt
MCswKaAnoCWGI2h0dHA6Ly9jcmwucGtpLmdvb2cvZ3RzcjEvZ3RzcjEuY3JsMFcG
A1UdIARQME4wOAYKKwYBBAHWeQIFAzAqMCgGCCsGAQUFBwIBFhxodHRwczovL3Br
aS5nb29nL3JlcG9zaXRvcnkvMAgGBmeBDAECATAIBgZngQwBAgIwDQYJKoZIhvcN
AQELBQADggIBAIl9rCBcDDy+mqhXlRu0rvqrpXJxtDaV/d9AEQNMwkYUuxQkq/BQ
cSLbrcRuf8/xam/IgxvYzolfh2yHuKkMo5uhYpSTld9brmYZCwKWnvy15xBpPnrL
RklfRuFBsdeYTWU0AIAaP0+fbH9JAIFTQaSSIYKCGvGjRFsqUBITTcFTNvNCCK9U
+o53UxtkOCcXCb1YyRt8OS1b887U7ZfbFAO/CVMkH8IMBHmYJvJh8VNS/UKMG2Yr
PxWhu//2m+OBmgEGcYk1KCTd4b3rGS3hSMs9WYNRtHTGnXzGsYZbr8w0xNPM1IER
lQCh9BIiAfq0g3GvjLeMcySsN1PCAJA/Ef5c7TaUEDu9Ka7ixzpiO2xj2YC/WXGs
Yye5TBeg2vZzFb8q3o/zpWwygTMD0IZRcZk0upONXbVRWPeyk+gB9lm+cZv9TSjO
z23HFtz30dZGm6fKa+l3D/2gthsjgx0QGtkJAITgRNOidSOzNIb2ILCkXhAd4FJG
AJ2xDx8hcFH1mt0G/FX0Kw4zd8NLQsLxdxP8c4CU6x+7Nz/OAipmsHMdMqUybDKw
juDEI/9bfU1lcKwrmz3O2+BtjjKAvpafkmO8l7tdufThcV4q5O8DIrGKZTqPwJNl
1IXNDw9bg1kWRxYtnCQ6yICmJhSFm/Y3m6xv+cXDBlHz4n/FsRC6UfTd
-----END CERTIFICATE-----


 2 s:C = US, O = Google Trust Services LLC, CN = GTS Root R1
   i:C = BE, O = GlobalSign nv-sa, OU = Root CA, CN = GlobalSign Root CA
-----BEGIN CERTIFICATE-----
MIIFYjCCBEqgAwIBAgIQd70NbNs2+RrqIQ/E8FjTDTANBgkqhkiG9w0BAQsFADBX
MQswCQYDVQQGEwJCRTEZMBcGA1UEChMQR2xvYmFsU2lnbiBudi1zYTEQMA4GA1UE
CxMHUm9vdCBDQTEbMBkGA1UEAxMSR2xvYmFsU2lnbiBSb290IENBMB4XDTIwMDYx
OTAwMDA0MloXDTI4MDEyODAwMDA0MlowRzELMAkGA1UEBhMCVVMxIjAgBgNVBAoT
GUdvb2dsZSBUcnVzdCBTZXJ2aWNlcyBMTEMxFDASBgNVBAMTC0dUUyBSb290IFIx
MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAthECix7joXebO9y/lD63
ladAPKH9gvl9MgaCcfb2jH/76Nu8ai6Xl6OMS/kr9rH5zoQdsfnFl97vufKj6bwS
iV6nqlKr+CMny6SxnGPb15l+8Ape62im9MZaRw1NEDPjTrETo8gYbEvs/AmQ351k
KSUjB6G00j0uYODP0gmHu81I8E3CwnqIiru6z1kZ1q+PsAewnjHxgsHA3y6mbWwZ
DrXYfiYaRQM9sHmklCitD38m5agI/pboPGiUU+6DOogrFZYJsuB6jC511pzrp1Zk
j5ZPaK49l8KEj8C8QMALXL32h7M1bKwYUH+E4EzNktMg6TO8UpmvMrUpsyUqtEj5
cuHKZPfmghCN6J3Cioj6OGaK/GP5Afl4/Xtcd/p2h/rs37EOeZVXtL0m79YB0esW
CruOC7XFxYpVq9Os6pFLKcwZpDIlTirxZUTQAs6qzkm06p98g7BAe+dDq6dso499
iYH6TKX/1Y7DzkvgtdizjkXPdsDtQCv9Uw+wp9U7DbGKogPeMa3Md+pvez7W35Ei
Eua++tgy/BBjFFFy3l3WFpO9KWgz7zpm7AeKJt8T11dleCfeXkkUAKIAf5qoIbap
sZWwpbkNFhHax2xIPEDgfg1azVY80ZcFuctL7TlLnMQ/0lUTbiSw1nH69MG6zO0b
9f6BQdgAmD06yK56mDcYBZUCAwEAAaOCATgwggE0MA4GA1UdDwEB/wQEAwIBhjAP
BgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBTkrysmcRorSCeFL1JmLO/wiRNxPjAf
BgNVHSMEGDAWgBRge2YaRQ2XyolQL30EzTSo//z9SzBgBggrBgEFBQcBAQRUMFIw
JQYIKwYBBQUHMAGGGWh0dHA6Ly9vY3NwLnBraS5nb29nL2dzcjEwKQYIKwYBBQUH
MAKGHWh0dHA6Ly9wa2kuZ29vZy9nc3IxL2dzcjEuY3J0MDIGA1UdHwQrMCkwJ6Al
oCOGIWh0dHA6Ly9jcmwucGtpLmdvb2cvZ3NyMS9nc3IxLmNybDA7BgNVHSAENDAy
MAgGBmeBDAECATAIBgZngQwBAgIwDQYLKwYBBAHWeQIFAwIwDQYLKwYBBAHWeQIF
AwMwDQYJKoZIhvcNAQELBQADggEBADSkHrEoo9C0dhemMXoh6dFSPsjbdBZBiLg9
NR3t5P+T4Vxfq7vqfM/b5A3Ri1fyJm9bvhdGaJQ3b2t6yMAYN/olUazsaL+yyEn9
WprKASOshIArAoyZl+tJaox118fessmXn1hIVw41oeQa1v1vg4Fv74zPl6/AhSrw
9U5pCZEt4Wi4wStz6dTZ/CLANx8LZh1J7QJVj2fhMtfTJr9w4z30Z209fOU0iOMy
+qduBmpvvYuR7hZL6Dupszfnw0Skfths18dG9ZKb59UhvmaSGZRVbNQpsg3BZlvi
d0lIKO2d1xozclOzgjXPYovJJIultzkMu34qQb9Sz/yilrbCgj8=
-----END CERTIFICATE-----



Take these three pem's and make pem files.  Take text starting/including 
---BEGIN up to text line ending/including --END and put in files:
one.pem, two.pem, three.pem.


Run this command on each pem file.  Take note of the CN field
and rename accordingly.  
$ openssl x509 -in one.pem -noout --text | less

This one has CN=mqtt.googelapis.com so rename it to mqtt_googleapis_com.pem


$ openssl x509 -in two.pem -noout --text | grep CN
        Issuer: C = US, O = Google Trust Services LLC, CN = GTS Root R1
        Subject: C = US, O = Google Trust Services LLC, CN = GTS CA 1C3

So rename two.pem to GTS_CA_1C3.pem


$ openssl x509 -in three.pem -noout --text | grep CN
        Issuer: C = BE, O = GlobalSign nv-sa, OU = Root CA, CN = GlobalSign Root CA
        Subject: C = US, O = Google Trust Services LLC, CN = GTS Root R1

so rename three.pem to GST_ROOT_R1.pem



Convert two of three pem files to der files

$ ./convert_pem_to_der.sh GTS_ROOT_R1.pem
davis@twenty:~/progs/ssl_publy/certs
$ ./convert_pem_to_der.sh GTS_CA_1C3.pem

Convert the der files to byte arrays.  Determine length and modify the NBRootCerts.h file (or whatever the name is) 
in the MKRNB/utilty dir.

$ ./make_hex.sh GTS_ROOT_R1.der > foo.txt

Need to remove trailing zeros and determine count.  I use vim with line numbering to multply last full line by 16. 
Then add the number of bytes in last line.

$ vi ~/Arduino/libraries/MKRNB/src/utility/NBRootCerts.h foo.txt


