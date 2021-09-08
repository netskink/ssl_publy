Hello

I am trying to figure out how to fix the GCP IoT core connection problem with a MKR NB 1500.   I was able to get the MKR1000 to connect to GCP IoT core using the arduino example and the GCP example.  One uses the crypto chip and one does all the code in software.

The MKR NB 1500 and MKR1000 both have the same crypto chip but the NB stores certs as hard coded arrays where as the 1000 uses the WINC1500.

This is the source file for the arduino-libraries/MKRNB which contains the certs:
https://github.com/arduino-libraries/MKRNB/blob/master/src/utility/NBRootCerts.h

I'm wondering how these arrays were generated.  Anyone know the process/method?

I'm looking at the various datasheets for the module and it is somewhat conflicting.

This manual is the SARA-R4 Series AT Commands Manual
https://www.u-blox.com/en/docs/UBX-17003787

section 20.3.2 SSL/TLS Certificates and privacy manager +USECMNG

Discusses the command the arduino library uses to load the cert arrays in the above header file.  The NBSSLClient.cpp file has the following line:

MODEM.sendf("AT+USECMNG=0,0,\"%s\",%d", _RCs[_certIndex].name, _RCs[_certIndex].size);

So, we know its using the 0,0 parameters for the +USECMNG command.  Some notes on this command:

Manages X.509 certificates and says "certificates and private keys both in DER
(Distinguished Encoding Rules) and in PEM (Privacy-Enhanced Mail) format are accepted. If the provided format is PEM, the imported certificate or private key will be automatically converted in DER format for the internal storage. It is also possible to validate certificates and private keys. Up to 16 certificates or private keys can be imported."

So supposedly it takes DER and PEM certs.  FWIW, a PEM is a Base64 encoded cert and a DER is a binary cert.  When you use the openssl command with s_client and -showcerts it prints a PEM format cert.  You can recognize the BEGIN CERTIFICATE keyword in plain ascii text and in the signature you see alphanumeric text with trailing == padding from the Base64 coding.

According to this section in manual, the certs are converted to DER if its a PEM. Although the Cert can not be retrieved, the MD5 hash string can be retrieved.  When you successfully load a cert, the modem will return the same MD5 hash string.

The manual says the cert must be X.509 and it must have only certain fields provided.  See last bullet in section 20.3.2.1.  (More about this field restriction later.)

Oddly, section 20.3.2.2 shows a raw ascii string for the data as >----BEGIN CERTIFICATE ---  This leads me to believe its literally expecting an asscii text string. 

'>' is hex 0x3E
'-' is hex 0x2D


$ echo ">-" | od -t x1 -An
 3e 2d 0a

Looking at the header file, all the certs start out with the same hex sequence: "0x30, 0x82, 0x03, 0xef"

Looking at this site, https://filext.com/file-extension/DER  it shows the X509 certificate DER file fingerprint has leading 0x30 0x82.

So I'm concluding these files are DER files.

So, how to get a root cert from google and add to this array in NBRootsCert.h?

This is the process I did and sadly it failed:
(When I got the MKR1000 working, I did not use the google.com:443 nor did I use the 
https://cloud.google.com/iot/docs/how-tos/mqtt-bridge "complete Google root CA cert package (128KB) for mqtt.googleapis.com"  instead I pointed the winc1500 to mqtt.googleapis.com:8883.  However I tried to build a combined cert pulled from that server yadda yadda and it failed to load.  As a simple test, I'll try to just load one of the server certs in the 128KB pem file.)

1. Edit https://pki.goog/roots.pem and find the uber GlobalSign root cert.  The issuer and owner are both GlobalSign.  Copy the relevant portion of the cert to a file.

$ cat GS_ROOT_CA.crt
# Operating CA: GlobalSign
# Issuer: CN=GlobalSign Root CA O=GlobalSign nv-sa OU=Root CA
# Subject: CN=GlobalSign Root CA O=GlobalSign nv-sa OU=Root CA
# Label: "GlobalSign Root CA"
# Serial: 4835703278459707669005204
# MD5 Fingerprint: 3e:45:52:15:09:51:92:e1:b7:5d:37:9f:b1:87:29:8a
# SHA1 Fingerprint: b1:bc:96:8b:d4:f4:9d:62:2a:a8:9a:81:f2:15:01:52:a4:1d:82:9c
# SHA256 Fingerprint: eb:d4:10:40:e4:bb:3e:c7:42:c9:e3:81:d3:1e:f2:a4:1a:48:b6:68:5c:96:e7:ce:f3:c1:df:6c:d4:33:1c:99
-----BEGIN CERTIFICATE-----
MIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkG
A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv
b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAw
MDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i
YWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxT
aWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZ
jc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavp
xy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp
1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdG
snUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJ
U26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N8
9iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8E
BTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0B
AQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOz
yj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE
38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymP
AbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUad
DKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbME
HMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A==
-----END CERTIFICATE-----

2.  Convert to DER

You can find this command via google, but its interesting to see the precise command in the u-blox documentation.  This is yet another u-blox document, the "SARA-R4 series Application development guide"

https://www.u-blox.com/en/docs/UBX-18019856

Section 16.1 Certificate format
"SARA-R4 series modules do not support PEM format.  (Notice this does not agree with the other document!!!!)  Only DER and CER formats are supported.  For an example of using OpenSSL application to convert PEM to DER:

openssl x509 -in cert.crt -outform der -out cert.der"

 so, to convert the PEM file above, 

davis@twenty:~/progs/ssl_publy/certs 
$ cat convert_pem_to_der.sh 

INFILE=$1
OUTFILE="${INFILE%.*}.der"

openssl x509 -in ${INFILE} -outform der -out ${OUTFILE}

davis@twenty:~/progs/ssl_publy/certs 
$ ./convert_pem_to_der.sh GS_ROOT_CA.crt 
davis@twenty:~/progs/ssl_publy/certs 
$ file GS_ROOT_CA.der 
GS_ROOT_CA.der: data
davis@twenty:~/progs/ssl_publy/certs 
$ od -t x1 -An --read-bytes=4 GS_ROOT_CA.der 
 30 82 03 75

The file command did not recognize it as a DER file, but the 0x30 0x82 is present.

3.  Convert the file to a byte sequence

davis@twenty:~/progs/ssl_publy/certs 
$ cat make_hex.sh 


echo "file specfied is: $1"

od -t x1 -An  $1 | awk '

{

    for (i = 1; i <= 16; i++)
        printf "0x%s,", $i
    print ""
}
'

davis@twenty:~/progs/ssl_publy/certs 
$ ./make_hex.sh GS_ROOT_CA.der > foo.txt
davis@twenty:~/progs/ssl_publy/certs 
davis@twenty:~/progs/ssl_publy/certs 
$ head -n2 foo.txt 
file specfied is: GS_ROOT_CA.der
0x30,0x82,0x03,0x75,0x30,0x82,0x02,0x5d,0xa0,0x03,0x02,0x01,0x02,0x02,0x0b,0x04,
davis@twenty:~/progs/ssl_publy/certs 

4. Modify NBRootsCert.h and sketch to print debug info.

So, add the contents of foo.txt so its in the NBRootsCert.h.  Since there is a limit of 16 certs, I removed the AWS and Big Daddy certs and added this new one as JFD.

I also modified the top level sketch so that it emits AT commands.

sketch mod:
// orig NB nbAccess;
NB nbAccess(true);

NBRootsCert.h mod:
<stuff snipped>
  {
    "JFD",
    (const uint8_t[]){        0x30,0x82,0x03,0x75,0x30,0x82,0x02,0x5d,0xa0,0x03,0x02,0x01,0x02,0x02,0x0b,0x04,
<stuff snipped>
       0x55,0xe2,0xfc,0x48,0xc9,0x29,0x26,0x69,0xe0
    },
    889
  },

As far as length goes, this matches the others in the array.  Its the number of bytes.

4.  Test the code

<stuff snipped>
AT+USECMNG=0,0,"GeoTrust_Primary_Certification_Authority_G3",1026
>
+USECMNG: 0,0,"GeoTrust_Primary_Certification_Authority_G3","B5E83436C910445848706D2E83D4B805"

OK
AT+USECMNG=0,0,"JFD",889
ERROR


This shows the cert above where I placed mine loading (I skipped showing all the certs loaded.  Nine in total are loaded.  I am attempting to load a new tenth.


