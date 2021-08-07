# Capture Dump Notes

Looking at arduino-ssl-ethertap-only-goog-domain-halt-004.pcapng

Notes about this capture file

* using wifi access point on same router as lan.
* no other traffic on the lan with possible exception of printer
* only arduino knows ssid/pass

On boot the arduino does the following:

1. uses ntp to sync time with nist.gov 
  frame 192
2. pings google
  frame 193
3. opens webpage to www.google.com
  frame 250
4. Attempts to upload telemetry 74.125.202.206 (gcp iot core mqtt endpoint)
  frame 333

In detail, this exchange requires arp, dns queries, etc.  Some of the simpler
bits of the exchange are mentioned here with screenshots of the capture file 
and discussion.  If nothing else, it shows how to read the decode before
we get to the problem of why ssl mqtt fails.

A couple of notes regarding the wireshark UI.  Notice the filter at top
in green.   That is the display filter.  It allows you to filter frames
from the capture file.  

Since the first frame is selected as the first line in blue of the top panel,
it is showing the networking frames in layers in the middle panel.  In my 
screenshots, most of the image will have the bottom minimized.  That 
panel shows the raw frame.  As you click on items in the middle panel 
it will highlight the relevant bytes in the frame corresponding the clicked
item.

1. joins network.  You can see that in the wifi probe requests and 
probe responses in the other capture files.

2. dhcp request and response.  That is also visible in a wifi capture.

3. dns request and response for ntp time server.  This is shown in 
frame 177.  Notice the name of the time server `time.nist.gov` is visible
in the lower panel as I select the query host portion in the middle panel.

![img](imgs/ss2.png)

Frame 178 which is the dns response and the screenshot shows the 
ip address of 128.138.141.172.  

```
$ nslookup 128.138.141.172
172.141.138.128.in-addr.arpa	name = utcnist2.colorado.edu.
```

![img](imgs/ss3.png)


4. ntp time sync with `time.nist.gov`

Frame 192 shows the ntp request and response.

![img](imgs/ss5.png)

5. ping to google.com

This involves the dns request and response.  This is shown in 
wireshark starting at frame 193 and 194.

In this screenshot, if you haven't noticed it already, the arrows in the 
leftmost frame number column show the start of a conversation and end.
In this example its a ping request and response.

Notice also how the destination address line is selected in the middle 
panel.  Its how ping knows where to send the packet.

![img](imgs/ss1.png)



