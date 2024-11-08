# Instrument_cluster
This project involves the implementation of an instrument cluster as the second DES (Distributed Embedded Systems) project in the SEA:ME curriculum.

## Overview
An instrument cluster application displaying real-time speed data and battery level.

### Features
- Digital speedometer & numeric speed level
- Battery level indicator

## Theoratical Background
- [CAN bus protocol](https://github.com/SEA-ME-DES-01-Instrument-Cluster/Instrument_cluster/wiki/About-CAN-bus-protocol)
- [Speed sensor](https://github.com/SEA-ME-DES-01-Instrument-Cluster/Instrument_cluster/wiki/Specifications-and-usage-of-speed-sensors-compatible-with-Arduino)
- [Qt framework its tools for GUI](https://github.com/SEA-ME-DES-01-Instrument-Cluster/Instrument_cluster/wiki/Basics-of-the-Qt-framework-and-its-tools-for-developing-embedded-GUIs)
- [What is Bare Metal?](https://github.com/SEA-ME-DES-01-Instrument-Cluster/Instrument_cluster/wiki/What-is-Bare-Metal%3F#what-is-bare-metal)

You can also find those topics on our Wiki.

## System Architecture
<img src="./diagram.svg">

## Components and Environment
### Software
- Main application: C++(Qt6)
- GUI: QML
- Firmware(for Arduino): C
- Speed data transmission: Controller Area Network (CAN)
- Battery data accessing: I2C protocol
- Host OS(for development): Ubuntu 20.04
- Raspberry Pi(target machine): Rasbian Desktop 64bit
- IDE: Qt Creator, Arduino IDE
- Version control: Git

### Hardware
- [WaveShare JetRacer AI Kit)](https://www.waveshare.com/wiki/JetRacer_AI_Kit)
- [MH Infrared Speed Sensor Module (FC-03)](https://einstronic.com/product/infrared-speed-sensor-module/)
- [Arduino Nano](https://docs.arduino.cc/hardware/nano/)
- [MCP2515 CAN BUS Module](https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/MCP2515-Family-Data-Sheet-DS20001801K.pdf)
- [SeeedStudio 2-CH CAN FD HAT](https://wiki.seeedstudio.com/2-Channel-CAN-BUS-FD-Shield-for-Raspberry-Pi/)
- [Raspberry Pi 4B](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/)
- [WaveShare 7.9inch DSI LCD](https://www.waveshare.com/wiki/7.9inch_DSI_LCD)

## Configuration
### Display - WaveShare 7.9inch DSI LCD
After we have written RaspberryPi OS (Debian Bookwarm, 64bit) to a sd card, we have added lines below to 'config.txt' at the root of the sd card file system. And ejected the sd card and boot up our Raspberry Pi, and we were able to see the display working as expected.
```
(...)
# WaveShare 7.9inch LCD
dtoverlay=vc4-kms-v3d
dtoverlay=vc4-kms-dsi-waveshare-panel,7_9_inch
```
### SeeedStudio 2-CH CAN HAT for Raspberry Pi
[Followed instructions on here](https://wiki.seeedstudio.com/2-Channel-CAN-BUS-FD-Shield-for-Raspberry-Pi/)
To activate CAN protocol on Raspberry Pi, you need to run:
```
sudo ip link set can1 up type can bitrate 500000
```

### Auto start Instrument Cluster at booting
```
# /etc/xdg/autostart/InstrumentCluster.desktop

[Desktop Entry]
Type=Application
Exec=/home/pi/InstrumentCluster
Hidden=false
NoDisplay=false
X-GNOME-Autostart-enabled=true
Name[en_US]=InstrumentCluster
Name=InstrumentCluster
Comment[en_US]=Start Instrument Cluster at startup
Comment=Start Instrument Cluster at startup
```
## Result
#### Display real-time speed and battery percentage
![image](https://github.com/user-attachments/assets/d907358c-8378-414e-980e-308d59534e3e)

#### Low battery percentage
![image](https://github.com/user-attachments/assets/1daf3746-772a-4799-a34f-05d7a2b9ccd7)

#### Battery charging state
![image](https://github.com/user-attachments/assets/f023f058-d071-40d0-8749-4d62701f8627)
