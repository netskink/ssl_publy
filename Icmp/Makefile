
.PHONY: compile upload terminal
.DEFAULT: compile


compile:
	arduino-cli compile  \
        --fqbn arduino:samd:mkr1000  Icmp


upload:
	arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:samd:mkr1000 Icmp

terminal:
	echo type ctrl-a x
	screen /dev/ttyACM0 115200
