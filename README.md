# Aerospace Village Badge 2020

This resository is to document and capture all of the engineering and design work that went into creating the [Aerospace Village](https://aerospacevillage.org) Badge for 2020.

The badge is a multifunctional design that is part SWAG, part antenna, part low level protocol interaction. In keeping with the spirit of aviation everything is as small as possible and tries to use as much of the available resources as possible.

You can even use this airplane shaped badge as an anetenna to locate real airplanes transmitting ADS-B. Additionally, you can also use it to capture data from other freqenices (i.e. ACARS) using the built in SMA to wire terminal blocks. Why stop there? You can also interact with your preferred I2C device ([bus pirate](https://learn.sparkfun.com/tutorials/bus-pirate-v36a-hookup-guide/all#introduction)) and control each of the available lighting packages. Alternatively, you could just wear it and look cool.


<img src="/Images/aerospace_Badge_day.GIF" width="300" /> <img src="/Images/aerospace_Badge_night.GIF" width="300" />

## Kit Assembly

Instructions for assembing a kit can be found in the Document folder.
    
  - [Tindie Instructions](https://github.com/daneallen/avBadge_2020/blob/master/Documents/Tindie%20Instructions.pdf)
  - [Instructions sent with kit](https://github.com/daneallen/avBadge_2020/blob/master/Documents/Send%20out%20instructions.pdf)


## Arduino Programming
Using the Arduino IDE Add the correct Boards Manager URL:

    - Under File->Preferences add the following URL http://drazzy.com/package_drazzy.com_index.json
    - Then with the new Boards Maanger options select ATTinyCore

Steps:

    - Programmer - USBTinyISP
    - Clock 8MHZ
    - Burn Bootloader
    - Upload using programmer


## AVR Programming

[device permissions help](https://andreasrohner.at/posts/Electronics/How-to-fix-device-permissions-for-the-USBasp-programmer/)

[ttyACM permission](https://stackoverflow.com/questions/40951728/avrdude-ser-open-cant-open-device-dev-ttyacm0-device-or-resource-busy)

```
sudo adduser <username> dialout
$ sudo chmod a+rw /dev/ttyACM0
```

## Hardware
The ATtiny85 is programmed with the [Sparkfun Tiny AVR Programmer](https://www.sparkfun.com/products/11801) using the [SparkFun ISP Pogo Adapter](https://www.sparkfun.com/products/11591)


## Lanyard Modification
Check out the .stl files that you can print to more easily turn the badge into a wearable lanyard.

<img src="sma lanyard/20200730_210854.jpg" width="300">
