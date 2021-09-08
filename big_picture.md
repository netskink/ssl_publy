# Big picture of SSL and problem with connecting 
20210822

A site has an SSL cert and a issuing authority.  The issuing authority
cert is provided by google and should be loaded on your computer or
cellphone.  As a client to a SSL/TLS protected server, you need to verify
the certificates of the server.   In the case of a "chain of trust" error
message in your browser, its because a certificate was missing some aspect
of the chain of trust.  Here are examples

* The cert has an issuing authortiy.  The issuing authority has a public
key which can be used to verify the authenticy of the cert bearing its name.
If the key is invalid, its an obvious error.

* The cert and all its certs in the chain of trust need to be either provided
or on the client.  The client does not fetch the certs during the handshake.  
(Or does it? Could it?)

Looking at the roots cert aka roots.pem provided via `https://pki.goog/roots.pem`

It has numerous certs. Around 38.

mqtt.2030.ltsapis.goog:8883

openssl s_client -showcerts mqtt.2030.ltsapis.goog:8883 < /dev/null > mqtt.2030.ltsapis.goog_1.dmp

openssl s_client -showcerts -servername mqtt.2030.ltsapis.goog:8883 -connect mqtt.2030.ltsapis.goog:8883 </dev/null > mqtt.2030.ltsapis.goog_2.dmp 
 
nmap -p 8883 --script ssl-cert mqtt.2030.ltsapis.goog



nmap output with port 8883 and 443 in above command is identical except
for port name:
```
< PORT    STATE SERVICE
< 443/tcp open  https
---
> PORT     STATE SERVICE
> 8883/tcp open  secure-mqtt
```




# mqtt.googleapis.com


Notes about SSL cert from mqtt.googleapis.com

Documentation 
* man openssl
* man openssl-x509
* man x509
* man verify

man x509 and man openssl-x509 show the same page.


## openssl s_client -showcerts mqtt.googleapis.com:8883
```
$ openssl s_client -showcerts mqtt.googleapis.com:8883
CONNECTED(00000003)
depth=2 OU = GlobalSign Root CA - R2, O = GlobalSign, CN = GlobalSign
verify return:1
depth=1 C = US, O = Google Trust Services, CN = GTS CA 1O1
verify return:1
depth=0 C = US, ST = California, L = Mountain View, O = Google LLC, CN = mqtt.googleapis.com
verify return:1
---
Certificate chain
 0 s:C = US, ST = California, L = Mountain View, O = Google LLC, CN = mqtt.googleapis.com
   i:C = US, O = Google Trust Services, CN = GTS CA 1O1
-----BEGIN CERTIFICATE-----
MIIFtTCCBJ2gAwIBAgIQT+XsvAMRU5QFAAAAAIgnoTANBgkqhkiG9w0BAQsFADBC
MQswCQYDVQQGEwJVUzEeMBwGA1UEChMVR29vZ2xlIFRydXN0IFNlcnZpY2VzMRMw
EQYDVQQDEwpHVFMgQ0EgMU8xMB4XDTIxMDgxNjA0MDUwNVoXDTIxMTEwODA0MDUw
NFowbTELMAkGA1UEBhMCVVMxEzARBgNVBAgTCkNhbGlmb3JuaWExFjAUBgNVBAcT
DU1vdW50YWluIFZpZXcxEzARBgNVBAoTCkdvb2dsZSBMTEMxHDAaBgNVBAMTE21x
dHQuZ29vZ2xlYXBpcy5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIB
AQCuZzLrQouQnFoLxDOQEqdrE1GmUhl3BFc3XfoQLhK15Rg4ifmVewwvhPmH8b7h
C/NKTdAiN+P9qp0hBiPDAoT6O+ujKZFN6jsE1K4U4ey/Nci1s3Y1OzjHrd5vQp6S
oKQxnDG/J2SBlfmNbWDoMMp6Lg7/cX8b/FTQOrYosmyRJamwoHWhCTTZjbq/U6aY
5PuA6J4urwFDYpLXVmz+s5dxOiPJFIH3Yp1vlyjGYyqiVJbypSux5pqpV6U2B5iy
ipslt0b5NG1ZVAFp7qbzv6ywICuW1kV9ng+Zi0bRw3s6lgMIfEvnkaZcTMiHw8wp
lODi0Bi9qrCzXGIj/Xkf/nllAgMBAAGjggJ6MIICdjAOBgNVHQ8BAf8EBAMCBaAw
EwYDVR0lBAwwCgYIKwYBBQUHAwEwDAYDVR0TAQH/BAIwADAdBgNVHQ4EFgQUKncm
25WE5PylF2gFs0Z9a06w4BYwHwYDVR0jBBgwFoAUmNH4bhDrz5vsYJ8YkBug630J
/SswaAYIKwYBBQUHAQEEXDBaMCsGCCsGAQUFBzABhh9odHRwOi8vb2NzcC5wa2ku
Z29vZy9ndHMxbzFjb3JlMCsGCCsGAQUFBzAChh9odHRwOi8vcGtpLmdvb2cvZ3Ny
Mi9HVFMxTzEuY3J0MDgGA1UdEQQxMC+CE21xdHQuZ29vZ2xlYXBpcy5jb22CGG1x
dHQtbXRscy5nb29nbGVhcGlzLmNvbTAhBgNVHSAEGjAYMAgGBmeBDAECAjAMBgor
BgEEAdZ5AgUDMDMGA1UdHwQsMCowKKAmoCSGImh0dHA6Ly9jcmwucGtpLmdvb2cv
R1RTMU8xY29yZS5jcmwwggEDBgorBgEEAdZ5AgQCBIH0BIHxAO8AdQCUILwejtWN
bIhzH4KLIiwN0dpNXmxPlD1h204vWE2iwgAAAXtNWVfCAAAEAwBGMEQCIC3dtx3f
QMWA49XFYtOFo6q/nHGj0paxUJxHASp9zNuvAiA5wNkvGYVRGw9c1G6Q03J+CpEm
nPxH9TBFXK1+4nT+HQB2AH0+8viP/4hVaCTCwMqeUol5K8UOeAl/LmqXaJl+IvDX
AAABe01ZWWsAAAQDAEcwRQIhANQktsVeqggQZQC+UKl3crPA8bUsKoLtyYtu1aEx
bmBBAiAuxiGKj6OmW6NY4BEYavesK1mPQqfjsNa5yl8hVrWjEzANBgkqhkiG9w0B
AQsFAAOCAQEAFZSQng/O2uQgwbAjLAqjN3XyA2gUztqwZCZiccUFMhz0eGCHfgNB
h0XqqmfywwEoboLzfZ2KB59Hb/zEyjN0jSePkYRswEb6T10GPMzL/MF6VXk7TrFZ
AdC5Aqimr/lXJn2qBTncSZdpo/ofQwzy2qTTw3t6IbVfhHXXpLkhxi5GrOVuf3Sr
a4tYAQQsebrzuXOp7CnrNkvqBm63OsPRUR8CBW2UH4hoZEiDjoZXyWAD6lKDySDq
lfIpSUd+nh46gY0LwS+bW7DjVg0fyQkmzfelb2AS4xZ2W+8R18jfREq77U4XyeJM
adZjt0szs0+x0azoFXtZ4U01mSbXloDu6Q==
-----END CERTIFICATE-----
 1 s:C = US, O = Google Trust Services, CN = GTS CA 1O1
   i:OU = GlobalSign Root CA - R2, O = GlobalSign, CN = GlobalSign
-----BEGIN CERTIFICATE-----
MIIESjCCAzKgAwIBAgINAeO0mqGNiqmBJWlQuDANBgkqhkiG9w0BAQsFADBMMSAw
HgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEGA1UEChMKR2xvYmFs
U2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjAeFw0xNzA2MTUwMDAwNDJaFw0yMTEy
MTUwMDAwNDJaMEIxCzAJBgNVBAYTAlVTMR4wHAYDVQQKExVHb29nbGUgVHJ1c3Qg
U2VydmljZXMxEzARBgNVBAMTCkdUUyBDQSAxTzEwggEiMA0GCSqGSIb3DQEBAQUA
A4IBDwAwggEKAoIBAQDQGM9F1IvN05zkQO9+tN1pIRvJzzyOTHW5DzEZhD2ePCnv
UA0Qk28FgICfKqC9EksC4T2fWBYk/jCfC3R3VZMdS/dN4ZKCEPZRrAzDsiKUDzRr
mBBJ5wudgzndIMYcLe/RGGFl5yODIKgjEv/SJH/UL+dEaltN11BmsK+eQmMF++Ac
xGNhr59qM/9il71I2dN8FGfcddwuaej4bXhp0LcQBbjxMcI7JP0aM3T4I+DsaxmK
FsbjzaTNC9uzpFlgOIg7rR25xoynUxv8vNmkq7zdPGHXkxWY7oG9j+JkRyBABk7X
rJfoucBZEqFJJSPk7XA0LKW0Y3z5oz2D0c1tJKwHAgMBAAGjggEzMIIBLzAOBgNV
HQ8BAf8EBAMCAYYwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMBIGA1Ud
EwEB/wQIMAYBAf8CAQAwHQYDVR0OBBYEFJjR+G4Q68+b7GCfGJAboOt9Cf0rMB8G
A1UdIwQYMBaAFJviB1dnHB7AagbeWbSaLd/cGYYuMDUGCCsGAQUFBwEBBCkwJzAl
BggrBgEFBQcwAYYZaHR0cDovL29jc3AucGtpLmdvb2cvZ3NyMjAyBgNVHR8EKzAp
MCegJaAjhiFodHRwOi8vY3JsLnBraS5nb29nL2dzcjIvZ3NyMi5jcmwwPwYDVR0g
BDgwNjA0BgZngQwBAgIwKjAoBggrBgEFBQcCARYcaHR0cHM6Ly9wa2kuZ29vZy9y
ZXBvc2l0b3J5LzANBgkqhkiG9w0BAQsFAAOCAQEAGoA+Nnn78y6pRjd9XlQWNa7H
TgiZ/r3RNGkmUmYHPQq6Scti9PEajvwRT2iWTHQr02fesqOqBY2ETUwgZQ+lltoN
FvhsO9tvBCOIazpswWC9aJ9xju4tWDQH8NVU6YZZ/XteDSGU9YzJqPjY8q3MDxrz
mqepBCf5o8mw/wJ4a2G6xzUr6Fb6T8McDO22PLRL6u3M4Tzs3A2M1j6bykJYi8wW
IRdAvKLWZu/axBVbzYmqmwkm5zLSDW5nIAJbELCQCZwMH56t2Dvqofxs6BBcCFIZ
USpxu6x6td0V7SvJCCosirSmIatj/9dSSVDQibet8q/7UK4v4ZUN80atnZz1yg==
-----END CERTIFICATE-----
---
Server certificate
subject=C = US, ST = California, L = Mountain View, O = Google LLC, CN = mqtt.googleapis.com

issuer=C = US, O = Google Trust Services, CN = GTS CA 1O1

---
No client certificate CA names sent
Peer signing digest: SHA256
Peer signature type: RSA-PSS
Server Temp Key: X25519, 253 bits
---
SSL handshake has read 3062 bytes and written 391 bytes
Verification: OK
---
New, TLSv1.3, Cipher is TLS_AES_256_GCM_SHA384
Server public key is 2048 bit
Secure Renegotiation IS NOT supported
Compression: NONE
Expansion: NONE
No ALPN negotiated
Early data was not sent
Verify return code: 0 (ok)
---
read:errno=0
davis@twenty:~/progs/MkrNb1500_diag
```


## openssl s_client -showcerts -servername mqtt.googleapis.com:8883 -connect mqtt.2030.ltsapis.goog:8883 </dev/null 

Produces essentially the same output as above



## nmap -p 8883 --script ssl-cert mqtt.googleapis.com

```
$ nmap -p 8883 --script ssl-cert mqtt.googleapis.com
Starting Nmap 7.70 ( https://nmap.org ) at 2021-09-05 17:16 EDT
Nmap scan report for mqtt.googleapis.com (74.125.69.206)
Host is up (0.059s latency).
Other addresses for mqtt.googleapis.com (not scanned): 74.125.69.206 74.125.69.206 74.125.69.206 2607:f8b0:4001:c08::ce 2607:f8b0:4001:c08::ce 2607:f8b0:4001:c08::ce 2607:f8b0:4001:c08::ce
rDNS record for 74.125.69.206: iq-in-f206.1e100.net

PORT     STATE SERVICE
8883/tcp open  secure-mqtt
| ssl-cert: Subject: commonName=mqtt.googleapis.com/organizationName=Google LLC/stateOrProvinceName=California/countryName=US
| Subject Alternative Name: DNS:mqtt.googleapis.com, DNS:mqtt-mtls.googleapis.com
| Issuer: commonName=GTS CA 1O1/organizationName=Google Trust Services/countryName=US
| Public Key type: rsa
| Public Key bits: 2048
| Signature Algorithm: sha256WithRSAEncryption
| Not valid before: 2021-08-16T04:05:05
| Not valid after:  2021-11-08T04:05:04
| MD5:   d67c efeb 7968 1e9a 0a7f 466f 89f9 1fe3
|_SHA-1: e8af 2e56 71da 1899 96ca 3d35 7dad 3248 51e8 2e67

Nmap done: 1 IP address (1 host up) scanned in 0.50 seconds
```


## Create a crt file for google

openssl shows two certs. one is intermediate and the other is the server.

copy and paste the BEGIN/END text and put in file named 

```
$ cat GTS_CA_101.crt
-----BEGIN CERTIFICATE-----
MIIFtTCCBJ2gAwIBAgIQT+XsvAMRU5QFAAAAAIgnoTANBgkqhkiG9w0BAQsFADBC
MQswCQYDVQQGEwJVUzEeMBwGA1UEChMVR29vZ2xlIFRydXN0IFNlcnZpY2VzMRMw
EQYDVQQDEwpHVFMgQ0EgMU8xMB4XDTIxMDgxNjA0MDUwNVoXDTIxMTEwODA0MDUw
NFowbTELMAkGA1UEBhMCVVMxEzARBgNVBAgTCkNhbGlmb3JuaWExFjAUBgNVBAcT
DU1vdW50YWluIFZpZXcxEzARBgNVBAoTCkdvb2dsZSBMTEMxHDAaBgNVBAMTE21x
dHQuZ29vZ2xlYXBpcy5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIB
AQCuZzLrQouQnFoLxDOQEqdrE1GmUhl3BFc3XfoQLhK15Rg4ifmVewwvhPmH8b7h
C/NKTdAiN+P9qp0hBiPDAoT6O+ujKZFN6jsE1K4U4ey/Nci1s3Y1OzjHrd5vQp6S
oKQxnDG/J2SBlfmNbWDoMMp6Lg7/cX8b/FTQOrYosmyRJamwoHWhCTTZjbq/U6aY
5PuA6J4urwFDYpLXVmz+s5dxOiPJFIH3Yp1vlyjGYyqiVJbypSux5pqpV6U2B5iy
ipslt0b5NG1ZVAFp7qbzv6ywICuW1kV9ng+Zi0bRw3s6lgMIfEvnkaZcTMiHw8wp
lODi0Bi9qrCzXGIj/Xkf/nllAgMBAAGjggJ6MIICdjAOBgNVHQ8BAf8EBAMCBaAw
EwYDVR0lBAwwCgYIKwYBBQUHAwEwDAYDVR0TAQH/BAIwADAdBgNVHQ4EFgQUKncm
25WE5PylF2gFs0Z9a06w4BYwHwYDVR0jBBgwFoAUmNH4bhDrz5vsYJ8YkBug630J
/SswaAYIKwYBBQUHAQEEXDBaMCsGCCsGAQUFBzABhh9odHRwOi8vb2NzcC5wa2ku
Z29vZy9ndHMxbzFjb3JlMCsGCCsGAQUFBzAChh9odHRwOi8vcGtpLmdvb2cvZ3Ny
Mi9HVFMxTzEuY3J0MDgGA1UdEQQxMC+CE21xdHQuZ29vZ2xlYXBpcy5jb22CGG1x
dHQtbXRscy5nb29nbGVhcGlzLmNvbTAhBgNVHSAEGjAYMAgGBmeBDAECAjAMBgor
BgEEAdZ5AgUDMDMGA1UdHwQsMCowKKAmoCSGImh0dHA6Ly9jcmwucGtpLmdvb2cv
R1RTMU8xY29yZS5jcmwwggEDBgorBgEEAdZ5AgQCBIH0BIHxAO8AdQCUILwejtWN
bIhzH4KLIiwN0dpNXmxPlD1h204vWE2iwgAAAXtNWVfCAAAEAwBGMEQCIC3dtx3f
QMWA49XFYtOFo6q/nHGj0paxUJxHASp9zNuvAiA5wNkvGYVRGw9c1G6Q03J+CpEm
nPxH9TBFXK1+4nT+HQB2AH0+8viP/4hVaCTCwMqeUol5K8UOeAl/LmqXaJl+IvDX
AAABe01ZWWsAAAQDAEcwRQIhANQktsVeqggQZQC+UKl3crPA8bUsKoLtyYtu1aEx
bmBBAiAuxiGKj6OmW6NY4BEYavesK1mPQqfjsNa5yl8hVrWjEzANBgkqhkiG9w0B
AQsFAAOCAQEAFZSQng/O2uQgwbAjLAqjN3XyA2gUztqwZCZiccUFMhz0eGCHfgNB
h0XqqmfywwEoboLzfZ2KB59Hb/zEyjN0jSePkYRswEb6T10GPMzL/MF6VXk7TrFZ
AdC5Aqimr/lXJn2qBTncSZdpo/ofQwzy2qTTw3t6IbVfhHXXpLkhxi5GrOVuf3Sr
a4tYAQQsebrzuXOp7CnrNkvqBm63OsPRUR8CBW2UH4hoZEiDjoZXyWAD6lKDySDq
lfIpSUd+nh46gY0LwS+bW7DjVg0fyQkmzfelb2AS4xZ2W+8R18jfREq77U4XyeJM
adZjt0szs0+x0azoFXtZ4U01mSbXloDu6Q==
-----END CERTIFICATE-----
```

Then make the der file

```
openssl x509 -in GTS_CA_101.crt -outform der -out GTS_CA_101.der
```

Can you make one combined DER?

make the following file below and was able to issue a command
to make one file of both certs?

```
$ openssl x509 -in GCP_COMBINED.crt -outform der -out GCP_COMBINED.der
```


```
$ cat GCP_COMBINED.crt
---
Certificate chain
 0 s:C = US, ST = California, L = Mountain View, O = Google LLC, CN = mqtt.googleapis.com
   i:C = US, O = Google Trust Services, CN = GTS CA 1O1
-----BEGIN CERTIFICATE-----
MIIFtTCCBJ2gAwIBAgIQT+XsvAMRU5QFAAAAAIgnoTANBgkqhkiG9w0BAQsFADBC
MQswCQYDVQQGEwJVUzEeMBwGA1UEChMVR29vZ2xlIFRydXN0IFNlcnZpY2VzMRMw
EQYDVQQDEwpHVFMgQ0EgMU8xMB4XDTIxMDgxNjA0MDUwNVoXDTIxMTEwODA0MDUw
NFowbTELMAkGA1UEBhMCVVMxEzARBgNVBAgTCkNhbGlmb3JuaWExFjAUBgNVBAcT
DU1vdW50YWluIFZpZXcxEzARBgNVBAoTCkdvb2dsZSBMTEMxHDAaBgNVBAMTE21x
dHQuZ29vZ2xlYXBpcy5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIB
AQCuZzLrQouQnFoLxDOQEqdrE1GmUhl3BFc3XfoQLhK15Rg4ifmVewwvhPmH8b7h
C/NKTdAiN+P9qp0hBiPDAoT6O+ujKZFN6jsE1K4U4ey/Nci1s3Y1OzjHrd5vQp6S
oKQxnDG/J2SBlfmNbWDoMMp6Lg7/cX8b/FTQOrYosmyRJamwoHWhCTTZjbq/U6aY
5PuA6J4urwFDYpLXVmz+s5dxOiPJFIH3Yp1vlyjGYyqiVJbypSux5pqpV6U2B5iy
ipslt0b5NG1ZVAFp7qbzv6ywICuW1kV9ng+Zi0bRw3s6lgMIfEvnkaZcTMiHw8wp
lODi0Bi9qrCzXGIj/Xkf/nllAgMBAAGjggJ6MIICdjAOBgNVHQ8BAf8EBAMCBaAw
EwYDVR0lBAwwCgYIKwYBBQUHAwEwDAYDVR0TAQH/BAIwADAdBgNVHQ4EFgQUKncm
25WE5PylF2gFs0Z9a06w4BYwHwYDVR0jBBgwFoAUmNH4bhDrz5vsYJ8YkBug630J
/SswaAYIKwYBBQUHAQEEXDBaMCsGCCsGAQUFBzABhh9odHRwOi8vb2NzcC5wa2ku
Z29vZy9ndHMxbzFjb3JlMCsGCCsGAQUFBzAChh9odHRwOi8vcGtpLmdvb2cvZ3Ny
Mi9HVFMxTzEuY3J0MDgGA1UdEQQxMC+CE21xdHQuZ29vZ2xlYXBpcy5jb22CGG1x
dHQtbXRscy5nb29nbGVhcGlzLmNvbTAhBgNVHSAEGjAYMAgGBmeBDAECAjAMBgor
BgEEAdZ5AgUDMDMGA1UdHwQsMCowKKAmoCSGImh0dHA6Ly9jcmwucGtpLmdvb2cv
R1RTMU8xY29yZS5jcmwwggEDBgorBgEEAdZ5AgQCBIH0BIHxAO8AdQCUILwejtWN
bIhzH4KLIiwN0dpNXmxPlD1h204vWE2iwgAAAXtNWVfCAAAEAwBGMEQCIC3dtx3f
QMWA49XFYtOFo6q/nHGj0paxUJxHASp9zNuvAiA5wNkvGYVRGw9c1G6Q03J+CpEm
nPxH9TBFXK1+4nT+HQB2AH0+8viP/4hVaCTCwMqeUol5K8UOeAl/LmqXaJl+IvDX
AAABe01ZWWsAAAQDAEcwRQIhANQktsVeqggQZQC+UKl3crPA8bUsKoLtyYtu1aEx
bmBBAiAuxiGKj6OmW6NY4BEYavesK1mPQqfjsNa5yl8hVrWjEzANBgkqhkiG9w0B
AQsFAAOCAQEAFZSQng/O2uQgwbAjLAqjN3XyA2gUztqwZCZiccUFMhz0eGCHfgNB
h0XqqmfywwEoboLzfZ2KB59Hb/zEyjN0jSePkYRswEb6T10GPMzL/MF6VXk7TrFZ
AdC5Aqimr/lXJn2qBTncSZdpo/ofQwzy2qTTw3t6IbVfhHXXpLkhxi5GrOVuf3Sr
a4tYAQQsebrzuXOp7CnrNkvqBm63OsPRUR8CBW2UH4hoZEiDjoZXyWAD6lKDySDq
lfIpSUd+nh46gY0LwS+bW7DjVg0fyQkmzfelb2AS4xZ2W+8R18jfREq77U4XyeJM
adZjt0szs0+x0azoFXtZ4U01mSbXloDu6Q==
-----END CERTIFICATE-----
 1 s:C = US, O = Google Trust Services, CN = GTS CA 1O1
   i:OU = GlobalSign Root CA - R2, O = GlobalSign, CN = GlobalSign
-----BEGIN CERTIFICATE-----
MIIESjCCAzKgAwIBAgINAeO0mqGNiqmBJWlQuDANBgkqhkiG9w0BAQsFADBMMSAw
HgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEGA1UEChMKR2xvYmFs
U2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjAeFw0xNzA2MTUwMDAwNDJaFw0yMTEy
MTUwMDAwNDJaMEIxCzAJBgNVBAYTAlVTMR4wHAYDVQQKExVHb29nbGUgVHJ1c3Qg
U2VydmljZXMxEzARBgNVBAMTCkdUUyBDQSAxTzEwggEiMA0GCSqGSIb3DQEBAQUA
A4IBDwAwggEKAoIBAQDQGM9F1IvN05zkQO9+tN1pIRvJzzyOTHW5DzEZhD2ePCnv
UA0Qk28FgICfKqC9EksC4T2fWBYk/jCfC3R3VZMdS/dN4ZKCEPZRrAzDsiKUDzRr
mBBJ5wudgzndIMYcLe/RGGFl5yODIKgjEv/SJH/UL+dEaltN11BmsK+eQmMF++Ac
xGNhr59qM/9il71I2dN8FGfcddwuaej4bXhp0LcQBbjxMcI7JP0aM3T4I+DsaxmK
FsbjzaTNC9uzpFlgOIg7rR25xoynUxv8vNmkq7zdPGHXkxWY7oG9j+JkRyBABk7X
rJfoucBZEqFJJSPk7XA0LKW0Y3z5oz2D0c1tJKwHAgMBAAGjggEzMIIBLzAOBgNV
HQ8BAf8EBAMCAYYwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMBIGA1Ud
EwEB/wQIMAYBAf8CAQAwHQYDVR0OBBYEFJjR+G4Q68+b7GCfGJAboOt9Cf0rMB8G
A1UdIwQYMBaAFJviB1dnHB7AagbeWbSaLd/cGYYuMDUGCCsGAQUFBwEBBCkwJzAl
BggrBgEFBQcwAYYZaHR0cDovL29jc3AucGtpLmdvb2cvZ3NyMjAyBgNVHR8EKzAp
MCegJaAjhiFodHRwOi8vY3JsLnBraS5nb29nL2dzcjIvZ3NyMi5jcmwwPwYDVR0g
BDgwNjA0BgZngQwBAgIwKjAoBggrBgEFBQcCARYcaHR0cHM6Ly9wa2kuZ29vZy9y
ZXBvc2l0b3J5LzANBgkqhkiG9w0BAQsFAAOCAQEAGoA+Nnn78y6pRjd9XlQWNa7H
TgiZ/r3RNGkmUmYHPQq6Scti9PEajvwRT2iWTHQr02fesqOqBY2ETUwgZQ+lltoN
FvhsO9tvBCOIazpswWC9aJ9xju4tWDQH8NVU6YZZ/XteDSGU9YzJqPjY8q3MDxrz
mqepBCf5o8mw/wJ4a2G6xzUr6Fb6T8McDO22PLRL6u3M4Tzs3A2M1j6bykJYi8wW
IRdAvKLWZu/axBVbzYmqmwkm5zLSDW5nIAJbELCQCZwMH56t2Dvqofxs6BBcCFIZ
USpxu6x6td0V7SvJCCosirSmIatj/9dSSVDQibet8q/7UK4v4ZUN80atnZz1yg==
-----END CERTIFICATE-----
---
```

converting to c byte array syntax

```
od -t x1 -An GCP_COMBINED.der | awk '

{

    for (i = 1; i <= 16; i++)
        printf "0x%s,", $i
    print ""
}
'

```


# Notes on SSL file extensions

X.509 is standard that defines certificate structure

Formats:

* PEM
* PKCS#7
* DER
* PKCS#12

PEM/PKCS#7 uses Base64 ASCII encoding

DER/PKCS#12 uses binary

## File extensions

Notes from https://knowledge.digicert.com/generalinformation/INFO2824.html

### PEM 
* .pem
* .crt  Base64 encoded X.509 certificate
* .cer  DER encoded binary X.509 certificate 
* .key
* .csr - certicate signing request.  Used to submit request to CA
* .crl - certicate revocation list - Designates a certificate that has been revoked

PEM files can include:
* server certificate
* intermediate certificate
* private key

The BEGIN text keyword can be
* CERTIFICATE
* KEY
* CERTIFICATE REQUEST

### PKCS#7
* .p7b
* .p7c

Cryptographic Message Syntax Standard
Storage of all certificate in path and does not store private keys

### DER
* .der
* .cer

These are binary files mainly used by Java webservers

DER-encoded binary X.509 Certificate

It does not support storage of private keys

### PKCS#12
* .pfx
* .p12

Supports storage of private/public keys and all certifcates in path.  These allow export 
of a certificate and retain full private key functionnality.
