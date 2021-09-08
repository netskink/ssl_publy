
# dump DER file in order to find out what fields are in the file.
# This u-blox manual shows which fields are supported.
#
# https://www.u-blox.com/en/docs/UBX-17003787
#
# excerpt section 20.3.2 SSL/TLS Certificates and private keys manager +USECMNG
#
# The USECMNG import functionality allows the following DN value fields:
#
# o  commonName (http://oid-info.com/get/2.5.4.3)
# o  serialNumber (http://oid-info.com/get/2.5.4.5)
# o  countryName (http://oid-info.com/get/2.5.4.6)
# o  localityName (http://oid-info.com/get/2.5.4.7)
# o  stateOrProvinceName (http://oid-info.com/get/2.5.4.8)
# o  organizationName (http://oid-info.com/get/2.5.4.10)
# o  organizationalUnitName (http://oid-info.com/get/2.5.4.11)
# o  userID (http://oid-info.com/get/0.9.2342.19200300.100.1.1)
# o  domainComponent (http://oid-info.com/get/0.9.2342.19200300.100.1.25)
# o  pkcs9_emailAddress (http://oid-info.com/get/1.2.840.113549.1.9.1)
# o  pkcs9_unstructuredName (http://oid-info.com/get/1.2.840.113549.1.9.2)
#
# The import of an X.509 certificate with DN containing other value fields 
# (not in the above list) will result in an import error 
# (error result code: USECMNG invalid certificate/key format).

# $1 is a DER file
openssl asn1parse -in $1 -inform DER
