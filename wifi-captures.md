# wifi capturing


# airmon-ng notes

## Installation

airmon-ng is a utility which is part of aircrack-ng.

```
sudo apt-get install aircrack-ng
```
## Setup

Some processes can change the interface and interfere with the
capture.  airmon-ng can kill all the processes but avahi-daemon
will respawn.  Disable it.


```
sudo systemctl disable avahi-daemon

sudo airmon-ng check
sudo airmon-ng check kill
sudo airmon-ng check

sudo airmon-ng start <desired wireless interface id>
```
## Usage

```
sudo ssldump -i wlx00c0ca6d23eb port 443
sudo ssldump -i wls1 port 443
sudo ssldump -r somecapture.pcap
```
