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
